/*
 * legacyfork: Lua-driven weapon bank overrides so multiple items can share a key.
 */
#include "g_local.h"

/**
 * @brief Rebuild CS_WEAPONBANK_OVERRIDES from all clients.
 * Format: space-separated "client:weapon:bank" tokens (bank 1..MAX_WEAP_BANKS_MP-1).
 */
void G_UpdateWeaponBankConfigString(void)
{
	char buf[MAX_INFO_STRING];
	int  clientNum, weapon, len = 0;

	buf[0] = '\0';

	for (clientNum = 0; clientNum < level.maxclients; clientNum++)
	{
		gclient_t *cl = &level.clients[clientNum];

		if (cl->pers.connected != CON_CONNECTED)
		{
			continue;
		}

		for (weapon = WP_KNIFE; weapon < WP_NUM_WEAPONS; weapon++)
		{
			int bank = cl->weaponBankOverride[weapon];

			if (bank <= 0 || bank >= MAX_WEAP_BANKS_MP)
			{
				continue;
			}

			if (len > 0 && len < (int)sizeof(buf) - 1)
			{
				buf[len++] = ' ';
				buf[len]   = '\0';
			}

			{
				char token[32];
				int  n = Com_sprintf(token, sizeof(token), "%i:%i:%i", clientNum, weapon, bank);

				if (len + n >= (int)sizeof(buf))
				{
					G_Printf("G_UpdateWeaponBankConfigString: truncated (too many overrides)\n");
					trap_SetConfigstring(CS_WEAPONBANK_OVERRIDES, buf);
					return;
				}

				Q_strncpyz(buf + len, token, sizeof(buf) - len);
				len += n;
			}
		}
	}

	trap_SetConfigstring(CS_WEAPONBANK_OVERRIDES, buf);
}

/**
 * @brief Assign weapon to a number-key bank for this client (0 clears).
 */
qboolean G_SetWeaponBankOverride(int clientNum, int weapon, int bank)
{
	gentity_t *ent;

	if (clientNum < 0 || clientNum >= level.maxclients)
	{
		return qfalse;
	}

	if (!IS_VALID_WEAPON(weapon))
	{
		return qfalse;
	}

	if (bank < 0 || bank >= MAX_WEAP_BANKS_MP)
	{
		return qfalse;
	}

	ent = g_entities + clientNum;
	if (!ent->client)
	{
		return qfalse;
	}

	ent->client->weaponBankOverride[weapon] = (byte)bank;
	G_UpdateWeaponBankConfigString();
	return qtrue;
}

/**
 * @brief Clear one weapon bank override (restore default table mapping).
 */
qboolean G_ClearWeaponBankOverride(int clientNum, int weapon)
{
	return G_SetWeaponBankOverride(clientNum, weapon, 0);
}

/**
 * @brief Clear all weapon bank overrides for a client.
 */
void G_ClearWeaponBankOverrides(int clientNum)
{
	gentity_t *ent;
	int       weapon;

	if (clientNum < 0 || clientNum >= level.maxclients)
	{
		return;
	}

	ent = g_entities + clientNum;
	if (!ent->client)
	{
		return;
	}

	for (weapon = 0; weapon < WP_NUM_WEAPONS; weapon++)
	{
		ent->client->weaponBankOverride[weapon] = 0;
	}

	G_UpdateWeaponBankConfigString();
}
