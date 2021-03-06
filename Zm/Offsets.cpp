#include "stdafx.h"
#include "Offsets.h"

HWND Offsets::SelfWnd = FindWindow(NULL, WNDNAME);
Offsets::ScreenSize *Offsets::Screen = reinterpret_cast<Offsets::ScreenSize *>(0x11A554C);
Offsets::entity_t *Offsets::Ent = reinterpret_cast<Offsets::entity_t *>(OFFSET_ENTITY);
Offsets::gentity_t *Offsets::GEnt = reinterpret_cast<Offsets::gentity_t *>(OFFSET_GENTITY_PLAYER);
Vector3 *Offsets::Pos = reinterpret_cast<Vector3 *>(OFFSET_POSITION);
const char *Offsets::WeaponList[95] = {
	"defaultweapon_mp", "ak74u_zm", "mp5k_zm", "qcw05_zm", "ak74u_upgraded_zm",
	"mp5k_upgraded_zm", "qcw05_upgraded_zm", "m14_zm", "m16_zm", "saritch_zm",
	"xm8_zm", "type95_zm", "tar21_zm", "m14_upgraded_zm", "m16_gl_upgraded_zm",
	"saritch_upgraded_zm", "xm8_upgraded_zm", "type95_upgraded_zm", "tar21_upgraded_zm",
	"gun870mcs_zm", "rottweil72_zm", "saiga12_zm", "srm1216_zm", "gun870mcs_upgraded_zm",
	"rottweil72_upgraded_zm", "saiga12_upgraded_zm", "srm1216_upgraded_zm", "galil_zm",
	"fnfal_zm", "rpd_zm", "hamr_zm", "galil_upgraded_zm", "fnfal_upgraded_zm",
	"rpd_upgraded_zm", "hamr_upgraded_zm", "dsr50_zm", "barretm82_zm",
	"dsr50_upgraded_zm", "barretm82_upgraded_zm", "knife_zm", "m1911_zm", "python_zm",
	"judge_zm", "kard_zm", "fiveseven_zm", "beretta93r_zm", "fivesevendw_zm",
	"m1911_upgraded_zm", "python_upgraded_zm", "judge_upgraded_zm", "kard_upgraded_zm",
	"fiveseven_upgraded_zm", "beretta93r_upgraded_zm", "fivesevendw_upgraded_zm", "usrpg_zm",
	"m32_zm", "usrpg_upgraded_zm", "m32_upgraded_zm", "ray_gun_zm", "jetgun_zm",
	"riotshield_zm", "tazer_knuckles_zm", "knife_ballistic_zm", "knife_ballistic_upgraded_zm",
	"knife_ballistic_bowie_zm", "knife_ballistic_bowie_upgraded_zm", "raygun_mark2_zm",
	"raygun_mark2_upgraded_zm", "ray_gun_upgraded_zm", "frag_grenade_zm", "sticky_grenade_zm",
	"cymbal_monkey_zm", "emp_grenade_zm", "claymore_zm", "knife_ballistic_no_melee_zm",
	"knife_ballistic_no_melee_upgraded_zm", "equip_turbine_zm", "equip_turret_zm",
	"equip_electrictrap_zm", "zombie_builder_zm", "buildable_piece_zm", "syrette_zm",
	"zombie_knuckle_crack", "zombie_perk_bottle_doubletap", "zombie_perk_bottle_jugg",
	"zombie_perk_bottle_marathon", "zombie_perk_bottle_revive", "zombie_perk_bottle_sleight",
	"zombie_perk_bottle_tombstone", "zombie_fists_zm", "zombie_tazer_flourish",
	"bowie_knife_zm", "zombie_bowie_flourish", "death_throe_zm", "death_self_zm"
};

int Offsets::WepLookup[] {
	1, 2, 3, 4, 5, 6, 7, 9, 10, 11, 12, 13, 14, 15, 16, 18, 20,
	22, 24, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38,
	39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53,
	55, 57, 58, 59, 60, 61, 62, 64, 65, 66, 67, 68, 69, 70, 71,
	72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86,
	87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101,
	102, 103, 104,
};

Offsets::gentity_t *GetGentity(int index) {
	return (Offsets::gentity_t *)(OFFSET_GENTITY_BASE + (index * OFFSET_GENTITY_SIZE));
}