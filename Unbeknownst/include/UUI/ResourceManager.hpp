#pragma once

#include "TGUI\TGUI.hpp"
#include <unordered_map>

namespace uui {

	class ResourceManager {

		public:

			void addTexture(std::string textureName, sf::Texture texture) { textureMap[textureName] = texture; }
			void addTheme(std::string themeName, tgui::Theme::Ptr theme) { themeMap[themeName] = theme; }
			void addFont(std::string fontName, sf::Font font) { fontMap[fontName] = font; }

			const sf::Texture& getTexture(std::string textureName) { return textureMap[textureName]; }
			const tgui::Theme::Ptr& getTheme(std::string themeName) { return themeMap[themeName]; }
			const sf::Font& getFont(std::string fontName) { return fontMap[fontName]; }

			static ResourceManager* Instance() { return &resourceManager; }

		protected:

			ResourceManager() {}

		private:

			static ResourceManager resourceManager;
			
			std::unordered_map<std::string, sf::Texture> textureMap;
			std::unordered_map<std::string, tgui::Theme::Ptr> themeMap;
			std::unordered_map<std::string, sf::Font> fontMap;

	};
}
