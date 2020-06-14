#pragma once
#include "../../dependencies/utilities/csgo.hpp"
#include "../features/features.hpp"
#include "../features/misc/engine_prediction.hpp"
#include "../menu/menu.hpp"

hooks::create_move::fn create_move_original = nullptr;
hooks::paint_traverse::fn paint_traverse_original = nullptr;

bool hooks::initialize() {
	auto create_move_target = reinterpret_cast<void*>(get_virtual(interfaces::clientmode, 24));
	auto paint_traverse_target = reinterpret_cast<void*>(get_virtual(interfaces::panel, 41));

	if (MH_Initialize() != MH_OK) {
		throw std::runtime_error("failed to initialize MH_Initialize.");
		return false;
	}

	if (MH_CreateHook(create_move_target, &create_move::hook, reinterpret_cast<void**>(&create_move_original)) != MH_OK) {
		throw std::runtime_error("failed to initialize create_move. (outdated index?)");
		return false;
	}

	if (MH_CreateHook(paint_traverse_target, &paint_traverse::hook, reinterpret_cast<void**>(&paint_traverse_original)) != MH_OK) {
		throw std::runtime_error("failed to initialize paint_traverse. (outdated index?)");
		return false;
	}

	if (MH_EnableHook(MH_ALL_HOOKS) != MH_OK) {
		throw std::runtime_error("failed to enable hooks.");
		return false;
	}

	console::log("[setup] hooks initialized!\n");
	return true;
}

void hooks::release() {
	MH_Uninitialize();

	MH_DisableHook(MH_ALL_HOOKS);
}

bool __fastcall hooks::create_move::hook(void* ecx, void* edx, int input_sample_frametime, c_usercmd* cmd) {
	create_move_original(input_sample_frametime, cmd);

	if (!cmd || !cmd->command_number)
		return create_move_original(input_sample_frametime, cmd);

	csgo::local_player = reinterpret_cast<player_t*>(interfaces::entity_list->get_client_entity(interfaces::engine->get_local_player()));

	uintptr_t* frame_pointer;
	__asm mov frame_pointer, ebp;
	bool& send_packet = *reinterpret_cast<bool*>(*frame_pointer - 0x1C);

	auto old_viewangles = cmd->viewangles;
	auto old_forwardmove = cmd->forwardmove;
	auto old_sidemove = cmd->sidemove;
	if(csgo::local_player)
	if (variables::backtrack && interfaces::engine->is_in_game() && interfaces::engine->is_connected() && csgo::local_player->is_alive())
	{
		if (cmd->command_number)
		{
			CBacktracking::RegisterTick(cmd);
		}
		CBacktracking::Begin(cmd);
		CBacktracking::End();
	}
	misc::movement::bunny_hop(cmd);
	legitbot::AimBot(cmd);
	prediction::start(cmd); 
	{
	} prediction::end();

	math::correct_movement(old_viewangles, cmd, old_forwardmove, old_sidemove);

	cmd->forwardmove = std::clamp(cmd->forwardmove, -450.0f, 450.0f);
	cmd->sidemove = std::clamp(cmd->sidemove, -450.0f, 450.0f);
	cmd->upmove = std::clamp(cmd->sidemove, -320.0f, 320.0f);

	cmd->viewangles.normalize();
	cmd->viewangles.x = std::clamp(cmd->viewangles.x, -89.0f, 89.0f);
	cmd->viewangles.y = std::clamp(cmd->viewangles.y, -180.0f, 180.0f);
	cmd->viewangles.z = 0.0f;
	return false;
}

void __stdcall hooks::paint_traverse::hook(unsigned int panel, bool force_repaint, bool allow_force) {
	auto panel_to_draw = fnv::hash(interfaces::panel->get_panel_name(panel));

	switch (panel_to_draw) {
	case fnv::hash("MatSystemTopPanel"):
		
		if (variables::watermark)
		{
			int width, height;
			interfaces::engine->get_screen_size(width, height);

			static int fps, old_tick_count;

			if ((interfaces::globals->tick_count - old_tick_count) > 50) {
				fps = static_cast<int>(1.f / interfaces::globals->frame_time);
				old_tick_count = interfaces::globals->tick_count;
			}
			std::stringstream ss;

			ss << "CRABWORKS.CC | fps: " << fps << "ms";

			render::draw_filled_rect(width - 275, 2, 230, 20, color(33, 35, 47, 255));
			render::draw_outline(width - 275, 2, 230, 20, color(30, 30, 41, 255));
			render::draw_text_string(width - 270, 7, render::fonts::watermark_font, ss.str().c_str(), false, color(255, 255, 255, 255));
		}

		visuals::boxesp();
		visuals::nameesp();
		visuals::healthesp();
		visuals::armoresp();
		visuals::glowesp();
		visuals::boneesp();
		visuals::snaplineesp();
		visuals::drawc4();
		visuals::drawfov();
	//	if(csgo::local_player)
		//if(variables::backtrack && variables::drawbacktrack && interfaces::engine->is_in_game() && interfaces::engine->is_connected() && csgo::local_player->is_alive())
			//CBacktracking::Draw();
		menu::toggle();
		menu::render();

		break;

	case fnv::hash("FocusOverlayPanel"):
		interfaces::panel->set_keyboard_input_enabled(panel, variables::menu::opened);
		interfaces::panel->set_mouse_input_enabled(panel, variables::menu::opened);
		break;
	}

	paint_traverse_original(interfaces::panel, panel, force_repaint, allow_force);
}