/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#ifndef MEASUREMENT_SINGLE_DISPLAY_3PVIEWBASE_HPP
#define MEASUREMENT_SINGLE_DISPLAY_3PVIEWBASE_HPP

#include <gui/common/FrontendApplication.hpp>
#include <mvp/View.hpp>
#include <gui/measurement_single_display_3p_screen/Measurement_Single_Display_3PPresenter.hpp>
#include <touchgfx/widgets/Box.hpp>
#include <touchgfx/widgets/Image.hpp>
#include <touchgfx/widgets/ButtonWithLabel.hpp>
#include <touchgfx/widgets/TextArea.hpp>
#include <touchgfx/widgets/TextAreaWithWildcard.hpp>
#include <touchgfx/widgets/Gauge.hpp>
#include <touchgfx/widgets/canvas/Line.hpp>
#include <touchgfx/widgets/canvas/PainterRGB565.hpp>

class Measurement_Single_Display_3PViewBase : public touchgfx::View<Measurement_Single_Display_3PPresenter>
{
public:
    Measurement_Single_Display_3PViewBase();
    virtual ~Measurement_Single_Display_3PViewBase();
    virtual void setupScreen();

protected:
    FrontendApplication& application() {
        return *static_cast<FrontendApplication*>(touchgfx::Application::getInstance());
    }

    /*
     * Member Declarations
     */
    touchgfx::Box __background;
    touchgfx::Image image_background;
    touchgfx::ButtonWithLabel buttonWithLabel_return;
    touchgfx::TextArea textArea_n90C;
    touchgfx::TextArea textArea_p90C;
    touchgfx::TextArea textArea_0C;
    touchgfx::TextAreaWithOneWildcard SMD3_Current;
    touchgfx::TextAreaWithOneWildcard SMD3_Frequency;
    touchgfx::TextAreaWithOneWildcard SMD3_Distance;
    touchgfx::Gauge SMD3_Gauge;
    touchgfx::Line line2;
    touchgfx::PainterRGB565 line2Painter;
    touchgfx::TextArea textArea_menu;
    touchgfx::Line line1;
    touchgfx::PainterRGB565 line1Painter;
    touchgfx::TextArea textArea_name;
    touchgfx::TextArea textArea_title;

    /*
     * Wildcard Buffers
     */
    static const uint16_t SMD3_CURRENT_SIZE = 10;
    touchgfx::Unicode::UnicodeChar SMD3_CurrentBuffer[SMD3_CURRENT_SIZE];
    static const uint16_t SMD3_FREQUENCY_SIZE = 10;
    touchgfx::Unicode::UnicodeChar SMD3_FrequencyBuffer[SMD3_FREQUENCY_SIZE];
    static const uint16_t SMD3_DISTANCE_SIZE = 10;
    touchgfx::Unicode::UnicodeChar SMD3_DistanceBuffer[SMD3_DISTANCE_SIZE];

private:

    /*
     * Canvas Buffer Size
     */
    static const uint32_t CANVAS_BUFFER_SIZE = 3600;
    uint8_t canvasBuffer[CANVAS_BUFFER_SIZE];

    /*
     * Callback Declarations
     */
    touchgfx::Callback<Measurement_Single_Display_3PViewBase, const touchgfx::AbstractButton&> buttonCallback;

    /*
     * Callback Handler Declarations
     */
    void buttonCallbackHandler(const touchgfx::AbstractButton& src);

};

#endif // MEASUREMENT_SINGLE_DISPLAY_3PVIEWBASE_HPP
