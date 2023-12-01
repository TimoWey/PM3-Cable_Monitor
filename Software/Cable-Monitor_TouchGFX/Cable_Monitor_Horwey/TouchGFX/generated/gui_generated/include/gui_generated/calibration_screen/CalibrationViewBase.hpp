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
#include <touchgfx/widgets/TextArea.hpp>
#include <touchgfx/widgets/ButtonWithLabel.hpp>

class CalibrationViewBase : public touchgfx::View<CalibrationPresenter>
{
public:
    CalibrationViewBase();
    virtual ~CalibrationViewBase();
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
    touchgfx::TextArea textArea2;
    touchgfx::TextArea textArea1;
    touchgfx::ButtonWithLabel buttonWithLabel3;
    touchgfx::ButtonWithLabel buttonWithLabel2;
    touchgfx::ButtonWithLabel buttonWithLabel1;

private:

};

#endif // CALIBRATIONVIEWBASE_HPP
