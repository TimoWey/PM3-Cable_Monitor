/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#ifndef CALIBRATIONVIEWBASE_HPP
#define CALIBRATIONVIEWBASE_HPP

#include <gui/common/FrontendApplication.hpp>
#include <mvp/View.hpp>
#include <gui/calibration_screen/CalibrationPresenter.hpp>
#include <touchgfx/widgets/Box.hpp>
#include <touchgfx/widgets/Image.hpp>
#include <touchgfx/widgets/ButtonWithLabel.hpp>
#include <touchgfx/containers/SwipeContainer.hpp>
#include <touchgfx/containers/Container.hpp>
#include <touchgfx/widgets/ButtonWithIcon.hpp>
#include <touchgfx/widgets/TextAreaWithWildcard.hpp>
#include <touchgfx/widgets/canvas/Line.hpp>
#include <touchgfx/widgets/canvas/PainterRGB565.hpp>
#include <touchgfx/widgets/TextArea.hpp>
#ifndef SIMULATOR

#include "main.h"
extern "C"
{
	#include "measuring.h"
	#include "calculation.h"
}
#endif

class CalibrationViewBase : public touchgfx::View<CalibrationPresenter>
{
public:
    CalibrationViewBase();
    virtual ~CalibrationViewBase();
    virtual void setupScreen();
    virtual void transitionBegins();

    /*
     * Virtual Action Handlers
     */
    virtual void Load_FLASH_Values()
    {
        // Override and implement this function in Calibration
    }

protected:
    FrontendApplication& application() {
        return *static_cast<FrontendApplication*>(touchgfx::Application::getInstance());
    }

    /*
     * Member Declarations
     */
    touchgfx::Box __background;
    touchgfx::Image image1;
    touchgfx::ButtonWithLabel buttonWithLabel3;
    touchgfx::SwipeContainer swipeContainer1;
    touchgfx::Container swipeContainerPadLeft;
    touchgfx::ButtonWithIcon buttonWithIcon_LP3;
    touchgfx::ButtonWithIcon buttonWithIcon_LP2;
    touchgfx::ButtonWithIcon buttonWithIcon_LP1;
    touchgfx::TextAreaWithOneWildcard textAreaCal_LP3;
    touchgfx::TextAreaWithOneWildcard textAreaCal_LP2;
    touchgfx::TextAreaWithOneWildcard textAreaCal_LP1;
    touchgfx::Line line1_LP;
    touchgfx::PainterRGB565 line1_LPPainter;
    touchgfx::TextArea textArea1_LP;
    touchgfx::Container swipeContainerPadRight;
    touchgfx::ButtonWithIcon buttonWithIcon_RP3;
    touchgfx::ButtonWithIcon buttonWithIcon_RP2;
    touchgfx::ButtonWithIcon buttonWithIcon_RP1;
    touchgfx::TextAreaWithOneWildcard textAreaCal_RP3;
    touchgfx::TextAreaWithOneWildcard textAreaCal_RP2;
    touchgfx::TextAreaWithOneWildcard textAreaCal_RP1;
    touchgfx::Line line1_RP;
    touchgfx::PainterRGB565 line1_RPPainter;
    touchgfx::TextArea textArea1_RP;
    touchgfx::Container swipeContainerHallLeft1P;
    touchgfx::ButtonWithIcon buttonWithIcon_LH2_5A_1P;
    touchgfx::TextAreaWithOneWildcard textAreaCal_LH_5A_1P;
    touchgfx::TextArea textArea1_CURRENTL_1P_5A;
    touchgfx::ButtonWithIcon buttonWithIcon_LH1_1A_1P;
    touchgfx::TextAreaWithOneWildcard textAreaCal_LH_1A_1P;
    touchgfx::TextArea textArea1_CURRENTL_1P_1A;
    touchgfx::Line line1_LH;
    touchgfx::PainterRGB565 line1_LHPainter;
    touchgfx::TextArea textArea1_LH;
    touchgfx::Container swipeContainerHallRight1P;
    touchgfx::ButtonWithIcon buttonWithIcon_RH2_5A_1P;
    touchgfx::TextAreaWithOneWildcard textAreaCal_RH_5A_1P;
    touchgfx::TextArea textArea1_CURRENTR_1P_5A;
    touchgfx::ButtonWithIcon buttonWithIcon_RH1_1A_1P;
    touchgfx::TextAreaWithOneWildcard textAreaCal_RH_1A_1P;
    touchgfx::TextArea textArea1_CURRENTR_1P_1A;
    touchgfx::Line line1_RH_1;
    touchgfx::PainterRGB565 line1_RH_1Painter;
    touchgfx::TextArea textArea1_RH_1P;
    touchgfx::Container swipeContainerHallLeft3P;
    touchgfx::ButtonWithIcon buttonWithIcon_LH2_5A_3P;
    touchgfx::TextAreaWithOneWildcard textAreaCal_LH_5A_3P;
    touchgfx::TextArea textArea1_CURRENTL_3P_5A;
    touchgfx::ButtonWithIcon buttonWithIcon_LH1_1A_3P;
    touchgfx::TextAreaWithOneWildcard textAreaCal_LH_1A_3P;
    touchgfx::TextArea textArea1_CURRENTL_3P_1A;
    touchgfx::Line line1_LH_3P;
    touchgfx::PainterRGB565 line1_LH_3PPainter;
    touchgfx::TextArea textArea1_LH_3P;
    touchgfx::Container swipeContainerHallRight3P;
    touchgfx::ButtonWithIcon buttonWithIcon_RH2_5A_3P;
    touchgfx::TextAreaWithOneWildcard textAreaCal_RH_5A_3P;
    touchgfx::TextArea textArea1_CURRENTR_3P_5A;
    touchgfx::ButtonWithIcon buttonWithIcon_RH1_1A_3P;
    touchgfx::TextAreaWithOneWildcard textAreaCal_RH_1A_3P;
    touchgfx::TextArea textArea1_CURRENTR_3P_1A;
    touchgfx::Line line1_RH_1_3P;
    touchgfx::PainterRGB565 line1_RH_1_3PPainter;
    touchgfx::TextArea textArea1_RH_3P;
    touchgfx::Line line1_1;
    touchgfx::PainterRGB565 line1_1Painter;
    touchgfx::TextArea textArea3;
    touchgfx::Line line1;
    touchgfx::PainterRGB565 line1Painter;
    touchgfx::TextArea textArea2;
    touchgfx::TextArea textArea1;

