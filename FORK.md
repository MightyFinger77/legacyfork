# legacyfork

Fork of [etlegacy/etlegacy](https://github.com/etlegacy/etlegacy) based on **v2.86.0**.

Extra feature: **stackable weapon banks** — multiple owned items can share one number key and cycle on repeat press. Your Lua can grant weapons and assign them to any bank via `et.SetWeaponBank`.

## Remotes

| remote | URL |
|--------|-----|
| `upstream` | `https://github.com/etlegacy/etlegacy.git` |
| `origin` | your GitHub fork |

## Stay current with ET Legacy

```bash
git fetch upstream --tags
git merge v2.8x.y
# resolve conflicts (usually cg_weapons.c, g_lua.c, bg_public.h, g_weaponbank.c)
```

Prefer small, isolated fork commits so merges stay easy.

## Build

Follow upstream ET Legacy build docs (CMake). Mod `fs_game` remains **`legacy`**.

## Lua: adren on key 7 for max First Aid (any class)

```lua
-- After granting adren (example):
-- et.AddWeaponToPlayer(clientNum, et.WP_MEDIC_ADRENALINE, ammo, clip, 0)
et.SetWeaponBank(clientNum, et.WP_MEDIC_ADRENALINE, 7)

-- Clear assignment (weapon stays owned; bank falls back to default table):
-- et.ClearWeaponBank(clientNum, et.WP_MEDIC_ADRENALINE)

-- Clear all overrides for a client:
-- et.ClearWeaponBanks(clientNum)
```

Engineer with mines + adren both on bank 7: press **7** for mines, **7** again for adren.

Grant rules (skill checks, etc.) stay in Lua; the engine only handles stacking/cycling.
