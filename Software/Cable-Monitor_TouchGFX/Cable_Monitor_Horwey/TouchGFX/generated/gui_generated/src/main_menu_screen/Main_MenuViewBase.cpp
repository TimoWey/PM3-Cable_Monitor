/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#include <gui_generated/main_menu_screen/Main_MenuViewBase.hpp>
#include <touchgfx/canvas_widget_renderer/CanvasWidgetRenderer.hpp>
#include <touchgfx/Color.hpp>
#include <images/BitmapDatabase.hpp>
#include <texts/TextKeysAndLanguages.hpp>

Main_MenuViewBase::Main_MenuViewBase() :
    buttonCallback(this, &Main_MenuViewBase::buttonCallbackHandler)
{
    touchgfx::CanvasWidgetRenderer::setupBuffer(canvasBuffer, CANVAS_BUFFER_SIZE);
    
    __background.setPosition(0, 0, 240, 320);
    __background.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    add(__background);

    image1.setXY(0, 0);
    image1.setBitmap(touchgfx::Bitmap(BITMAP_BACKGROUND_2_RESIZED_4_ID));
    add(image1);

    line1.setPosition(0, 50, 240, 10);
    line1Painter.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    line1.setPainter(line1Painter);
    line1.setStart(5, 5);
    line1.setEnd(235, 5);
    line1.setLineWidth(1);
    line1.setLineEndingStyle(touchgfx::Line::ROUND_CAP_ENDING);
    add(line1);

    textArea2.setXY(69, 36);
    textArea2.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    textArea2.setLinespacing(0);
    textArea2.setTypedText(touchgfx::TypedText(T___SINGLEUSE_6D7Z));
    add(textArea2);

    textArea1.setXY(50, 12);
    textArea1.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    textArea1.setLinespacing(0);
    textArea1.setTypedText(touchgfx::TypedText(T___SINGLEUSE_9K1W));
    add(textArea1);

    buttonWithLabel3.setXY(33, 240);
    buttonWithLabel3.setBitmaps(touchgfx::Bitmap(BITMAP_ALTERNATE_THEME_IMAGES_WIDGETS_BUTTON_REGULAR_HEIGHT_50_SMALL_ROUND_PRESSED_ID), touchgfx::Bitmap(BITMAP_ALTERNATE_THEME_IMAGES_WIDGETS_BUTTON_REGULAR_HEIGHT_50_SMALL_ROUND_NORMAL_ID));
    buttonWithLabel3.setLabelText(touchgfx::TypedText(T___SINGLEUSE_WFCV));
    buttonWithLabel3.setLabelColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    buttonWithLabel3.setLabelColorPressed(touchgfx::Color::getColorFromRGB(255, 255, 255));
    buttonWithLabel3.setAction(buttonCallback);
    add(buttonWithLabel3);

    buttonWithLabel2.setXY(33, 170);
    buttonWithLabel2.setBitmaps(touchgfx::Bitmap(BITMAP_ALTERNATE_THEME_IMAGES_WIDGETS_BUTTON_REGULAR_HEIGHT_50_SMALL_ROUND_PRESSED_ID), touchgfx::Bitmap(BITMAP_ALTERNATE_THEME_IMAGES_WIDGETS_BUTTON_REGULAR_HEIGHT_50_SMALL_ROUND_NORMAL_ID));
    buttonWithLabel2.setLabelText(touchgfx::TypedText(T___SINGLEUSE_6X9O));
    buttonWithLabel2.setLabelColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    buttonWithLabel2.setLabelColorPressed(touchgfx::Color::getColorFromRGB(255, 255, 255));
    buttonWithLabel2.setAction(buttonCallback);
    add(buttonWithLabel2);

    buttonWithLabel1.setXY(33, 100);
    buttonWithLabel1.setBitmaps(touchgfx::Bitmap(BITMAP_ALTERNATE_THEME_IMAGES_WIDGETS_BUTTON_REGULAR_HEIGHT_50_SMALL_ROUND_PRESSED_ID), touchgfx::Bitmap(BITMAP_ALTERNATE_THEME_IMAGES_WIDGETS_BUTTON_REGULAR_HEIGHT_50_SMALL_ROUND_NORMAL_ID));
    buttonWithLabel1.setLabelText(touchgfx::TypedText(T___SINGLEUSE_8673));
    buttonWithLabel1.setLabelColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    buttonWithLabel1.setLabelColorPressed(touchgfx::Color::getColorFromRGB(255, 255, 255));
    buttonWithLabel1.setAction(buttonCallback);
    add(buttonWithLabel1);

    buttonWithIcon1.setXY(190, 12);
    buttonWithIcon1.setBitmaps(touchgfx::Bitmap(BITMAP_ALTERNATE_THEME_IMAGES_WIDGETS_BUTTON_ICON_ROUND_MICRO_OUTLINE_NORMAL_ID), touchgfx::Bitmap(BITMAP_ALTERNATE_THEME_IMAGES_WIDGETS_BUTTON_ICON_ROUND_MICRO_OUTLINE_PRESSED_ID), touchgfx::Bitmap(BITMAP_POWER_OFF_36X36_ID), touchgfx::Bitmap(BITMAP_POWER_OFF_36X36_ID));
    buttonWithIcon1.setIconXY(0, 0);
    buttonWithIcon1.setAction(buttonCallback);
    add(buttonWithIcon1);
}

Main_MenuViewBase::~Main_MenuViewBase()
{
    touchgfx::CanvasWidgetRenderer::resetBuffer();
}

void Main_MenuViewBase::setupScreen()
{

}

void Main_MenuViewBase::buttonCallbackHandler(const touchgfx::AbstractButton& src)
{
    if (&src == &buttonWithLabel1)
    {
        //Interaction1
        //When buttonWithLabel1 clicked change screen to Measurement
        //Go to Measurement with screen transition towards East
        application().gotoMeasurementScreenWipeTransitionEast();
    }
    if (&src == &buttonWithLabel2)
    {
        //Interaction2
        //When buttonWithLabel2 clicked change screen to Calibration
        //Go to Calibration with screen transition towards East
        application().gotoCalibrationScreenWipeTransitionEast();
    }
    if (&src == &buttonWithLabel3)
    {
        //Interaction3
        //When buttonWithLabel3 clicked change screen to Project_Info
        //Go to Project_Info with screen transition towards East
        application().gotoProject_InfoScreenWipeTransitionEast();
    }
    if (&src == &buttonWithIcon1)
    {
        //Interaction4
        //When buttonWithIcon1 clicked call virtual function
        //Call Device_off
        Device_off();
    }
}
