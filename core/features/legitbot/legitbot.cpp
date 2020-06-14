#include "../features.hpp"

player_t* legitbot::GetBestTarget(c_usercmd* cmd)
{
    float ofov = variables::aimbot_fov;
    float nfov = 0;
    player_t* player = nullptr;

    for (int iPlayer = 0; iPlayer < interfaces::globals->max_clients; iPlayer++)
    {
		auto pCSPlayer = reinterpret_cast<player_t*>(interfaces::entity_list->get_client_entity(iPlayer));
		if (!pCSPlayer)
			continue;
		if (pCSPlayer == csgo::local_player || pCSPlayer->team() == csgo::local_player->team())
			continue;
		if (pCSPlayer->dormant())
			continue;
		if (!(pCSPlayer->is_alive() && pCSPlayer->health() > 0))
			continue;
        if (pCSPlayer->has_gun_game_immunity())
            continue;
        vec3_t eyepos = csgo::local_player->get_eye_pos();
        vec3_t enemyheadpos = pCSPlayer->get_bone_position(8);
        vec3_t angleTo = math::calculate_angle(eyepos, enemyheadpos);
        angleTo.clamp();
        nfov = cmd->viewangles.distance_to(angleTo);

        if (nfov < ofov)
        {
            ofov = nfov;
            player = pCSPlayer;
        }
    }
    return player;
}

void legitbot::weapon_settings(weapon_t* weapon)
{
    

    if (!weapon)
        return;
    
    if (is_pistol(weapon)) {
        switch (variables::aim_bone_pistol) {
        case 0:
            hitbox_id = hitbox_head;
            break;
        case 1:
            hitbox_id = hitbox_neck;
            break;
        case 2:
            hitbox_id = hitbox_chest;
            break;
        case 3:
            hitbox_id = hitbox_stomach;
            break;
        case 4:
            hitbox_id = hitbox_pelvis;
            break;
        }
        variables::aimbot_smoothing = variables::aim_smooth_pistol;
        variables::aimbot_fov = variables::aim_fov_pistol;
        variables::rcs_x = variables::rcs_x_pistol;
        variables::rcs_y = variables::rcs_y_pistol;
    }
    else if (is_rifle(weapon)) {
        switch (variables::aim_bone_rifle) {
        case 0:
            hitbox_id = hitbox_head;
            break;
        case 1:
            hitbox_id = hitbox_neck;
            break;
        case 2:
            hitbox_id = hitbox_chest;
            break;
        case 3:
            hitbox_id = hitbox_stomach;
            break;
        case 4:
            hitbox_id = hitbox_pelvis;
            break;
        }

        variables::aimbot_smoothing = variables::aim_smooth_rifle;
        variables::aimbot_fov = variables::aim_fov_rifle;
        variables::rcs_x = variables::rcs_x_rifle;
        variables::rcs_y = variables::rcs_y_rifle;
    }
    else if (is_sniper(weapon)) {
        switch (variables::aim_bone_sniper) {
        case 0:
            hitbox_id = hitbox_head;
            break;
        case 1:
            hitbox_id = hitbox_neck;
            break;
        case 2:
            hitbox_id = hitbox_chest;
            break;
        case 3:
            hitbox_id = hitbox_stomach;
            break;
        case 4:
            hitbox_id = hitbox_pelvis;
            break;
        }

        variables::aimbot_smoothing = variables::aim_smooth_sniper;
        variables::aimbot_fov = variables::aim_fov_sniper;
        variables::rcs_x = variables::rcs_x_sniper;
        variables::rcs_y = variables::rcs_y_sniper;
    }
    else if (is_heavy(weapon)) {
        switch (variables::aim_bone_heavy) {
        case 0:
            hitbox_id = hitbox_head;
            break;
        case 1:
            hitbox_id = hitbox_neck;
            break;
        case 2:
            hitbox_id = hitbox_chest;
            break;
        case 3:
            hitbox_id = hitbox_stomach;
            break;
        case 4:
            hitbox_id = hitbox_pelvis;
            break;
        }

        variables::aimbot_smoothing = variables::aim_smooth_heavy;
        variables::aimbot_fov = variables::aim_fov_heavy;
        variables::rcs_x = variables::rcs_x_heavy;
        variables::rcs_y = variables::rcs_y_heavy;
    }
    else if (is_smg(weapon)) {
        switch (variables::aim_bone_smg) {
        case 0:
            hitbox_id = hitbox_head;
            break;
        case 1:
            hitbox_id = hitbox_neck;
            break;
        case 2:
            hitbox_id = hitbox_chest;
            break;
        case 3:
            hitbox_id = hitbox_stomach;
            break;
        case 4:
            hitbox_id = hitbox_pelvis;
            break;
        }

        variables::aimbot_smoothing = variables::aim_smooth_smg;
        variables::aimbot_fov = variables::aim_fov_smg;
        variables::rcs_x = variables::rcs_x_smg;
        variables::rcs_y = variables::rcs_y_smg;
    }
}

void legitbot::AimBot(c_usercmd* cmd)
{
    if (!variables::aimbot)
        return;
    if (!interfaces::engine->is_connected() || !interfaces::engine->is_in_game())
        return;
    if (!csgo::local_player)
        return;
    if (!csgo::local_player->is_alive())
        return;
    player_t* target = GetBestTarget(cmd);
    auto weapon = csgo::local_player->active_weapon();
    weapon_settings(weapon);
    if (target)
    {
        vec3_t eyepos = csgo::local_player->get_eye_pos();
        vec3_t targethead = target->get_bone_position(8);
        vec3_t viewangles = math::calculate_angle(eyepos, targethead);
        viewangles.clamp();
        vec3_t delta = cmd->viewangles - viewangles;
        delta.clamp();
        vec3_t finalAng = cmd->viewangles - delta / (variables::aimbot_smoothing * 20);
        finalAng.clamp();
        if (variables::aimbot_isvisiblecheck && csgo::local_player->can_see_player_pos(target, target->get_eye_pos()))
        {
            cmd->viewangles = finalAng;
            interfaces::engine->set_view_angles(cmd->viewangles);
        }
        else if(!variables::aimbot_isvisiblecheck)
        {
            cmd->viewangles = finalAng;
            interfaces::engine->set_view_angles(cmd->viewangles);
        }

    }
}