#pragma once

#include <map>
#include "Font.h"

enum class FontType
{
	ARIAL
};

class FontLibrary
{
public:
	static void Load(Font* _font, FontType _key) {
		library.insert(std::pair<FontType, Font*>(_key, _font));
	};

	static Font* Retrieve(FontType _key) {
		return library[_key];
	}

    static void Destroy() {
        for (auto [key, value] : library)
            delete value;
    }

private:
    FontLibrary() = default;
	static std::map<FontType, Font*> library;

public:
    static void Initialize()
    {
        Font* arial_font = new Font;

        // Initialize font arial
        arial_font->load("resources/fonts/arial.ttf");
        Load(arial_font, FontType::ARIAL);
    }
};

