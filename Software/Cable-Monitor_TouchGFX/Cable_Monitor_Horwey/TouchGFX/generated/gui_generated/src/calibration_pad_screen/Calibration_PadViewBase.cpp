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

    swipeContainer1.setXY(0, 85);
    swipeContainer1.setPageIndicatorBitmaps(touchgfx::Bitmap(BITMAP_ALTERNATE_THEME_IMAGES_WIDGETS_SWIPECONTAINER_MEDIUM_OFF_NORMAL_ID), touchgfx::Bitmap(BITMAP_ALTERNATE_THEME_IMAGES_WIDGETS_SWIPECONTAINER_MEDIUM_ON_ACTIVE_ID));
    swipeContainer1.setPageIndicatorXY(80, 140);
    swipeContainer1.setSwipeCutoff(50);
    swipeContainer1.setEndSwipeElasticWidth(50);

    swipeContainerPadLeft.setWidth(240);
    swipeContainerPadLeft.setHeight(172);
    buttonWithIcon_LP3.setXY(194, 97);
    buttonWithIcon_LP3.setBitmaps(touchgfx::Bitmap(BITMAP_ALTERNATE_THEME_IMAGES_WIDGETS_BUTTON_ICON_ROUND_MICRO_OUTLINE_NORMAL_ID), touchgfx::Bitmap(BITMAP_ALTERNATE_THEME_IMAGES_WIDGETS_BUTTON_ICON_ROUND_MICRO_OUTLINE_PRESSED_ID), touchgfx::Bitmap(BITMAP_CHECKMARK_ID), touchgfx::Bitmap(BITMAP_CHECKMARK_ID));
    buttonWithIcon_LP3.setIconXY(0, 0);
    buttonWithIcon_LP3.setAction(buttonCallback);
    swipeContainerPadLeft.add(buttonWithIcon_LP3);

    buttonWithIcon_LP2.setXY(194, 61);
    buttonWithIcon_LP2.setBitmaps(touchgfx::Bitmap(BITMAP_ALTERNATE_THEME_IMAGES_WIDGETS_BUTTON_ICON_ROUND_MICRO_OUTLINE_NORMAL_ID), touchgfx::Bitmap(BITMAP_ALTERNATE_THEME_IMAGES_WIDGETS_BUTTON_ICON_ROUND_MICRO_OUTLINE_PRESSED_ID), touchgfx::Bitmap(BITMAP_CHECKMARK_ID), touchgfx::Bitmap(BITMAP_CHECKMARK_ID));
    buttonWithIcon_LP2.setIconXY(0, 0);
    buttonWithIcon_LP2.setAction(buttonCallback);
    swipeContainerPadLeft.add(buttonWithIcon_LP2);

    buttonWithIcon_LP1.setXY(194, 25);
    buttonWithIcon_LP1.setBitmaps(touchgfx::Bitmap(BITMAP_ALTERNATE_THEME_IMAGES_WIDGETS_BUTTON_ICON_ROUND_MICRO_OUTLINE_NORMAL_ID), touchgfx::Bitmap(BITMAP_ALTERNATE_THEME_IMAGES_WIDGETS_BUTTON_ICON_ROUND_MICRO_OUTLINE_PRESSED_ID), touchgfx::Bitmap(BITMAP_CHECKMARK_ID), touchgfx::Bitmap(BITMAP_CHECKMARK_ID));
    buttonWithIcon_LP1.setIconXY(0, 0);
    buttonWithIcon_LP1.setAction(buttonCallback);
    swipeContainerPadLeft.add(buttonWithIcon_LP1);

    textAreaCal_LP3.setXY(10, 104);
    textAreaCal_LP3.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    textAreaCal_LP3.setLinespacing(0);
    Unicode::snprintf(textAreaCal_LP3Buffer, TEXTAREACAL_LP3_SIZE, "%s", touchgfx::TypedText(T___SINGLEUSE_12P5).getText());
    textAreaCal_LP3.setWildcard(textAreaCal_LP3Buffer);
    textAreaCal_LP3.resizeToCurrentText();
    textAreaCal_LP3.setTypedText(touchgfx::TypedText(T_TEXTAREACAL_LH3));
    swipeContainerPadLeft.add(textAreaCal_LP3);

    textAreaCal_LP2.setXY(22, 68);
    textAreaCal_LP2.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    textAreaCal_LP2.setLinespacing(0);
    Unicode::snprintf(textAreaCal_LP2Buffer, TEXTAREACAL_LP2_SIZE, "%s", touchgfx::TypedText(T___SINGLEUSE_01G5).getText());
    textAreaCal_LP2.setWildcard(textAreaCal_LP2Buffer);
    textAreaCal_LP2.resizeToCurrentText();
    textAreaCal_LP2.setTypedText(touchgfx::TypedText(T_TEXTAREACAL_LH2));
    swipeContainerPadLeft.add(textAreaCal_LP2);

    textAreaCal_LP1.setXY(22, 32);
    textAreaCal_LP1.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    textAreaCal_LP1.setLinespacing(0);
    Unicode::snprintf(textAreaCal_LP1Buffer, TEXTAREACAL_LP1_SIZE, "%s", touchgfx::TypedText(T___SINGLEUSE_TG06).getText());
    textAreaCal_LP1.setWildcard(textAreaCal_LP1Buffer);
    textAreaCal_LP1.resizeToCurrentText();
    textAreaCal_LP1.setTypedText(touchgfx::TypedText(T_TEXTAREACAL_LH1));
    swipeContainerPadLeft.add(textAreaCal_LP1);

    line1_LP.setPosition(0, 15, 240, 10);
    line1_LPPainter.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    line1_LP.setPainter(line1_LPPainter);
    line1_LP.setStart(5, 5);
    line1_LP.setEnd(235, 5);
    line1_LP.setLineWidth(1);
    line1_LP.setLineEndingStyle(touchgfx::Line::ROUND_CAP_ENDING);
    swipeContainerPadLeft.add(line1_LP);

    textArea1_LP.setXY(96, 0);
    textArea1_LP.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    textArea1_LP.setLinespacing(0);
    textArea1_LP.setTypedText(touchgfx::TypedText(T___SINGLEUSE_Q2TU));
    swipeContainerPadLeft.add(textArea1_LP);

    swipeContainer1.add(swipeContainerPadLeft);

    swipeContainerPadRight.setWidth(240);
    swipeContainerPadRight.setHeight(172);
    buttonWithIcon_RP3.setXY(194, 97);
    buttonWithIcon_RP3.setBitmaps(touchgfx::Bitmap(BITMAP_ALTERNATE_THEME_IMAGES_WIDGETS_BUTTON_ICON_ROUND_MICRO_OUTLINE_NORMAL_ID), touchgfx::Bitmap(BITMAP_ALTERNATE_THEME_IMAGES_WIDGETS_BUTTON_ICON_ROUND_MICRO_OUTLINE_PRESSED_ID), touchgfx::Bitmap(BITMAP_CHECKMARK_ID), touchgfx::Bitmap(BITMAP_CHECKMARK_ID));
    buttonWithIcon_RP3.setIconXY(0, 0);
    buttonWithIcon_RP3.setAction(buttonCallback);
    swipeContainerPadRight.add(buttonWithIcon_RP3);

    buttonWithIcon_RP2.setXY(194, 61);
    buttonWithIcon_RP2.setBitmaps(touchgfx::Bitmap(BITMAP_ALTERNATE_THEME_IMAGES_WIDGETS_BUTTON_ICON_ROUND_MICRO_OUTLINE_NORMAL_ID), touchgfx::Bitmap(BITMAP_ALTERNATE_THEME_IMAGES_WIDGETS_BUTTON_ICON_ROUND_MICRO_OUTLINE_PRESSED_ID), touchgfx::Bitmap(BITMAP_CHECKMARK_ID), touchgfx::Bitmap(BITMAP_CHECKMARK_ID));
    buttonWithIcon_RP2.setIconXY(0, 0);
    buttonWithIcon_RP2.setAction(buttonCallback);
    swipeContainerPadRight.add(buttonWithIcon_RP2);

    buttonWithIcon_RP1.setXY(194, 25);
    buttonWithIcon_RP1.setBitmaps(touchgfx::Bitmap(BITMAP_ALTERNATE_THEME_IMAGES_WIDGETS_BUTTON_ICON_ROUND_MICRO_OUTLINE_NORMAL_ID), touchgfx::Bitmap(BITMAP_ALTERNATE_THEME_IMAGES_WIDGETS_BUTTON_ICON_ROUND_MICRO_OUTLINE_PRESSED_ID), touchgfx::Bitmap(BITMAP_CHECKMARK_ID), touchgfx::Bitmap(BITMAP_CHECKMARK_ID));
    buttonWithIcon_RP1.setIconXY(0, 0);
    buttonWithIcon_RP1.setAction(buttonCallback);
    swipeContainerPadRight.add(buttonWithIcon_RP1);

    textAreaCal_RP3.setXY(10, 104);
    textAreaCal_RP3.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    textAreaCal_RP3.setLinespacing(0);
    Unicode::snprintf(textAreaCal_RP3Buffer, TEXTAREACAL_RP3_SIZE, "%s", touchgfx::TypedText(T___SINGLEUSE_8T3Q).getText());
    textAreaCal_RP3.setWildcard(textAreaCal_RP3Buffer);
    textAreaCal_RP3.resizeToCurrentText();
    textAreaCal_RP3.setTypedText(touchgfx::TypedText(T_TEXTAREACAL_RH3));
    swipeContainerPadRight.add(textAreaCal_RP3);

    textAreaCal_RP2.setXY(22, 68);
    textAreaCal_RP2.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    textAreaCal_RP2.setLinespacing(0);
    Unicode::snprintf(textAreaCal_RP2Buffer, TEXTAREACAL_RP2_SIZE, "%s", touchgfx::TypedText(T___SINGLEUSE_NZZI).getText());
    textAreaCal_RP2.setWildcard(textAreaCal_RP2Buffer);
    textAreaCal_RP2.resizeToCurrentText();
    textAreaCal_RP2.setTypedText(touchgfx::TypedText(T_TEXTAREACAL_RH2));
    swipeContainerPadRight.add(textAreaCal_RP2);

    textAreaCal_RP1.setXY(22, 32);
    textAreaCal_RP1.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    textAreaCal_RP1.setLinespacing(0);
    Unicode::snprintf(textAreaCal_RP1Buffer, TEXTAREACAL_RP1_SIZE, "%s", touchgfx::TypedText(T___SINGLEUSE_XVN8).getText());
    textAreaCal_RP1.setWildcard(textAreaCal_RP1Buffer);
    textAreaCal_RP1.resizeToCurrentText();
    textAreaCal_RP1.setTypedText(touchgfx::TypedText(T_TEXTAREACAL_LH1));
    swipeContainerPadRight.add(textAreaCal_RP1);

    line1_RP.setPosition(0, 15, 240, 10);
    line1_RPPainter.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    line1_RP.setPainter(line1_RPPainter);
    line1_RP.setStart(5, 5);
    line1_RP.setEnd(235, 5);
    line1_RP.setLineWidth(1);
    line1_RP.setLineEndingStyle(touchgfx::Line::ROUND_CAP_ENDING);
    swipeContainerPadRight.add(line1_RP);

    textArea1_RP.setXY(92, 0);
    textArea1_RP.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    textArea1_RP.setLinespacing(0);
    textArea1_RP.setTypedText(touchgfx::TypedText(T___SINGLEUSE_L8ZM));
    swipeContainerPadRight.add(textArea1_RP);

    swipeContainer1.add(swipeContainerPadRight);

    swipeContainerHallLeft.setWidth(240);
    swipeContainerHallLeft.setHeight(172);
    buttonWithIcon_LH3.setXY(194, 97);
    buttonWithIcon_LH3.setBitmaps(touchgfx::Bitmap(BITMAP_ALTERNATE_THEME_IMAGES_WIDGETS_BUTTON_ICON_ROUND_MICRO_OUTLINE_NORMAL_ID), touchgfx::Bitmap(BITMAP_ALTERNATE_THEME_IMAGES_WIDGETS_BUTTON_ICON_ROUND_MICRO_OUTLINE_PRESSED_ID), touchgfx::Bitmap(BITMAP_CHECKMARK_ID), touchgfx::Bitmap(BITMAP_CHECKMARK_ID));
    buttonWithIcon_LH3.setIconXY(0, 0);
    buttonWithIcon_LH3.setAction(buttonCallback);
    swipeContainerHallLeft.add(buttonWithIcon_LH3);

    buttonWithIcon_LH2.setXY(194, 61);
    buttonWithIcon_LH2.setBitmaps(touchgfx::Bitmap(BITMAP_ALTERNATE_THEME_IMAGES_WIDGETS_BUTTON_ICON_ROUND_MICRO_OUTLINE_NORMAL_ID), touchgfx::Bitmap(BITMAP_ALTERNATE_THEME_IMAGES_WIDGETS_BUTTON_ICON_ROUND_MICRO_OUTLINE_PRESSED_ID), touchgfx::Bitmap(BITMAP_CHECKMARK_ID), touchgfx::Bitmap(BITMAP_CHECKMARK_ID));
    buttonWithIcon_LH2.setIconXY(0, 0);
    buttonWithIcon_LH2.setAction(buttonCallback);
    swipeContainerHallLeft.add(buttonWithIcon_LH2);

    buttonWithIcon_LH1.setXY(194, 25);
    buttonWithIcon_LH1.setBitmaps(touchgfx::Bitmap(BITMAP_ALTERNATE_THEME_IMAGES_WIDGETS_BUTTON_ICON_ROUND_MICRO_OUTLINE_NORMAL_ID), touchgfx::Bitmap(BITMAP_ALTERNATE_THEME_IMAGES_WIDGETS_BUTTON_ICON_ROUND_MICRO_OUTLINE_PRESSED_ID), touchgfx::Bitmap(BITMAP_CHECKMARK_ID), touchgfx::Bitmap(BITMAP_CHECKMARK_ID));
    buttonWithIcon_LH1.setIconXY(0, 0);
    buttonWithIcon_LH1.setAction(buttonCallback);
    swipeContainerHallLeft.add(buttonWithIcon_LH1);

    textAreaCal_LH3.setXY(10, 104);
    textAreaCal_LH3.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    textAreaCal_LH3.setLinespacing(0);
    Unicode::snprintf(textAreaCal_LH3Buffer, TEXTAREACAL_LH3_SIZE, "%s", touchgfx::TypedText(T___SINGLEUSE_4NSV).getText());
    textAreaCal_LH3.setWildcard(textAreaCal_LH3Buffer);
    textAreaCal_LH3.resizeToCurrentText();
    textAreaCal_LH3.setTypedText(touchgfx::TypedText(T_TEXTAREACAL_LH3));
    swipeContainerHallLeft.add(textAreaCal_LH3);

    textAreaCal_LH2.setXY(22, 68);
    textAreaCal_LH2.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    textAreaCal_LH2.setLinespacing(0);
    Unicode::snprintf(textAreaCal_LH2Buffer, TEXTAREACAL_LH2_SIZE, "%s", touchgfx::TypedText(T___SINGLEUSE_M8NH).getText());
    textAreaCal_LH2.setWildcard(textAreaCal_LH2Buffer);
    textAreaCal_LH2.resizeToCurrentText();
    textAreaCal_LH2.setTypedText(touchgfx::TypedText(T_TEXTAREACAL_LH2));
    swipeContainerHallLeft.add(textAreaCal_LH2);

    textAreaCal_LH1.setXY(22, 32);
    textAreaCal_LH1.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    textAreaCal_LH1.setLinespacing(0);
    Unicode::snprintf(textAreaCal_LH1Buffer, TEXTAREACAL_LH1_SIZE, "%s", touchgfx::TypedText(T___SINGLEUSE_I3S7).getText());
    textAreaCal_LH1.setWildcard(textAreaCal_LH1Buffer);
    textAreaCal_LH1.resizeToCurrentText();
    textAreaCal_LH1.setTypedText(touchgfx::TypedText(T_TEXTAREACAL_LH1));
    swipeContainerHallLeft.add(textAreaCal_LH1);

    line1_LH.setPosition(0, 15, 240, 10);
    line1_LHPainter.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    line1_LH.setPainter(line1_LHPainter);
    line1_LH.setStart(5, 5);
    line1_LH.setEnd(235, 5);
    line1_LH.setLineWidth(1);
    line1_LH.setLineEndingStyle(touchgfx::Line::ROUND_CAP_ENDING);
    swipeContainerHallLeft.add(line1_LH);

    textArea1_LH.setXY(73, 0);
    textArea1_LH.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    textArea1_LH.setLinespacing(0);
    textArea1_LH.setTypedText(touchgfx::TypedText(T___SINGLEUSE_F9FQ));
    swipeContainerHallLeft.add(textArea1_LH);

    swipeContainer1.add(swipeContainerHallLeft);

    swipeContainerHallRight.setWidth(240);
    swipeContainerHallRight.setHeight(172);
    buttonWithIcon_RH3.setXY(194, 97);
    buttonWithIcon_RH3.setBitmaps(touchgfx::Bitmap(BITMAP_ALTERNATE_THEME_IMAGES_WIDGETS_BUTTON_ICON_ROUND_MICRO_OUTLINE_NORMAL_ID), touchgfx::Bitmap(BITMAP_ALTERNATE_THEME_IMAGES_WIDGETS_BUTTON_ICON_ROUND_MICRO_OUTLINE_PRESSED_ID), touchgfx::Bitmap(BITMAP_CHECKMARK_ID), touchgfx::Bitmap(BITMAP_CHECKMARK_ID));
    buttonWithIcon_RH3.setIconXY(0, 0);
    buttonWithIcon_RH3.setAction(buttonCallback);
    swipeContainerHallRight.add(buttonWithIcon_RH3);

    buttonWithIcon_RH2.setXY(194, 61);
    buttonWithIcon_RH2.setBitmaps(touchgfx::Bitmap(BITMAP_ALTERNATE_THEME_IMAGES_WIDGETS_BUTTON_ICON_ROUND_MICRO_OUTLINE_NORMAL_ID), touchgfx::Bitmap(BITMAP_ALTERNATE_THEME_IMAGES_WIDGETS_BUTTON_ICON_ROUND_MICRO_OUTLINE_PRESSED_ID), touchgfx::Bitmap(BITMAP_CHECKMARK_ID), touchgfx::Bitmap(BITMAP_CHECKMARK_ID));
    buttonWithIcon_RH2.setIconXY(0, 0);
    buttonWithIcon_RH2.setAction(buttonCallback);
    swipeContainerHallRight.add(buttonWithIcon_RH2);

    buttonWithIcon_RH1.setXY(194, 25);
    buttonWithIcon_RH1.setBitmaps(touchgfx::Bitmap(BITMAP_ALTERNATE_THEME_IMAGES_WIDGETS_BUTTON_ICON_ROUND_MICRO_OUTLINE_NORMAL_ID), touchgfx::Bitmap(BITMAP_ALTERNATE_THEME_IMAGES_WIDGETS_BUTTON_ICON_ROUND_MICRO_OUTLINE_PRESSED_ID), touchgfx::Bitmap(BITMAP_CHECKMARK_ID), touchgfx::Bitmap(BITMAP_CHECKMARK_ID));
    buttonWithIcon_RH1.setIconXY(0, 0);
    buttonWithIcon_RH1.setAction(buttonCallback);
    swipeContainerHallRight.add(buttonWithIcon_RH1);

    textAreaCal_RH3.setXY(10, 104);
    textAreaCal_RH3.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    textAreaCal_RH3.setLinespacing(0);
    Unicode::snprintf(textAreaCal_RH3Buffer, TEXTAREACAL_RH3_SIZE, "%s", touchgfx::TypedText(T___SINGLEUSE_4PQQ).getText());
    textAreaCal_RH3.setWildcard(textAreaCal_RH3Buffer);
    textAreaCal_RH3.resizeToCurrentText();
    textAreaCal_RH3.setTypedText(touchgfx::TypedText(T_TEXTAREACAL_LH3));
    swipeContainerHallRight.add(textAreaCal_RH3);

    textAreaCal_RH2.setXY(22, 68);
    textAreaCal_RH2.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    textAreaCal_RH2.setLinespacing(0);
    Unicode::snprintf(textAreaCal_RH2Buffer, TEXTAREACAL_RH2_SIZE, "%s", touchgfx::TypedText(T___SINGLEUSE_YVQL).getText());
    textAreaCal_RH2.setWildcard(textAreaCal_RH2Buffer);
    textAreaCal_RH2.resizeToCurrentText();
    textAreaCal_RH2.setTypedText(touchgfx::TypedText(T_TEXTAREACAL_LH2));
    swipeContainerHallRight.add(textAreaCal_RH2);

    textAreaCal_RH1.setXY(22, 32);
    textAreaCal_RH1.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    textAreaCal_RH1.setLinespacing(0);
    Unicode::snprintf(textAreaCal_RH1Buffer, TEXTAREACAL_RH1_SIZE, "%s", touchgfx::TypedText(T___SINGLEUSE_TIGW).getText());
    textAreaCal_RH1.setWildcard(textAreaCal_RH1Buffer);
    textAreaCal_RH1.resizeToCurrentText();
    textAreaCal_RH1.setTypedText(touchgfx::TypedText(T_TEXTAREACAL_LH1));
    swipeContainerHallRight.add(textAreaCal_RH1);

    line1_RH_1.setPosition(0, 15, 240, 10);
    line1_RH_1Painter.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    line1_RH_1.setPainter(line1_RH_1Painter);
    line1_RH_1.setStart(5, 5);
    line1_RH_1.setEnd(235, 5);
    line1_RH_1.setLineWidth(1);
    line1_RH_1.setLineEndingStyle(touchgfx::Line::ROUND_CAP_ENDING);
    swipeContainerHallRight.add(line1_RH_1);

    textArea1_RH_1.setXY(73, 0);
    textArea1_RH_1.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    textArea1_RH_1.setLinespacing(0);
    textArea1_RH_1.setTypedText(touchgfx::TypedText(T___SINGLEUSE_IZSY));
    swipeContainerHallRight.add(textArea1_RH_1);

    swipeContainer1.add(swipeContainerHallRight);

    swipeContainer1.setSelectedPage(0);
    add(swipeContainer1);

    line1_1.setPosition(0, 75, 240, 10);
    line1_1Painter.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    line1_1.setPainter(line1_1Painter);
    line1_1.setStart(5, 5);
    line1_1.setEnd(235, 5);
    line1_1.setLineWidth(1);
    line1_1.setLineEndingStyle(touchgfx::Line::ROUND_CAP_ENDING);
    add(line1_1);

    textArea3.setXY(70, 60);
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
    transitionBegins();
}

