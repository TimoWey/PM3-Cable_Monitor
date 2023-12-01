/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#include <gui_generated/measurement_accurate_display_screen/Measurement_Accurate_DisplayViewBase.hpp>
#include <touchgfx/canvas_widget_renderer/CanvasWidgetRenderer.hpp>
#include <touchgfx/Color.hpp>
#include <images/BitmapDatabase.hpp>
#include <texts/TextKeysAndLanguages.hpp>

Measurement_Accurate_DisplayViewBase::Measurement_Accurate_DisplayViewBase() :
    buttonCallback(this, &Measurement_Accurate_DisplayViewBase::buttonCallbackHandler)
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
    textArea2.setTypedText(touchgfx::TypedText(T___SINGLEUSE_YCWF));
    add(textArea2);

    textArea1.setXY(50, 12);
    textArea1.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    textArea1.setLinespacing(0);
    textArea1.setTypedText(touchgfx::TypedText(T___SINGLEUSE_7ZBX));
    add(textArea1);

    buttonWithLabel3.setXY(33, 240);
    buttonWithLabel3.setBitmaps(touchgfx::Bitmap(BITMAP_ALTERNATE_THEME_IMAGES_WIDGETS_BUTTON_REGULAR_HEIGHT_50_SMALL_ROUND_PRESSED_ID), touchgfx::Bitmap(BITMAP_ALTERNATE_THEME_IMAGES_WIDGETS_BUTTON_REGULAR_HEIGHT_50_SMALL_ROUND_NORMAL_ID));
    buttonWithLabel3.setLabelText(touchgfx::TypedText(T___SINGLEUSE_ZXHY));
    buttonWithLabel3.setLabelColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    buttonWithLabel3.setLabelColorPressed(touchgfx::Color::getColorFromRGB(255, 255, 255));
    buttonWithLabel3.setAction(buttonCallback);
    add(buttonWithLabel3);

    gauge1.setBackground(touchgfx::Bitmap(BITMAP_ALTERNATE_THEME_IMAGES_WIDGETS_GAUGE_TINY_BACKGROUNDS_DARK_ID));
    gauge1.setPosition(56, 69, 120, 120);
    gauge1.setCenter(60, 60);
    gauge1.setStartEndAngle(-90, 90);
    gauge1.setRange(0, 100);
    gauge1.setValue(50);
    gauge1.setNeedle(BITMAP_ALTERNATE_THEME_IMAGES_WIDGETS_GAUGE_TINY_NEEDLES_ROUGH_ID, 5, 33);
    gauge1.setMovingNeedleRenderingAlgorithm(touchgfx::TextureMapper::BILINEAR_INTERPOLATION);
    gauge1.setSteadyNeedleRenderingAlgorithm(touchgfx::TextureMapper::BILINEAR_INTERPOLATION);
    add(gauge1);
}

Measurement_Accurate_DisplayViewBase::~Measurement_Accurate_DisplayViewBase()
{
    touchgfx::CanvasWidgetRenderer::resetBuffer();
}

void Measurement_Accurate_DisplayViewBase::setupScreen()
{

}

void Measurement_Accurate_DisplayViewBase::buttonCallbackHandler(const touchgfx::AbstractButton& src)
{
    if (&src == &buttonWithLabel3)
    {
        //Interaction1
        //When buttonWithLabel3 clicked change screen to Measurement_Single
        //Go to Measurement_Single with screen transition towards West
        application().gotoMeasurement_SingleScreenSlideTransitionWest();
    }
}
