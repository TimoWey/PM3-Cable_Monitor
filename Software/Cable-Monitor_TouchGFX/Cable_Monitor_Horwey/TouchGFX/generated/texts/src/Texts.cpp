/* DO NOT EDIT THIS FILE */
/* This file is autogenerated by the text-database code generator */

#include <stdarg.h>
#include <touchgfx/TextProvider.hpp>
#include <touchgfx/Texts.hpp>
#include <touchgfx/TypedText.hpp>
#include <touchgfx/Unicode.hpp>
#include <touchgfx/hal/HAL.hpp>
#include <touchgfx/lcd/LCD.hpp>
#include <texts/TypedTextDatabase.hpp>

uint16_t touchgfx::Font::getStringWidth(const touchgfx::Unicode::UnicodeChar* text, ...) const
{
    va_list pArg;
    va_start(pArg, text);
    uint16_t width = getStringWidthLTR(TEXT_DIRECTION_LTR, text, pArg);
    va_end(pArg);
    return width;
}

uint16_t touchgfx::Font::getStringWidth(touchgfx::TextDirection textDirection, const touchgfx::Unicode::UnicodeChar* text, ...) const
{
    va_list pArg;
    va_start(pArg, text);
    uint16_t width = getStringWidthLTR(textDirection, text, pArg);
    va_end(pArg);
    return width;
}

touchgfx::Unicode::UnicodeChar touchgfx::TextProvider::getNextLigature(TextDirection direction)
{
    if (fontGsubTable && nextCharacters.peekChar())
    {
        substituteGlyphs();
        if (nextCharacters.peekChar(1) == 0x093F) // Hindi I-matra
        {
            nextCharacters.replaceAt1(nextCharacters.peekChar());
            nextCharacters.replaceAt0(0x093F);
        }
    }
    return getNextChar();
}

void touchgfx::TextProvider::initializeInternal()
{
    fillInputBuffer();
}

void touchgfx::LCD::drawString(touchgfx::Rect widgetArea, const touchgfx::Rect& invalidatedArea, const touchgfx::LCD::StringVisuals& stringVisuals, const touchgfx::Unicode::UnicodeChar* format, ...)
{
    va_list pArg;
    va_start(pArg, format);
    drawStringLTR(widgetArea, invalidatedArea, stringVisuals, format, pArg);
    va_end(pArg);
}

// Default TypedTextDatabase
extern const touchgfx::TypedText::TypedTextData* const typedTextDatabaseArray[];

