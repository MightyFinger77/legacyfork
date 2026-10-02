--[[
  legacyfork example: put adrenaline on weapon bank 7 for players with max First Aid.

  Requires legacyfork qagame/cgame with et.SetWeaponBank.
  Adjust skill level check to match your server (SK_MEDIC_ADRENALINE / max med).
]]

local WP_ADREN = et.WP_MEDIC_ADRENALINE
local BANK_7   = 7

-- Example: call from your existing max-med grant logic after AddWeaponToPlayer
function StackAdrenOn7(clientNum)
  -- et.AddWeaponToPlayer(clientNum, WP_ADREN, ammo, clip, 0)
  et.SetWeaponBank(clientNum, WP_ADREN, BANK_7)
end

function et_ClientDisconnect(clientNum)
  et.ClearWeaponBanks(clientNum)
end