    /*
     * Wildcard Buffers
     */
    static const uint16_t TEXTAREACAL_LP3_SIZE = 10;
    touchgfx::Unicode::UnicodeChar textAreaCal_LP3Buffer[TEXTAREACAL_LP3_SIZE];
    static const uint16_t TEXTAREACAL_LP2_SIZE = 10;
    touchgfx::Unicode::UnicodeChar textAreaCal_LP2Buffer[TEXTAREACAL_LP2_SIZE];
    static const uint16_t TEXTAREACAL_LP1_SIZE = 10;
    touchgfx::Unicode::UnicodeChar textAreaCal_LP1Buffer[TEXTAREACAL_LP1_SIZE];
    static const uint16_t TEXTAREACAL_RP3_SIZE = 10;
    touchgfx::Unicode::UnicodeChar textAreaCal_RP3Buffer[TEXTAREACAL_RP3_SIZE];
    static const uint16_t TEXTAREACAL_RP2_SIZE = 10;
    touchgfx::Unicode::UnicodeChar textAreaCal_RP2Buffer[TEXTAREACAL_RP2_SIZE];
    static const uint16_t TEXTAREACAL_RP1_SIZE = 10;
    touchgfx::Unicode::UnicodeChar textAreaCal_RP1Buffer[TEXTAREACAL_RP1_SIZE];
    static const uint16_t TEXTAREACAL_LH_5A_1P_SIZE = 10;
    touchgfx::Unicode::UnicodeChar textAreaCal_LH_5A_1PBuffer[TEXTAREACAL_LH_5A_1P_SIZE];
    static const uint16_t TEXTAREACAL_LH_1A_1P_SIZE = 10;
    touchgfx::Unicode::UnicodeChar textAreaCal_LH_1A_1PBuffer[TEXTAREACAL_LH_1A_1P_SIZE];
    static const uint16_t TEXTAREACAL_RH_5A_1P_SIZE = 10;
    touchgfx::Unicode::UnicodeChar textAreaCal_RH_5A_1PBuffer[TEXTAREACAL_RH_5A_1P_SIZE];
    static const uint16_t TEXTAREACAL_RH_1A_1P_SIZE = 10;
    touchgfx::Unicode::UnicodeChar textAreaCal_RH_1A_1PBuffer[TEXTAREACAL_RH_1A_1P_SIZE];
    static const uint16_t TEXTAREACAL_LH_5A_3P_SIZE = 10;
    touchgfx::Unicode::UnicodeChar textAreaCal_LH_5A_3PBuffer[TEXTAREACAL_LH_5A_3P_SIZE];
    static const uint16_t TEXTAREACAL_LH_1A_3P_SIZE = 10;
    touchgfx::Unicode::UnicodeChar textAreaCal_LH_1A_3PBuffer[TEXTAREACAL_LH_1A_3P_SIZE];
    static const uint16_t TEXTAREACAL_RH_5A_3P_SIZE = 10;
    touchgfx::Unicode::UnicodeChar textAreaCal_RH_5A_3PBuffer[TEXTAREACAL_RH_5A_3P_SIZE];
    static const uint16_t TEXTAREACAL_RH_1A_3P_SIZE = 10;
    touchgfx::Unicode::UnicodeChar textAreaCal_RH_1A_3PBuffer[TEXTAREACAL_RH_1A_3P_SIZE];

private:

    /*
     * Canvas Buffer Size
     */
    static const uint32_t CANVAS_BUFFER_SIZE = 3600;
    uint8_t canvasBuffer[CANVAS_BUFFER_SIZE];

    /*
     * Callback Declarations
     */
    touchgfx::Callback<CalibrationViewBase, const touchgfx::AbstractButton&> buttonCallback;

    /*
     * Callback Handler Declarations
     */
    void buttonCallbackHandler(const touchgfx::AbstractButton& src);

};

#endif // CALIBRATIONVIEWBASE_HPP