TEXT_LOCATION_FLASH_PRAGMA
KEEP extern const touchgfx::Unicode::UnicodeChar texts_all_languages[] TEXT_LOCATION_FLASH_ATTRIBUTE = {
    0x56, 0x65, 0x72, 0x73, 0x69, 0x6f, 0x6e, 0x3a, 0x20, 0x31, 0x2e, 0x30, 0xa, 0x44, 0x61, 0x74, 0x65, 0x3a, 0x20, 0x30, 0x31, 0x2e, 0x31, 0x32, 0x2e, 0x32, 0x30, 0x32, 0x33, 0xa, 0x41, 0x75, 0x74, 0x68, 0x6f, 0x72, 0x73, 0x3a, 0x20, 0x48, 0x6f, 0x72, 0x76, 0x61, 0x74, 0x20, 0x26, 0x20, 0x57, 0x65, 0x79, 0xa, 0x4d, 0x6f, 0x64, 0x75, 0x6c, 0x3a, 0x20, 0x45, 0x54, 0x2e, 0x50, 0x4d, 0x33, 0x20, 0x5a, 0x48, 0x41, 0x57, 0xa, 0x4c, 0x65, 0x63, 0x74, 0x75, 0x72, 0x65, 0x72, 0x73, 0x3a, 0x20, 0x4d, 0x61, 0x74, 0x69, 0x63, 0x20, 0x26, 0xa, 0x45, 0x68, 0x72, 0x65, 0x6e, 0x73, 0x70, 0x65, 0x72, 0x67, 0x65, 0x72, 0x0, // @0 "Version: 1.0\nDate: 01.12.2023\nAuthors: Horvat & Wey\nModul: ET.PM3 ZHAW\nLecturers: Matic &\nEhrensperger"
    0x41, 0x63, 0x63, 0x75, 0x72, 0x61, 0x74, 0x65, 0x20, 0x4d, 0x65, 0x61, 0x73, 0x75, 0x72, 0x65, 0x6d, 0x65, 0x6e, 0x74, 0x3a, 0x20, 0x31, 0x2d, 0x50, 0x68, 0x61, 0x73, 0x65, 0x0, // @103 "Accurate Measurement: 1-Phase"
    0x41, 0x63, 0x63, 0x75, 0x72, 0x61, 0x74, 0x65, 0x20, 0x4d, 0x65, 0x61, 0x73, 0x75, 0x72, 0x65, 0x6d, 0x65, 0x6e, 0x74, 0x3a, 0x20, 0x33, 0x2d, 0x50, 0x68, 0x61, 0x73, 0x65, 0x0, // @133 "Accurate Measurement: 3-Phase"
    0x48, 0x61, 0x6c, 0x6c, 0x2d, 0x53, 0x65, 0x6e, 0x73, 0x6f, 0x72, 0x20, 0x20, 0x43, 0x61, 0x6c, 0x69, 0x62, 0x72, 0x61, 0x74, 0x69, 0x6f, 0x6e, 0x20, 0x4d, 0x65, 0x6e, 0x75, 0x0, // @163 "Hall-Sensor  Calibration Menu"
    0x53, 0x69, 0x6e, 0x67, 0x6c, 0x65, 0x20, 0x4d, 0x65, 0x61, 0x73, 0x75, 0x72, 0x65, 0x6d, 0x65, 0x6e, 0x74, 0x3a, 0x20, 0x31, 0x2d, 0x50, 0x68, 0x61, 0x73, 0x65, 0x0, // @193 "Single Measurement: 1-Phase"
    0x53, 0x69, 0x6e, 0x67, 0x6c, 0x65, 0x20, 0x4d, 0x65, 0x61, 0x73, 0x75, 0x72, 0x65, 0x6d, 0x65, 0x6e, 0x74, 0x3a, 0x20, 0x33, 0x2d, 0x50, 0x68, 0x61, 0x73, 0x65, 0x0, // @221 "Single Measurement: 3-Phase"
    0x41, 0x63, 0x63, 0x75, 0x72, 0x61, 0x74, 0x65, 0x20, 0x4d, 0x65, 0x61, 0x73, 0x75, 0x72, 0x65, 0x6d, 0x65, 0x6e, 0x74, 0x20, 0x4d, 0x65, 0x6e, 0x75, 0x0, // @249 "Accurate Measurement Menu"
    0x53, 0x69, 0x6e, 0x67, 0x6c, 0x65, 0x20, 0x4d, 0x65, 0x61, 0x73, 0x75, 0x72, 0x65, 0x6d, 0x65, 0x6e, 0x74, 0x20, 0x4d, 0x65, 0x6e, 0x75, 0x0, // @275 "Single Measurement Menu"
    0x46, 0x72, 0x65, 0x71, 0x75, 0x65, 0x6e, 0x63, 0x79, 0x3a, 0x20, 0x2, 0x20, 0x48, 0x7a, 0x0, // @299 "Frequency: <> Hz"
    0x44, 0x69, 0x73, 0x74, 0x61, 0x6e, 0x63, 0x65, 0x3a, 0x20, 0x2, 0x20, 0x6d, 0x6d, 0x0, // @315 "Distance: <> mm"
    0x62, 0x79, 0x20, 0x41, 0x6c, 0x65, 0x6a, 0x61, 0x6e, 0x64, 0x72, 0x6f, 0x20, 0x26, 0x20, 0x54, 0x69, 0x6d, 0x6f, 0x0, // @330 "by Alejandro & Timo"
    0x43, 0x75, 0x72, 0x72, 0x65, 0x6e, 0x74, 0x3a, 0x20, 0x2, 0x20, 0x41, 0x0, // @350 "Current: <> A"
    0x41, 0x75, 0x74, 0x6f, 0x20, 0x6f, 0x66, 0x66, 0x3a, 0x20, 0x2, 0x0, // @363 "Auto off: <>"
    0x31, 0x30, 0x30, 0x20, 0x6d, 0x6d, 0x3a, 0x20, 0x2, 0x0, // @375 "100 mm: <>"
    0x31, 0x30, 0x20, 0x6d, 0x6d, 0x3a, 0x20, 0x2, 0x0, // @385 "10 mm: <>"
    0x35, 0x30, 0x20, 0x6d, 0x6d, 0x3a, 0x20, 0x2, 0x0, // @394 "50 mm: <>"
    0x41, 0x62, 0x6f, 0x72, 0x74, 0x20, 0x26, 0x20, 0x52, 0x65, 0x74, 0x75, 0x72, 0x6e, 0x0, // @403 "Abort & Return"
    0x43, 0x61, 0x62, 0x6c, 0x65, 0x2d, 0x4d, 0x6f, 0x6e, 0x69, 0x74, 0x6f, 0x72, 0x0, // @418 "Cable-Monitor"
    0x50, 0x72, 0x6f, 0x6a, 0x65, 0x63, 0x74, 0x20, 0x49, 0x6e, 0x66, 0x6f, 0x0, // @432 "Project Info"
    0x43, 0x61, 0x6c, 0x69, 0x62, 0x72, 0x61, 0x74, 0x69, 0x6f, 0x6e, 0x0, // @445 "Calibration"
    0x48, 0x61, 0x6c, 0x6c, 0x2d, 0x53, 0x65, 0x6e, 0x73, 0x6f, 0x72, 0x0, // @457 "Hall-Sensor"
    0x4d, 0x65, 0x61, 0x73, 0x75, 0x72, 0x65, 0x6d, 0x65, 0x6e, 0x74, 0x0, // @469 "Measurement"
    0x52, 0x65, 0x74, 0x75, 0x72, 0x6e, 0x20, 0x48, 0x6f, 0x6d, 0x65, 0x0, // @481 "Return Home"
    0x31, 0x20, 0x2d, 0x20, 0x50, 0x68, 0x61, 0x73, 0x65, 0x0, // @493 "1 - Phase"
    0x33, 0x20, 0x2d, 0x20, 0x50, 0x68, 0x61, 0x73, 0x65, 0x0, // @503 "3 - Phase"
    0x4d, 0x61, 0x69, 0x6e, 0x20, 0x4d, 0x65, 0x6e, 0x75, 0x0, // @513 "Main Menu"
    0x52, 0x69, 0x67, 0x68, 0x74, 0x20, 0x50, 0x61, 0x64, 0x0, // @523 "Right Pad"
    0x41, 0x63, 0x63, 0x75, 0x72, 0x61, 0x74, 0x65, 0x0, // @533 "Accurate"
    0x4c, 0x65, 0x66, 0x74, 0x20, 0x50, 0x61, 0x64, 0x0, // @542 "Left Pad"
    0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x0, // @551 "0000000"
    0x30, 0x30, 0x30, 0x2e, 0x30, 0x30, 0x0, // @559 "000.00"
    0x53, 0x69, 0x6e, 0x67, 0x6c, 0x65, 0x0, // @566 "Single"
    0x2d, 0x39, 0x30, 0xb0, 0x0, // @573 "-90?"
    0x30, 0x2e, 0x30, 0x0, // @578 "0.0"
    0x36, 0x30, 0x0 // @582 "60"
};

