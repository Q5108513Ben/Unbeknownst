#pragma once

#include "XML\KeyInput.hpp"
#include <unordered_map>

class KeyBindings {

	public:

		static KeyBindings* Instance() { return &keyBinds; }

		void InitialiseKeyBinds();

		const KeyData& GetKey(std::string key) { return userKeyBinds[key]; }

		const std::unordered_map<std::string, KeyData>& GetUserKeys() { return userKeyBinds; }
		const std::vector<std::pair<std::string, KeyData>>& GetDefaultKeys() { return defaultKeyBinds; }

	protected:
		
		KeyBindings() {}

	private:

		static KeyBindings keyBinds;

		std::vector<std::pair<std::string, KeyData>> defaultKeyBinds;
		std::unordered_map<std::string, KeyData> userKeyBinds;

		void ParseKey(KeyData& key, std::string input, std::string keycode);
};