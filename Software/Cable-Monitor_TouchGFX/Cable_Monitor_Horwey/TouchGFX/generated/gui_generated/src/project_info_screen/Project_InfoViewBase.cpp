/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#include <gui_generated/project_info_screen/Project_InfoViewBase.hpp>
#include <touchgfx/canvas_widget_renderer/CanvasWidgetRenderer.hpp>
#include <touchgfx/Color.hpp>
#include <images/BitmapDatabase.hpp>
#include <texts/TextKeysAndLanguages.hpp>

Project_InfoViewBase::Project_InfoViewBase() :
    buttonCallback(this, &Project_InfoViewBase::buttonCallbackHandler)
{
    touchgfx::CanvasWidgetRenderer::setupBuffer(canvasBuffer, CANVAS_BUFFER_SIZE);
    
    __background.setPosition(0, 0, 240, 320);
    __background.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    add(__background);

    image1.setXY(0, 0);
    image1.setBitmap(touchgfx::Bitmap(BITMAP_BACKGROUND_2_RESIZED_4_ID));
    add(image1);

    textArea3_1.setXY(86, 308);
    textArea3_1.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    textArea3_1.setLinespacing(0);
    Unicode::snprintf(textArea3_1Buffer, TEXTAREA3_1_SIZE, "%s", touchgfx::TypedText(T___SINGLEUSE_5C9S).getText());
    textArea3_1.setWildcard(textArea3_1Buffer);
    textArea3_1.resizeToCurrentText();
    textArea3_1.setTypedText(touchgfx::TypedText(T___SINGLEUSE_KYIO));
    add(textArea3_1);

    line1.setPosition(0, 50, 240, 10);
    line1Painter.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    line1.setPainter(line1Painter);
    line1.setStart(5, 5);
    line1.setEnd(235, 5);
    line1.setLineWidth(1);
    line1.setLineEndingStyle(touchgfx::Line::ROUND_CAP_ENDING);
    add(line1);

    buttonWithLabel3.setXY(33, 240);
    buttonWithLabel3.setBitmaps(touchgfx::Bitmap(BITMAP_ALTERNATE_THEME_IMAGES_WIDGETS_BUTTON_REGULAR_HEIGHT_50_SMALL_ROUND_PRESSED_ID), touchgfx::Bitmap(BITMAP_ALTERNATE_THEME_IMAGES_WIDGETS_BUTTON_REGULAR_HEIGHT_50_SMALL_ROUND_NORMAL_ID));
    buttonWithLabel3.setLabelText(touchgfx::TypedText(T___SINGLEUSE_VQIQ));
    buttonWithLabel3.setLabelColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    buttonWithLabel3.setLabelColorPressed(touchgfx::Color::getColorFromRGB(255, 255, 255));
    buttonWithLabel3.setAction(buttonCallback);
    add(buttonWithLabel3);

    textArea3.setXY(5, 91);
    textArea3.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    textArea3.setLinespacing(0);
    textArea3.setTypedText(touchgfx::TypedText(T___SINGLEUSE_9J9T));
    add(textArea3);

    textArea2.setXY(69, 36);
    textArea2.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    textArea2.setLinespacing(0);
    textArea2.setTypedText(touchgfx::TypedText(T___SINGLEUSE_8N0V));
    add(textArea2);

    textArea1.setXY(50, 12);
    textArea1.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    textArea1.setLinespacing(0);
    textArea1.setTypedText(touchgfx::TypedText(T___SINGLEUSE_SSFQ));
    add(textArea1);
}

Project_InfoViewBase::~Project_InfoViewBase()
{
    touchgfx::CanvasWidgetRenderer::resetBuffer();
}

void Project_InfoViewBase::setupScreen()
{

}

void Project_InfoViewBase::buttonCallbackHandler(const touchgfx::AbstractButton& src)
{
    if (&src == &buttonWithLabel3)
    {
        //Interaction1
        //When buttonWithLabel3 clicked change screen to Main_Menu
        //Go to Main_Menu with screen transition towards West
        application().gotoMain_MenuScreenWipeTransitionWest();
    }
}
