#include "menu.hpp"
#include "../features/features.hpp"
//todo auto elements positioning

auto do_frame = [&](std::int32_t x, std::int32_t y, std::int32_t w, std::int32_t h, color bg, color header_text, color header_line, const std::string& name) {
		render::draw_filled_rect(x, y, w, h, bg);
		render::draw_filled_rect(x, y, w, 30, header_text);
		render::draw_filled_rect(x, y + 30, w, 2, header_line);
		render::draw_text_string(x + 10, y + 8, render::fonts::watermark_font, name, false, color::white());
};

void menu::render() {
	if (!variables::menu::opened)
		return;

	do_frame(variables::menu::x, variables::menu::y, variables::menu::w, variables::menu::h, color(36, 36, 36, 255), color(25, 25, 25, 255), color(36, 36, 36, 255), "CRABWORKS.CC");
	
	menu_framework::group_box(variables::menu::x + 5, variables::menu::y + 35, variables::menu::w - 10, 80, render::fonts::watermark_font, "tabs", false); {
		menu_framework::tab(variables::menu::x + variables::menu::w / 3 - 35, variables::menu::y + 55, 100, 30, render::fonts::watermark_font, "aimbot", menu::current_tab, 0, false);
		menu_framework::tab(variables::menu::x + variables::menu::w / 2 - 35, variables::menu::y + 55, 100, 30, render::fonts::watermark_font, "visuals", menu::current_tab, 1, false);
		menu_framework::tab(variables::menu::x + variables::menu::w - variables::menu::w / 3 - 35, variables::menu::y + 55, 100, 30, render::fonts::watermark_font, "misc", menu::current_tab, 2, false);
	}

	switch (current_tab) {
	case 0:
		menu_framework::group_box(variables::menu::x + 5, variables::menu::y + 125, variables::menu::w - 10, 320, render::fonts::watermark_font, "aimbot", false); 
		static int test = 0;
		static int page = 0;
		switch (page)
		{
		case 0:
			

				menu_framework::check_box(variables::menu::x + 10, variables::menu::y + 135, variables::menu::x + 575, render::fonts::watermark_font, "aimbot", variables::aimbot);
				menu_framework::slider(variables::menu::x + 10, variables::menu::y + 150, 125, render::fonts::watermark_font, "fov", variables::aim_fov_pistol, 0.f, 10.f);
				menu_framework::slider(variables::menu::x + 10, variables::menu::y + 165, 125, render::fonts::watermark_font, "smooth", variables::aim_smooth_pistol, 1.f, 5.f);
				menu_framework::check_box(variables::menu::x + 10, variables::menu::y + 180, variables::menu::x + 575, render::fonts::watermark_font, "Only enemy is visible", variables::aimbot_isvisiblecheck);
			
		case 1:
			
			   
				menu_framework::check_box(variables::menu::x + 10, variables::menu::y + 135, variables::menu::x + 575, render::fonts::watermark_font, "aimbot", variables::aimbot);
				menu_framework::slider(variables::menu::x + 10, variables::menu::y + 150, 125, render::fonts::watermark_font, "fov", variables::aim_fov_rifle, 0.f, 10.f);
				menu_framework::slider(variables::menu::x + 10, variables::menu::y + 165, 125, render::fonts::watermark_font, "smooth", variables::aim_fov_rifle, 1.f, 5.f);
				menu_framework::check_box(variables::menu::x + 10, variables::menu::y + 180, variables::menu::x + 575, render::fonts::watermark_font, "Only enemy is visible", variables::aimbot_isvisiblecheck);
			
			
		}
		break;
	case 1:
		menu_framework::group_box(variables::menu::x + 5, variables::menu::y + 125, variables::menu::w - 10, 320, render::fonts::watermark_font, "visuals", false); {
			menu_framework::check_box(variables::menu::x + 10, variables::menu::y + 135, variables::menu::x + 575, render::fonts::watermark_font, "Team ESP", variables::showteamesp);
			menu_framework::check_box(variables::menu::x + 10, variables::menu::y + 150, variables::menu::x + 575, render::fonts::watermark_font, "box", variables::boxesp);
			menu_framework::check_box(variables::menu::x + 10, variables::menu::y + 165, variables::menu::x + 575, render::fonts::watermark_font, "name", variables::nameesp);
			menu_framework::check_box(variables::menu::x + 10, variables::menu::y + 180, variables::menu::x + 575, render::fonts::watermark_font, "health", variables::healthesp);
			menu_framework::check_box(variables::menu::x + 10, variables::menu::y + 195, variables::menu::x + 575, render::fonts::watermark_font, "armour", variables::armoresp);
			//menu_framework::check_box(variables::menu::x + 10, variables::menu::y + 210, variables::menu::x + 575, render::fonts::watermark_font, "Glow ESP", variables::glowesp);
			menu_framework::check_box(variables::menu::x + 10, variables::menu::y + 225, variables::menu::x + 575, render::fonts::watermark_font, "skeleton", variables::boneesp);
		//	menu_framework::check_box(variables::menu::x + 10, variables::menu::y + 240, variables::menu::x + 575, render::fonts::watermark_font, "Snapline ESP", variables::snaplineesp);
			menu_framework::check_box(variables::menu::x + 10, variables::menu::y + 255, variables::menu::x + 575, render::fonts::watermark_font, "draw bomb", variables::drawc4);
			menu_framework::check_box(variables::menu::x + 10, variables::menu::y + 270, variables::menu::x + 575, render::fonts::watermark_font, "Draw Backtrack", variables::drawbacktrack);
			menu_framework::check_box(variables::menu::x + 10, variables::menu::y + 285, variables::menu::x + 575, render::fonts::watermark_font, "draw fov", variables::drawfov);
		}
		break;
	case 2:
		menu_framework::group_box(variables::menu::x + 5, variables::menu::y + 125, variables::menu::w - 10, 320, render::fonts::watermark_font, "misc", false); {
			menu_framework::check_box(variables::menu::x + 10, variables::menu::y + 135, variables::menu::x + 575, render::fonts::watermark_font, "WaterMark", variables::watermark);
			menu_framework::check_box(variables::menu::x + 10, variables::menu::y + 150, variables::menu::x + 575, render::fonts::watermark_font, "BunnyHop", variables::bhop);
			menu_framework::check_box(variables::menu::x + 10, variables::menu::y + 165, variables::menu::x + 575, render::fonts::watermark_font, "Backtracking", variables::backtrack);
		}
		break;
	}

	menu_framework::menu_movement(variables::menu::x, variables::menu::y, variables::menu::w, 30);
}

void menu::toggle() {
	if (GetAsyncKeyState(VK_INSERT) & 1)
		variables::menu::opened = !variables::menu::opened;
}