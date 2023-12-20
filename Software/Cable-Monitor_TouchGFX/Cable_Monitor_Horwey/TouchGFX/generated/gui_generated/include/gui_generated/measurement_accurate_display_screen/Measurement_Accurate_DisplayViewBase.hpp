/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#ifndef MEASUREMENT_ACCURATE_DISPLAYVIEWBASE_HPP
#define MEASUREMENT_ACCURATE_DISPLAYVIEWBASE_HPP

#include <gui/common/FrontendApplication.hpp>
#include <mvp/View.hpp>
#include <gui/measurement_accurate_display_screen/Measurement_Accurate_DisplayPresenter.hpp>
#include <touchgfx/widgets/Box.hpp>
#include <touchgfx/widgets/Image.hpp>
#include <touchgfx/widgets/ButtonWithLabel.hpp>
#include <touchgfx/widgets/TextArea.hpp>
#include <touchgfx/widgets/TextAreaWithWildcard.hpp>
#include <touchgfx/widgets/Gauge.hpp>
#include <touchgfx/widgets/canvas/Line.hpp>
#include <touchgfx/widgets/canvas/PainterRGB565.hpp>

class Measurement_Accurate_DisplayViewBase : public touchgfx::View<Measurement_Accurate_DisplayPresenter>
{
public:
    Measurement_Accurate_DisplayViewBase();
    virtual ~Measurement_Accurate_DisplayViewBase();
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
    touchgfx::ButtonWithLabel buttonWithLabel_Return;
    touchgfx::TextArea textArea_n90C;
    touchgfx::TextArea textArea_p90C;
    touchgfx::TextArea textArea_0C;
    touchgfx::TextAreaWithOneWildcard AMD1_Current;
    touchgfx::TextAreaWithOneWildcard AMD1_Frequency;
    touchgfx::TextAreaWithOneWildcard AMD1_Distance;
    touchgfx::Gauge AMD1_Gauge;
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
    static const uint16_t AMD1_CURRENT_SIZE = 10;
    touchgfx::Unicode::UnicodeChar AMD1_CurrentBuffer[AMD1_CURRENT_SIZE];
    static const uint16_t AMD1_FREQUENCY_SIZE = 10;
    touchgfx::Unicode::UnicodeChar AMD1_FrequencyBuffer[AMD1_FREQUENCY_SIZE];
    static const uint16_t AMD1_DISTANCE_SIZE = 10;
    touchgfx::Unicode::UnicodeChar AMD1_DistanceBuffer[AMD1_DISTANCE_SIZE];

private:

    /*
     * Canvas Buffer Size
     */
    static const uint32_t CANVAS_BUFFER_SIZE = 3600;
    uint8_t canvasBuffer[CANVAS_BUFFER_SIZE];

    /*
     * Callback Declarations
     */
    touchgfx::Callback<Measurement_Accurate_DisplayViewBase, const touchgfx::AbstractButton&> buttonCallback;

    /*
     * Callback Handler Declarations
     */
    void buttonCallbackHandler(const touchgfx::AbstractButton& src);

};

#endif // MEASUREMENT_ACCURATE_DISPLAYVIEWBASE_HPP
