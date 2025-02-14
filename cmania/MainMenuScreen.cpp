﻿#include "SongSelectScreen.h"
#include "ScreenController.h"
#include "SettingsScreen.h"
#include "MainMenuScreen.h"
#include "LogOverlay.h"

class MainMenuScreen : public Screen {
	bool is_name_exists = false;
	std::wstring input_buf;
	virtual void Activate(bool y) override {
		if (y) {
			is_name_exists = game->Settings["Name"].GetString() != 0;
		}
	}
	virtual void Render(GameBuffer& buf) {
		if (!is_name_exists) {
			buf.DrawString("输入您的大名(仅用于录像):", 0, 0, {}, {});
			buf.DrawString(input_buf, 0, 1, {}, {});
			return;
		}
		buf.DrawString("按下 Enter 进入选歌界面\n按下 O 键进行设置", 0, 0, {}, {});
	}
	virtual void Key(KeyEventArgs kea) {
		if (kea.Pressed) {
			if (!is_name_exists) {
				if (kea.Key == ConsoleKey::Backspace) {
					if (input_buf.size() > 0) {
						input_buf.resize(input_buf.size() - 1);
					}
					return;
				}
				if (kea.Key == ConsoleKey::Enter) {
					auto str = Utf162Utf8(std::wstring{ input_buf.begin(), input_buf.end() });
					is_name_exists = true;
					game->Settings["Name"].SetArray(str.c_str(), str.size());
					game->Settings.Write();
				}
				if (kea.UnicodeChar >= 31) {
					input_buf.push_back(kea.UnicodeChar);
				}
				return;
			}
			if (kea.Key == ConsoleKey::Enter) {
				parent->Navigate(MakeSongSelectScreen());
			}
			if (kea.Key == ConsoleKey::O) {
				parent->Navigate(MakeSettingsScreen());
			}
		}
	}
};

Screen* MakeMainMenuScreen() {
	return new MainMenuScreen();
}
