// 4.22.1 0xf6693442
// Generated by imageconverter. Please, do not edit!

#include <images/BitmapDatabase.hpp>
#include <touchgfx/Bitmap.hpp>

extern const unsigned char image_alternate_theme_images_widgets_button_icon_round_micro_outline_normal[]; // BITMAP_ALTERNATE_THEME_IMAGES_WIDGETS_BUTTON_ICON_ROUND_MICRO_OUTLINE_NORMAL_ID = 0, Size: 36x36 pixels
extern const unsigned char image_alternate_theme_images_widgets_button_icon_round_micro_outline_pressed[]; // BITMAP_ALTERNATE_THEME_IMAGES_WIDGETS_BUTTON_ICON_ROUND_MICRO_OUTLINE_PRESSED_ID = 1, Size: 36x36 pixels
extern const unsigned char image_alternate_theme_images_widgets_button_regular_height_50_small_round_normal[]; // BITMAP_ALTERNATE_THEME_IMAGES_WIDGETS_BUTTON_REGULAR_HEIGHT_50_SMALL_ROUND_NORMAL_ID = 2, Size: 175x50 pixels
extern const unsigned char image_alternate_theme_images_widgets_button_regular_height_50_small_round_pressed[]; // BITMAP_ALTERNATE_THEME_IMAGES_WIDGETS_BUTTON_REGULAR_HEIGHT_50_SMALL_ROUND_PRESSED_ID = 3, Size: 175x50 pixels
extern const unsigned char image_alternate_theme_images_widgets_gauge_small_backgrounds_light_precision[]; // BITMAP_ALTERNATE_THEME_IMAGES_WIDGETS_GAUGE_SMALL_BACKGROUNDS_LIGHT_PRECISION_ID = 4, Size: 184x184 pixels
extern const unsigned char image_alternate_theme_images_widgets_gauge_small_needles_rough[]; // BITMAP_ALTERNATE_THEME_IMAGES_WIDGETS_GAUGE_SMALL_NEEDLES_ROUGH_ID = 5, Size: 16x62 pixels
extern const unsigned char image_background_2_resized_4[]; // BITMAP_BACKGROUND_2_RESIZED_4_ID = 6, Size: 240x320 pixels
extern const unsigned char image_checkmark[]; // BITMAP_CHECKMARK_ID = 7, Size: 36x36 pixels
extern const unsigned char image_power_off_36x36[]; // BITMAP_POWER_OFF_36X36_ID = 8, Size: 36x36 pixels
extern const unsigned char image_shutdown[]; // BITMAP_SHUTDOWN_ID = 9, Size: 247x320 pixels

const touchgfx::Bitmap::BitmapData bitmap_database[] = {
    { image_alternate_theme_images_widgets_button_icon_round_micro_outline_normal, 0, 36, 36, 31, 12, 4, ((uint8_t)touchgfx::Bitmap::ARGB8888) >> 3, 12, ((uint8_t)touchgfx::Bitmap::ARGB8888) & 0x7 },
    { image_alternate_theme_images_widgets_button_icon_round_micro_outline_pressed, 0, 36, 36, 31, 12, 4, ((uint8_t)touchgfx::Bitmap::ARGB8888) >> 3, 12, ((uint8_t)touchgfx::Bitmap::ARGB8888) & 0x7 },
    { image_alternate_theme_images_widgets_button_regular_height_50_small_round_normal, 0, 175, 50, 18, 1, 139, ((uint8_t)touchgfx::Bitmap::ARGB8888) >> 3, 48, ((uint8_t)touchgfx::Bitmap::ARGB8888) & 0x7 },
    { image_alternate_theme_images_widgets_button_regular_height_50_small_round_pressed, 0, 175, 50, 18, 1, 139, ((uint8_t)touchgfx::Bitmap::ARGB8888) >> 3, 48, ((uint8_t)touchgfx::Bitmap::ARGB8888) & 0x7 },
    { image_alternate_theme_images_widgets_gauge_small_backgrounds_light_precision, 0, 184, 184, 27, 27, 130, ((uint8_t)touchgfx::Bitmap::ARGB8888) >> 3, 130, ((uint8_t)touchgfx::Bitmap::ARGB8888) & 0x7 },
    { image_alternate_theme_images_widgets_gauge_small_needles_rough, 0, 16, 62, 6, 2, 4, ((uint8_t)touchgfx::Bitmap::ARGB8888) >> 3, 47, ((uint8_t)touchgfx::Bitmap::ARGB8888) & 0x7 },
    { image_background_2_resized_4, 0, 240, 320, 0, 0, 240, ((uint8_t)touchgfx::Bitmap::RGB565) >> 3, 320, ((uint8_t)touchgfx::Bitmap::RGB565) & 0x7 },
    { image_checkmark, 0, 36, 36, 6, 6, 12, ((uint8_t)touchgfx::Bitmap::ARGB8888) >> 3, 9, ((uint8_t)touchgfx::Bitmap::ARGB8888) & 0x7 },
    { image_power_off_36x36, 0, 36, 36, 12, 17, 12, ((uint8_t)touchgfx::Bitmap::ARGB8888) >> 3, 7, ((uint8_t)touchgfx::Bitmap::ARGB8888) & 0x7 },
    { image_shutdown, 0, 247, 320, 0, 0, 247, ((uint8_t)touchgfx::Bitmap::RGB565) >> 3, 320, ((uint8_t)touchgfx::Bitmap::RGB565) & 0x7 }
};

namespace BitmapDatabase
{
const touchgfx::Bitmap::BitmapData* getInstance()
{
    return bitmap_database;
}

uint16_t getInstanceSize()
{
    return (uint16_t)(sizeof(bitmap_database) / sizeof(touchgfx::Bitmap::BitmapData));
}
} // namespace BitmapDatabase
