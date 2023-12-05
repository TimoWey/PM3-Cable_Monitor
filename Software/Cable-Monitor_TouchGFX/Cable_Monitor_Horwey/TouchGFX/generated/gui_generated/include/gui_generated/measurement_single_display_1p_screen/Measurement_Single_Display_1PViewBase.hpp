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
#include <touchgfx/widgets/canvas/Line.hpp>
#include <touchgfx/widgets/canvas/PainterRGB565.hpp>
#include <touchgfx/widgets/ButtonWithLabel.hpp>
#include <gui/containers/Gauge_with_Values.hpp>

class Measurement_Single_Display_1PViewBase : public touchgfx::View<Measurement_Single_Display_1PPresenter>
{
public:
    Measurement_Single_Display_1PViewBase();
    virtual ~Measurement_Single_Display_1PViewBase();
    virtual void setupScreen();

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
    touchgfx::Line line1;
    touchgfx::PainterRGB565 line1Painter;
    touchgfx::TextArea textArea2;
    touchgfx::TextArea textArea1;
    touchgfx::ButtonWithLabel buttonWithLabel3;
    Gauge_with_Values gauge_with_Values1;

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

};

#endif // MEASUREMENT_SINGLE_DISPLAY_1PVIEWBASE_HPP
