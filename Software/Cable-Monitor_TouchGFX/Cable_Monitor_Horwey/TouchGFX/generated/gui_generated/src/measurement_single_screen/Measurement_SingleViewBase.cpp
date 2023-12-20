/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#include <gui_generated/measurement_single_screen/Measurement_SingleViewBase.hpp>
#include <touchgfx/canvas_widget_renderer/CanvasWidgetRenderer.hpp>
#include <touchgfx/Color.hpp>
#include <images/BitmapDatabase.hpp>
#include <texts/TextKeysAndLanguages.hpp>

Measurement_SingleViewBase::Measurement_SingleViewBase() :
    buttonCallback(this, &Measurement_SingleViewBase::buttonCallbackHandler)
{
    touchgfx::CanvasWidgetRenderer::setupBuffer(canvasBuffer, CANVAS_BUFFER_SIZE);
    
    __background.setPosition(0, 0, 240, 320);
    __background.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    add(__background);

    image_background.setXY(0, 0);
    image_background.setBitmap(touchgfx::Bitmap(BITMAP_BACKGROUND_2_RESIZED_4_ID));
    add(image_background);

    textArea_auto_off.setXY(86, 308);
    textArea_auto_off.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    textArea_auto_off.setLinespacing(0);
    Unicode::snprintf(textArea_auto_offBuffer, TEXTAREA_AUTO_OFF_SIZE, "%s", touchgfx::TypedText(T___SINGLEUSE_DTDC).getText());
    textArea_auto_off.setWildcard(textArea_auto_offBuffer);
    textArea_auto_off.resizeToCurrentText();
    textArea_auto_off.setTypedText(touchgfx::TypedText(T___SINGLEUSE_VDD5));
    add(textArea_auto_off);

    buttonWithLabel_Return.setXY(33, 240);
    buttonWithLabel_Return.setBitmaps(touchgfx::Bitmap(BITMAP_ALTERNATE_THEME_IMAGES_WIDGETS_BUTTON_REGULAR_HEIGHT_50_SMALL_ROUND_PRESSED_ID), touchgfx::Bitmap(BITMAP_ALTERNATE_THEME_IMAGES_WIDGETS_BUTTON_REGULAR_HEIGHT_50_SMALL_ROUND_NORMAL_ID));
    buttonWithLabel_Return.setLabelText(touchgfx::TypedText(T___SINGLEUSE_O699));
    buttonWithLabel_Return.setLabelColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    buttonWithLabel_Return.setLabelColorPressed(touchgfx::Color::getColorFromRGB(255, 255, 255));
    buttonWithLabel_Return.setAction(buttonCallback);
    add(buttonWithLabel_Return);

    buttonWithLabel_3Phase.setXY(33, 170);
    buttonWithLabel_3Phase.setBitmaps(touchgfx::Bitmap(BITMAP_ALTERNATE_THEME_IMAGES_WIDGETS_BUTTON_REGULAR_HEIGHT_50_SMALL_ROUND_PRESSED_ID), touchgfx::Bitmap(BITMAP_ALTERNATE_THEME_IMAGES_WIDGETS_BUTTON_REGULAR_HEIGHT_50_SMALL_ROUND_NORMAL_ID));
    buttonWithLabel_3Phase.setLabelText(touchgfx::TypedText(T___SINGLEUSE_3S2P));
    buttonWithLabel_3Phase.setLabelColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    buttonWithLabel_3Phase.setLabelColorPressed(touchgfx::Color::getColorFromRGB(255, 255, 255));
    buttonWithLabel_3Phase.setAction(buttonCallback);
    add(buttonWithLabel_3Phase);

    buttonWithLabel_1Phase.setXY(33, 100);
    buttonWithLabel_1Phase.setBitmaps(touchgfx::Bitmap(BITMAP_ALTERNATE_THEME_IMAGES_WIDGETS_BUTTON_REGULAR_HEIGHT_50_SMALL_ROUND_PRESSED_ID), touchgfx::Bitmap(BITMAP_ALTERNATE_THEME_IMAGES_WIDGETS_BUTTON_REGULAR_HEIGHT_50_SMALL_ROUND_NORMAL_ID));
    buttonWithLabel_1Phase.setLabelText(touchgfx::TypedText(T___SINGLEUSE_RPQK));
    buttonWithLabel_1Phase.setLabelColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    buttonWithLabel_1Phase.setLabelColorPressed(touchgfx::Color::getColorFromRGB(255, 255, 255));
    buttonWithLabel_1Phase.setAction(buttonCallback);
    add(buttonWithLabel_1Phase);

    line2.setPosition(0, 75, 240, 10);
    line2Painter.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    line2.setPainter(line2Painter);
    line2.setStart(5, 5);
    line2.setEnd(235, 5);
    line2.setLineWidth(1);
    line2.setLineEndingStyle(touchgfx::Line::ROUND_CAP_ENDING);
    add(line2);

    textArea_menu.setXY(41, 60);
    textArea_menu.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    textArea_menu.setLinespacing(0);
    textArea_menu.setTypedText(touchgfx::TypedText(T___SINGLEUSE_1QNY));
    add(textArea_menu);

    line1.setPosition(0, 50, 240, 10);
    line1Painter.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    line1.setPainter(line1Painter);
    line1.setStart(5, 5);
    line1.setEnd(235, 5);
    line1.setLineWidth(1);
    line1.setLineEndingStyle(touchgfx::Line::ROUND_CAP_ENDING);
    add(line1);

    textArea_name.setXY(69, 35);
    textArea_name.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    textArea_name.setLinespacing(0);
    textArea_name.setTypedText(touchgfx::TypedText(T___SINGLEUSE_T0FJ));
    add(textArea_name);

    textArea_title.setXY(54, 12);
    textArea_title.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    textArea_title.setLinespacing(0);
    textArea_title.setTypedText(touchgfx::TypedText(T___SINGLEUSE_3BUV));
    add(textArea_title);
}

Measurement_SingleViewBase::~Measurement_SingleViewBase()
{
    touchgfx::CanvasWidgetRenderer::resetBuffer();
}

void Measurement_SingleViewBase::setupScreen()
{

}

void Measurement_SingleViewBase::buttonCallbackHandler(const touchgfx::AbstractButton& src)
{
    if (&src == &buttonWithLabel_Return)
    {
        //Interaction1
        //When buttonWithLabel_Return clicked change screen to Measurement
        //Go to Measurement with screen transition towards West
        application().gotoMeasurementScreenWipeTransitionWest();
    }
    if (&src == &buttonWithLabel_1Phase)
    {
        //Interaction2
        //When buttonWithLabel_1Phase clicked change screen to Measurement_Single_Display_1P
        //Go to Measurement_Single_Display_1P with screen transition towards East
        application().gotoMeasurement_Single_Display_1PScreenWipeTransitionEast();
    }
    if (&src == &buttonWithLabel_3Phase)
    {
        //Interaction3
        //When buttonWithLabel_3Phase clicked change screen to Measurement_Single_Display_3P
        //Go to Measurement_Single_Display_3P with screen transition towards East
        application().gotoMeasurement_Single_Display_3PScreenWipeTransitionEast();
    }
}
