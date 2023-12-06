/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#ifndef MEASUREMENT_SINGLEVIEWBASE_HPP
#define MEASUREMENT_SINGLEVIEWBASE_HPP

#include <gui/common/FrontendApplication.hpp>
#include <mvp/View.hpp>
#include <gui/measurement_single_screen/Measurement_SinglePresenter.hpp>
#include <touchgfx/widgets/Box.hpp>
#include <touchgfx/widgets/Image.hpp>
#include <touchgfx/widgets/TextAreaWithWildcard.hpp>
#include <touchgfx/widgets/TextArea.hpp>
#include <touchgfx/widgets/canvas/Line.hpp>
#include <touchgfx/widgets/canvas/PainterRGB565.hpp>
#include <touchgfx/widgets/ButtonWithLabel.hpp>

class Measurement_SingleViewBase : public touchgfx::View<Measurement_SinglePresenter>
{
public:
    Measurement_SingleViewBase();
    virtual ~Measurement_SingleViewBase();
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
    touchgfx::TextAreaWithOneWildcard textArea3_1;
    touchgfx::TextArea textArea3;
    touchgfx::Line line1;
    touchgfx::PainterRGB565 line1Painter;
    touchgfx::TextArea textArea2;
    touchgfx::TextArea textArea1;
    touchgfx::ButtonWithLabel buttonWithLabel3;
    touchgfx::ButtonWithLabel buttonWithLabel2;
    touchgfx::ButtonWithLabel buttonWithLabel1;

    /*
     * Wildcard Buffers
     */
    static const uint16_t TEXTAREA3_1_SIZE = 4;
    touchgfx::Unicode::UnicodeChar textArea3_1Buffer[TEXTAREA3_1_SIZE];

private:

    /*
     * Canvas Buffer Size
     */
    static const uint32_t CANVAS_BUFFER_SIZE = 3600;
    uint8_t canvasBuffer[CANVAS_BUFFER_SIZE];

    /*
     * Callback Declarations
     */
    touchgfx::Callback<Measurement_SingleViewBase, const touchgfx::AbstractButton&> buttonCallback;

    /*
     * Callback Handler Declarations
     */
    void buttonCallbackHandler(const touchgfx::AbstractButton& src);

};

#endif // MEASUREMENT_SINGLEVIEWBASE_HPP
