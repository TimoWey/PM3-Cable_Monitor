/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#ifndef MEASUREMENT_SINGLE_DISPLAY_1PVIEWBASE_HPP
#define MEASUREMENT_SINGLE_DISPLAY_1PVIEWBASE_HPP

#include <gui/common/FrontendApplication.hpp>
#include <mvp/View.hpp>
#include <gui/measurement_single_display_1p_screen/Measurement_Single_Display_1PPresenter.hpp>
#include <touchgfx/widgets/Box.hpp>
#include <touchgfx/widgets/Image.hpp>
#include <touchgfx/widgets/TextArea.hpp>
#include <touchgfx/widgets/Gauge.hpp>
#include <touchgfx/widgets/TextAreaWithWildcard.hpp>
#include <touchgfx/widgets/canvas/Line.hpp>
#include <touchgfx/widgets/canvas/PainterRGB565.hpp>
#include <touchgfx/widgets/ButtonWithLabel.hpp>

class Measurement_Single_Display_1PViewBase : public touchgfx::View<Measurement_Single_Display_1PPresenter>
{
public:
    Measurement_Single_Display_1PViewBase();
    virtual ~Measurement_Single_Display_1PViewBase();
    virtual void setupScreen();
    virtual void handleTickEvent();

    /*
     * Virtual Action Handlers
     */
    virtual void testGui()
    {
        // Override and implement this function in Measurement_Single_Display_1P
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
    touchgfx::TextArea textArea3;
    touchgfx::Gauge SMD1_gauge;
    touchgfx::TextAreaWithOneWildcard SMD1_Current;
    touchgfx::TextAreaWithOneWildcard SMD1_Frequency;
    touchgfx::TextAreaWithOneWildcard SMD1_Distance;
    touchgfx::TextArea textArea4;
    touchgfx::TextArea textArea4_1;
    touchgfx::TextArea textArea4_2;
    touchgfx::Line line1;
    touchgfx::PainterRGB565 line1Painter;
    touchgfx::TextArea textArea2;
    touchgfx::TextArea textArea1;
    touchgfx::ButtonWithLabel buttonWithLabel3;

    /*
     * Wildcard Buffers
     */
    static const uint16_t SMD1_CURRENT_SIZE = 10;
    touchgfx::Unicode::UnicodeChar SMD1_CurrentBuffer[SMD1_CURRENT_SIZE];
    static const uint16_t SMD1_FREQUENCY_SIZE = 10;
    touchgfx::Unicode::UnicodeChar SMD1_FrequencyBuffer[SMD1_FREQUENCY_SIZE];
    static const uint16_t SMD1_DISTANCE_SIZE = 10;
    touchgfx::Unicode::UnicodeChar SMD1_DistanceBuffer[SMD1_DISTANCE_SIZE];

private:

    /*
     * Canvas Buffer Size
     */
    static const uint32_t CANVAS_BUFFER_SIZE = 3600;
    uint8_t canvasBuffer[CANVAS_BUFFER_SIZE];

    /*
     * Callback Declarations
     */
    touchgfx::Callback<Measurement_Single_Display_1PViewBase, const touchgfx::AbstractButton&> buttonCallback;

    /*
     * Callback Handler Declarations
     */
    void buttonCallbackHandler(const touchgfx::AbstractButton& src);

    /*
     * Tick Counter Declarations
     */
    static const uint32_t TICK_INTERACTION2_INTERVAL = 5;
    uint32_t frameCountInteraction2Interval;

};

#endif // MEASUREMENT_SINGLE_DISPLAY_1PVIEWBASE_HPP
