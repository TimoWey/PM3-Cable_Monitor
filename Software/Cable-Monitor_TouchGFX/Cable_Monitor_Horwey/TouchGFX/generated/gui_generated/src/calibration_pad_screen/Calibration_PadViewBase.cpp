/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#include <gui_generated/calibration_pad_screen/Calibration_PadViewBase.hpp>
#include <touchgfx/canvas_widget_renderer/CanvasWidgetRenderer.hpp>
#include <touchgfx/Color.hpp>
#include <images/BitmapDatabase.hpp>
#include <texts/TextKeysAndLanguages.hpp>

Calibration_PadViewBase::Calibration_PadViewBase() :
    buttonCallback(this, &Calibration_PadViewBase::buttonCallbackHandler)
{
    touchgfx::CanvasWidgetRenderer::setupBuffer(canvasBuffer, CANVAS_BUFFER_SIZE);
    
    __background.setPosition(0, 0, 240, 320);
    __background.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    add(__background);

    image1.setXY(0, 0);
    image1.setBitmap(touchgfx::Bitmap(BITMAP_BACKGROUND_2_RESIZED_4_ID));
    add(image1);

    buttonWithLabel3.setXY(33, 257);
    buttonWithLabel3.setBitmaps(touchgfx::Bitmap(BITMAP_ALTERNATE_THEME_IMAGES_WIDGETS_BUTTON_REGULAR_HEIGHT_50_SMALL_ROUND_PRESSED_ID), touchgfx::Bitmap(BITMAP_ALTERNATE_THEME_IMAGES_WIDGETS_BUTTON_REGULAR_HEIGHT_50_SMALL_ROUND_NORMAL_ID));
    buttonWithLabel3.setLabelText(touchgfx::TypedText(T___SINGLEUSE_ZZKI));
    buttonWithLabel3.setLabelColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    buttonWithLabel3.setLabelColorPressed(touchgfx::Color::getColorFromRGB(255, 255, 255));
    buttonWithLabel3.setAction(buttonCallback);
    add(buttonWithLabel3);

    textArea3.setXY(58, 60);
    textArea3.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    textArea3.setLinespacing(0);
    textArea3.setTypedText(touchgfx::TypedText(T___SINGLEUSE_X786));
    add(textArea3);

    line1.setPosition(0, 50, 240, 10);
    line1Painter.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    line1.setPainter(line1Painter);
    line1.setStart(5, 5);
    line1.setEnd(235, 5);
    line1.setLineWidth(1);
    line1.setLineEndingStyle(touchgfx::Line::ROUND_CAP_ENDING);
    add(line1);

    textArea2.setXY(69, 35);
    textArea2.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    textArea2.setLinespacing(0);
    textArea2.setTypedText(touchgfx::TypedText(T___SINGLEUSE_FJID));
    add(textArea2);

    textArea1.setXY(54, 12);
    textArea1.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    textArea1.setLinespacing(0);
    textArea1.setTypedText(touchgfx::TypedText(T___SINGLEUSE_EAAK));
    add(textArea1);
}

Calibration_PadViewBase::~Calibration_PadViewBase()
{
    touchgfx::CanvasWidgetRenderer::resetBuffer();
}

void Calibration_PadViewBase::setupScreen()
{

}

void Calibration_PadViewBase::buttonCallbackHandler(const touchgfx::AbstractButton& src)
{
    if (&src == &buttonWithLabel3)
    {
        //Interaction1
        //When buttonWithLabel3 clicked change screen to Calibration
        //Go to Calibration with screen transition towards West
        application().gotoCalibrationScreenWipeTransitionWest();
    }
}