void Calibration_PadViewBase::buttonCallbackHandler(const touchgfx::AbstractButton& src)
{
    if (&src == &buttonWithLabel3)
    {
        //Interaction1
        //When buttonWithLabel3 clicked change screen to Main_Menu
        //Go to Main_Menu with screen transition towards West
        application().gotoMain_MenuScreenWipeTransitionWest();
    }
    if (&src == &buttonWithIcon_LP1)
    {
        //Interaction_LP1
        //When buttonWithIcon_LP1 clicked execute C++ code
        //Execute C++ code
        #ifndef SIMULATOR
        
        SwipeContainer swipeContainer = swipeContainer1;
        uint32_t* Samples = MEAS_start_measure();
        
        FFT fft = calculate_freq_and_signalstrength(1, Samples, 50);
        
        setCalibrationFlashValues(SECTOR_23_ADDR, (uint32_t)fft.signal_strength, 0, 12);
        
        Unicode::snprintf(textAreaCal_LP1Buffer, TEXTAREACAL_LP1_SIZE, "%d", (uint32_t)fft.signal_strength);
        swipeContainer1.invalidate();
        
        #endif
    }
    if (&src == &buttonWithIcon_LP2)
    {
        //Interaction_LP2
        //When buttonWithIcon_LP2 clicked execute C++ code
        //Execute C++ code
        #ifndef SIMULATOR
        
        SwipeContainer swipeContainer = swipeContainer1;
        uint32_t* Samples = MEAS_start_measure();
        
        FFT fft = calculate_freq_and_signalstrength(1, Samples, 50);
        
        setCalibrationFlashValues(SECTOR_23_ADDR, (uint32_t)fft.signal_strength, 1, 12);
        
        Unicode::snprintf(textAreaCal_LP2Buffer, TEXTAREACAL_LP2_SIZE, "%d", (uint32_t)fft.signal_strength);
        swipeContainer1.invalidate();
        
        #endif
    }
    if (&src == &buttonWithIcon_LP3)
    {
        //Interaction_LP3
        //When buttonWithIcon_LP3 clicked execute C++ code
        //Execute C++ code
        #ifndef SIMULATOR
        
        SwipeContainer swipeContainer = swipeContainer1;
        uint32_t* Samples = MEAS_start_measure();
        
        FFT fft = calculate_freq_and_signalstrength(1, Samples, 50);
        
        setCalibrationFlashValues(SECTOR_23_ADDR, (uint32_t)fft.signal_strength, 2, 12);
        
        Unicode::snprintf(textAreaCal_LP3Buffer, TEXTAREACAL_LP3_SIZE, "%d", (uint32_t)fft.signal_strength);
        swipeContainer1.invalidate();
        
        #endif
    }
    if (&src == &buttonWithIcon_RP1)
    {
        //Interaction_RP1
        //When buttonWithIcon_RP1 clicked execute C++ code
        //Execute C++ code
        #ifndef SIMULATOR
        
        SwipeContainer swipeContainer = swipeContainer1;
        uint32_t* Samples = MEAS_start_measure();
        
        FFT fft = calculate_freq_and_signalstrength(1, Samples, 50);
        
        setCalibrationFlashValues(SECTOR_23_ADDR, (uint32_t)fft.signal_strength, 3, 12);
        
        Unicode::snprintf(textAreaCal_RP1Buffer, TEXTAREACAL_RP1_SIZE, "%d", (uint32_t)fft.signal_strength);
        swipeContainer1.invalidate();
        
        #endif
    }
    if (&src == &buttonWithIcon_RP2)
    {
        //Interaction_RP2
        //When buttonWithIcon_RP2 clicked execute C++ code
        //Execute C++ code
        #ifndef SIMULATOR
        
        SwipeContainer swipeContainer = swipeContainer1;
        uint32_t* Samples = MEAS_start_measure();
        
        FFT fft = calculate_freq_and_signalstrength(1, Samples, 50);
        
        setCalibrationFlashValues(SECTOR_23_ADDR, (uint32_t)fft.signal_strength, 4, 12);
        
        Unicode::snprintf(textAreaCal_RP2Buffer, TEXTAREACAL_RP2_SIZE, "%d", (uint32_t)fft.signal_strength);
        swipeContainer1.invalidate();
        
        #endif
    }
    if (&src == &buttonWithIcon_RP3)
    {
        //Interaction_RP3
        //When buttonWithIcon_RP3 clicked execute C++ code
        //Execute C++ code
        #ifndef SIMULATOR
        
        SwipeContainer swipeContainer = swipeContainer1;
        uint32_t* Samples = MEAS_start_measure();
        
        FFT fft = calculate_freq_and_signalstrength(1, Samples, 50);
        
        setCalibrationFlashValues(SECTOR_23_ADDR, (uint32_t)fft.signal_strength, 5, 12);
        
        Unicode::snprintf(textAreaCal_RP3Buffer, TEXTAREACAL_RP3_SIZE, "%d", (uint32_t)fft.signal_strength);
        swipeContainer1.invalidate();
        
        #endif
    }
    if (&src == &buttonWithIcon_LH1)
    {
        //Interaction_LH1
        //When buttonWithIcon_LH1 clicked execute C++ code
        //Execute C++ code
        #ifndef SIMULATOR
        
        SwipeContainer swipeContainer = swipeContainer1;
        uint32_t* Samples = MEAS_start_measure();
        
        FFT fft = calculate_freq_and_signalstrength(1, Samples, 50);
        
        setCalibrationFlashValues(SECTOR_23_ADDR, (uint32_t)fft.signal_strength, 6, 12);
        
        Unicode::snprintf(textAreaCal_LH1Buffer, TEXTAREACAL_LH1_SIZE, "%d", (uint32_t)fft.signal_strength);
        swipeContainer1.invalidate();
        
        #endif
    }
    if (&src == &buttonWithIcon_LH2)
    {
        //Interaction_LH2
        //When buttonWithIcon_LH2 clicked execute C++ code
        //Execute C++ code
        #ifndef SIMULATOR
        
        SwipeContainer swipeContainer = swipeContainer1;
        uint32_t* Samples = MEAS_start_measure();
        
        FFT fft = calculate_freq_and_signalstrength(1, Samples, 50);
        
        setCalibrationFlashValues(SECTOR_23_ADDR, (uint32_t)fft.signal_strength, 7, 12);
        
        Unicode::snprintf(textAreaCal_LH2Buffer, TEXTAREACAL_LH2_SIZE, "%d", (uint32_t)fft.signal_strength);
        swipeContainer1.invalidate();
        
        #endif
    }
    if (&src == &buttonWithIcon_LH3)
    {
        //Interaction_LH3
        //When buttonWithIcon_LH3 clicked execute C++ code
        //Execute C++ code
        #ifndef SIMULATOR
        
        SwipeContainer swipeContainer = swipeContainer1;
        uint32_t* Samples = MEAS_start_measure();
        
        FFT fft = calculate_freq_and_signalstrength(1, Samples, 50);
        
        setCalibrationFlashValues(SECTOR_23_ADDR, (uint32_t)fft.signal_strength, 8, 12);
        
        Unicode::snprintf(textAreaCal_LH3Buffer, TEXTAREACAL_LH3_SIZE, "%d", (uint32_t)fft.signal_strength);
        swipeContainer1.invalidate();
        
        #endif
    }
    if (&src == &buttonWithIcon_RH1)
    {
        //Interaction_RH1
        //When buttonWithIcon_RH1 clicked execute C++ code
        //Execute C++ code
        #ifndef SIMULATOR
        
        SwipeContainer swipeContainer = swipeContainer1;
        uint32_t* Samples = MEAS_start_measure();
        
        FFT fft = calculate_freq_and_signalstrength(1, Samples, 50);
        
        setCalibrationFlashValues(SECTOR_23_ADDR, (uint32_t)fft.signal_strength, 9, 12);
        
        Unicode::snprintf(textAreaCal_RH1Buffer, TEXTAREACAL_RH1_SIZE, "%d", (uint32_t)fft.signal_strength);
        swipeContainer1.invalidate();
        
        #endif
    }
    if (&src == &buttonWithIcon_RH2)
    {
        //Interaction_RH2
        //When buttonWithIcon_RH2 clicked execute C++ code
        //Execute C++ code
        #ifndef SIMULATOR
        
        SwipeContainer swipeContainer = swipeContainer1;
        uint32_t* Samples = MEAS_start_measure();
        
        FFT fft = calculate_freq_and_signalstrength(1, Samples, 50);
        
        setCalibrationFlashValues(SECTOR_23_ADDR, (uint32_t)fft.signal_strength, 10, 12);
        
        Unicode::snprintf(textAreaCal_RH2Buffer, TEXTAREACAL_RH2_SIZE, "%d", (uint32_t)fft.signal_strength);
        swipeContainer1.invalidate();
        
        #endif
    }
    if (&src == &buttonWithIcon_RH3)
    {
        //Interaction_RH3
        //When buttonWithIcon_RH3 clicked execute C++ code
        //Execute C++ code
        #ifndef SIMULATOR
        
        SwipeContainer swipeContainer = swipeContainer1;
        uint32_t* Samples = MEAS_start_measure();
        
        FFT fft = calculate_freq_and_signalstrength(1, Samples, 50);
        
        setCalibrationFlashValues(SECTOR_23_ADDR, (uint32_t)fft.signal_strength, 11, 12);
        
        Unicode::snprintf(textAreaCal_RH3Buffer, TEXTAREACAL_RH3_SIZE, "%d", (uint32_t)fft.signal_strength);
        swipeContainer1.invalidate();
        
        #endif
    }
}

void Calibration_PadViewBase::transitionBegins()
{
    //Interaction2
    //When screen transition begins call virtual function
    //Call Load_FLASH_Values
    Load_FLASH_Values();
}
