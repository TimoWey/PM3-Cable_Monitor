/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#ifndef CALIBRATION_PADVIEWBASE_HPP
#define CALIBRATION_PADVIEWBASE_HPP

#include <gui/common/FrontendApplication.hpp>
#include <mvp/View.hpp>
#include <gui/calibration_pad_screen/Calibration_PadPresenter.hpp>
#include <touchgfx/widgets/Box.hpp>
#include <touchgfx/widgets/Image.hpp>
#include <touchgfx/widgets/ButtonWithLabel.hpp>
#include <touchgfx/containers/SwipeContainer.hpp>
#include <touchgfx/containers/Container.hpp>
#include <touchgfx/widgets/TextAreaWithWildcard.hpp>
#include <touchgfx/widgets/ButtonWithIcon.hpp>
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

class Calibration_PadViewBase : public touchgfx::View<Calibration_PadPresenter>
{
public:
    Calibration_PadViewBase();
    virtual ~Calibration_PadViewBase();
    virtual void setupScreen();
    virtual void transitionBegins();

    /*
     * Virtual Action Handlers
     */
    virtual void Load_FLASH_Values()
    {
        // Override and implement this function in Calibration_Pad
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
    touchgfx::TextAreaWithOneWildcard textAreaCal_LP1_1;
    touchgfx::ButtonWithIcon buttonWithIcon_LP3;
    touchgfx::ButtonWithIcon buttonWithIcon_LP2;
    touchgfx::ButtonWithIcon buttonWithIcon_LP1;
    touchgfx::TextAreaWithOneWildcard textAreaCal_LP3;
    touchgfx::TextAreaWithOneWildcard textAreaCal_LP2;
    touchgfx::TextAreaWithOneWildcard textAreaCal_LP1;
    touchgfx::Line line1_1_2_1;
    touchgfx::PainterRGB565 line1_1_2_1Painter;
    touchgfx::TextArea textArea3_2_1;
    touchgfx::Container swipeContainerPadRight;
    touchgfx::ButtonWithIcon buttonWithIcon_RP3;
    touchgfx::ButtonWithIcon buttonWithIcon_RP2;
    touchgfx::ButtonWithIcon buttonWithIcon_RP1;
    touchgfx::TextAreaWithOneWildcard textAreaCal_RP3;
    touchgfx::TextAreaWithOneWildcard textAreaCal_RP2;
    touchgfx::TextAreaWithOneWildcard textAreaCal_RP1;
    touchgfx::Line line1_1_2;
    touchgfx::PainterRGB565 line1_1_2Painter;
    touchgfx::TextArea textArea3_2;
    touchgfx::Container swipeContainerHallLeft;
    touchgfx::ButtonWithIcon buttonWithIcon_LH3;
    touchgfx::ButtonWithIcon buttonWithIcon_LH2;
    touchgfx::ButtonWithIcon buttonWithIcon_LH1;
    touchgfx::TextAreaWithOneWildcard textAreaCal_LH3;
    touchgfx::TextAreaWithOneWildcard textAreaCal_LH2;
    touchgfx::TextAreaWithOneWildcard textAreaCal_LH1;
    touchgfx::Line line1_1_2_2;
    touchgfx::PainterRGB565 line1_1_2_2Painter;
    touchgfx::TextArea textArea3_2_2;
    touchgfx::Container swipeContainerHallRight;
    touchgfx::ButtonWithIcon buttonWithIcon_RH3;
    touchgfx::ButtonWithIcon buttonWithIcon_RH2;
    touchgfx::ButtonWithIcon buttonWithIcon_RH1;
    touchgfx::TextAreaWithOneWildcard textAreaCal_RH3;
    touchgfx::TextAreaWithOneWildcard textAreaCal_RH2;
    touchgfx::TextAreaWithOneWildcard textAreaCal_RH1;
    touchgfx::Line line1_1_2_3;
    touchgfx::PainterRGB565 line1_1_2_3Painter;
    touchgfx::TextArea textArea3_2_3;
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
    static const uint16_t TEXTAREACAL_LP1_1_SIZE = 10;
    touchgfx::Unicode::UnicodeChar textAreaCal_LP1_1Buffer[TEXTAREACAL_LP1_1_SIZE];
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
    static const uint16_t TEXTAREACAL_LH3_SIZE = 10;
    touchgfx::Unicode::UnicodeChar textAreaCal_LH3Buffer[TEXTAREACAL_LH3_SIZE];
    static const uint16_t TEXTAREACAL_LH2_SIZE = 10;
    touchgfx::Unicode::UnicodeChar textAreaCal_LH2Buffer[TEXTAREACAL_LH2_SIZE];
    static const uint16_t TEXTAREACAL_LH1_SIZE = 10;
    touchgfx::Unicode::UnicodeChar textAreaCal_LH1Buffer[TEXTAREACAL_LH1_SIZE];
    static const uint16_t TEXTAREACAL_RH3_SIZE = 10;
    touchgfx::Unicode::UnicodeChar textAreaCal_RH3Buffer[TEXTAREACAL_RH3_SIZE];
    static const uint16_t TEXTAREACAL_RH2_SIZE = 10;
    touchgfx::Unicode::UnicodeChar textAreaCal_RH2Buffer[TEXTAREACAL_RH2_SIZE];
    static const uint16_t TEXTAREACAL_RH1_SIZE = 10;
    touchgfx::Unicode::UnicodeChar textAreaCal_RH1Buffer[TEXTAREACAL_RH1_SIZE];

private:

    /*
     * Canvas Buffer Size
     */
    static const uint32_t CANVAS_BUFFER_SIZE = 3600;
    uint8_t canvasBuffer[CANVAS_BUFFER_SIZE];

    /*
     * Callback Declarations
     */
    touchgfx::Callback<Calibration_PadViewBase, const touchgfx::AbstractButton&> buttonCallback;

    /*
     * Callback Handler Declarations
     */
    void buttonCallbackHandler(const touchgfx::AbstractButton& src);

};

#endif // CALIBRATION_PADVIEWBASE_HPP