TEXT_LOCATION_FLASH_PRAGMA
KEEP extern const uint32_t indicesGb[] TEXT_LOCATION_FLASH_ATTRIBUTE;

// Array holding dynamically installed languages
struct TranslationHeader
{
    uint32_t offset_to_texts;
    uint32_t offset_to_indices;
    uint32_t offset_to_typedtext;
};
static const TranslationHeader* languagesArray[1] = { 0 };

// Compiled and linked in languages
static const uint32_t* const staticLanguageIndices[] = {
    indicesGb
};

touchgfx::LanguageId touchgfx::Texts::currentLanguage = static_cast<touchgfx::LanguageId>(0);
static const touchgfx::Unicode::UnicodeChar* currentLanguagePtr = 0;
static const uint32_t* currentLanguageIndices = 0;

void touchgfx::Texts::setLanguage(touchgfx::LanguageId id)
{
    const touchgfx::TypedText::TypedTextData* currentLanguageTypedText = 0;
    if (id < 1)
    {
        if (languagesArray[id] != 0)
        {
            // Dynamic translation is added
            const TranslationHeader* translation = languagesArray[id];
            currentLanguagePtr = (const touchgfx::Unicode::UnicodeChar*)(((const uint8_t*)translation) + translation->offset_to_texts);
            currentLanguageIndices = (const uint32_t*)(((const uint8_t*)translation) + translation->offset_to_indices);
            currentLanguageTypedText = (const touchgfx::TypedText::TypedTextData*)(((const uint8_t*)translation) + translation->offset_to_typedtext);
        }
        else
        {
            // Compiled and linked in languages
            currentLanguagePtr = texts_all_languages;
            currentLanguageIndices = staticLanguageIndices[id];
            currentLanguageTypedText = typedTextDatabaseArray[id];
        }
    }

    if (currentLanguageTypedText)
    {
        currentLanguage = id;
        touchgfx::TypedText::registerTypedTextDatabase(currentLanguageTypedText,
                                                       TypedTextDatabase::getFonts(), TypedTextDatabase::getInstanceSize());
    }
}

void touchgfx::Texts::setTranslation(touchgfx::LanguageId id, const void* translation)
{
    languagesArray[id] = (const TranslationHeader*)translation;
}

const touchgfx::Unicode::UnicodeChar* touchgfx::Texts::getText(TypedTextId id) const
{
    return &currentLanguagePtr[currentLanguageIndices[id]];
}
