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

    image_background.setXY(0, 0);
    image_background.setBitmap(touchgfx::Bitmap(BITMAP_BACKGROUND_2_RESIZED_4_ID));
    add(image_background);

    textArea_auto_off.setXY(86, 308);
    textArea_auto_off.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    textArea_auto_off.setLinespacing(0);
    Unicode::snprintf(textArea_auto_offBuffer, TEXTAREA_AUTO_OFF_SIZE, "%s", touchgfx::TypedText(T___SINGLEUSE_5C9S).getText());
    textArea_auto_off.setWildcard(textArea_auto_offBuffer);
    textArea_auto_off.resizeToCurrentText();
    textArea_auto_off.setTypedText(touchgfx::TypedText(T___SINGLEUSE_KYIO));
    add(textArea_auto_off);

    buttonWithLabel_Return.setXY(33, 240);
    buttonWithLabel_Return.setBitmaps(touchgfx::Bitmap(BITMAP_ALTERNATE_THEME_IMAGES_WIDGETS_BUTTON_REGULAR_HEIGHT_50_SMALL_ROUND_PRESSED_ID), touchgfx::Bitmap(BITMAP_ALTERNATE_THEME_IMAGES_WIDGETS_BUTTON_REGULAR_HEIGHT_50_SMALL_ROUND_NORMAL_ID));
    buttonWithLabel_Return.setLabelText(touchgfx::TypedText(T___SINGLEUSE_VQIQ));
    buttonWithLabel_Return.setLabelColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    buttonWithLabel_Return.setLabelColorPressed(touchgfx::Color::getColorFromRGB(255, 255, 255));
    buttonWithLabel_Return.setAction(buttonCallback);
    add(buttonWithLabel_Return);

    textArea_Info.setXY(7, 91);
    textArea_Info.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    textArea_Info.setLinespacing(0);
    textArea_Info.setTypedText(touchgfx::TypedText(T___SINGLEUSE_9J9T));
    add(textArea_Info);

    line2.setPosition(0, 75, 240, 10);
    line2Painter.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    line2.setPainter(line2Painter);
    line2.setStart(5, 5);
    line2.setEnd(235, 5);
    line2.setLineWidth(1);
    line2.setLineEndingStyle(touchgfx::Line::ROUND_CAP_ENDING);
    add(line2);

    textArea_menu.setXY(67, 60);
    textArea_menu.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    textArea_menu.setLinespacing(0);
    textArea_menu.setTypedText(touchgfx::TypedText(T___SINGLEUSE_BYJD));
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
    textArea_name.setTypedText(touchgfx::TypedText(T___SINGLEUSE_8N0V));
    add(textArea_name);

    textArea_title.setXY(54, 12);
    textArea_title.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    textArea_title.setLinespacing(0);
    textArea_title.setTypedText(touchgfx::TypedText(T___SINGLEUSE_SSFQ));
    add(textArea_title);
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
    if (&src == &buttonWithLabel_Return)
    {
        //Interaction1
        //When buttonWithLabel_Return clicked change screen to Main_Menu
        //Go to Main_Menu with screen transition towards West
        application().gotoMain_MenuScreenWipeTransitionWest();
    }
}
