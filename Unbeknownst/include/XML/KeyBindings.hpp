#pragma once

#include "XML\KeyInput.hpp"
#include <unordered_map>

class KeyBindings {

	public:

		static KeyBindings* Instance() { return &keyBinds; }

		void InitialiseKeyBinds();

		const KeyData& GetKey(std::string key) { return defaultKeyBinds[key]; }

	protected:
		
		KeyBindings() {}

	private:

		static KeyBindings keyBinds;

		std::unordered_map<std::string, KeyData> defaultKeyBinds;
		std::unordered_map<std::string, KeyData> customKeyBinds;

		void ParseKey(KeyData& key, std::string input, std::string keycode);
};