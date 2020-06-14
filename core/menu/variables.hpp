#pragma once

namespace variables {
	// misc
	inline bool watermark = true;
	inline bool bhop = false;
	inline bool backtrack = false;
	//visuals
	inline bool showteamesp = false;
	inline bool boxesp = false;
	inline bool nameesp = false;
	inline bool healthesp = false;
	inline bool armoresp = false;
	inline bool glowesp = false;
	inline bool boneesp = false;
	inline bool snaplineesp = false;
	inline bool drawc4 = false;
	inline bool drawbacktrack = false;
	inline bool drawfov = false;
	//aim
	inline bool aimbot = false;
	inline float aimbot_fov = 0.f;
	inline float rcs_x;
	inline float rcs_y;
	inline float aimbot_smoothing = 2.f;
	inline bool aimbot_isvisiblecheck = true;
	inline bool aimbot_rcs = true;
	inline float aimbot_rcsval = 2.f;
	inline float aim_fov_pistol; //= 0.0f ;
	inline float rcs_x_pistol{ 0.0f };
	inline float rcs_y_pistol{ 0.0f };
	inline float rcs_x_rifle{ 0.0f };
	inline float rcs_y_rifle{ 0.0f };
	inline float rcs_x_sniper{ 0.0f };
	inline float rcs_y_sniper{ 0.0f };
	inline float rcs_x_heavy{ 0.0f };
	inline float rcs_y_heavy{ 0.0f };
	inline float rcs_x_smg{ 0.0f };
	inline float rcs_y_smg{ 0.0f };
	inline float aim_smooth_pistol{ 5.f };
	inline float aim_fov_rifle{ 0.0f };
	inline float aim_smooth_rifle{ 5.f };
	inline float aim_fov_sniper{ 0.0f };
	inline float aim_smooth_sniper{ 5.f };
	inline float aim_fov_heavy{ 0.0f };
	inline float aim_smooth_heavy{ 5.f };
	inline float aim_fov_smg{ 0.0f };
	inline float aim_smooth_smg{ 5.f };
	inline int aim_bone_smg{ 0 };
	inline int aim_bone_sniper{ 0 };
	inline int aim_bone_pistol{ 0 };
	inline int aim_mode{ 0 };
	inline int aim_bone_rifle{ 0 };
	inline int aim_bone_heavy{ 0 };
	inline int aim_weapon{ 0 };;

	namespace menu {
		inline bool opened = false;
		inline int x = 140, y = 140;
		inline int w = 600, h = 450;
	}
}