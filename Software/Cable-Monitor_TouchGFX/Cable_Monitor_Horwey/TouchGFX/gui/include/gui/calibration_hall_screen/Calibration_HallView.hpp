#ifndef CALIBRATION_HALLVIEW_HPP
#define CALIBRATION_HALLVIEW_HPP

#include <gui_generated/calibration_hall_screen/Calibration_HallViewBase.hpp>
#include <gui/calibration_hall_screen/Calibration_HallPresenter.hpp>

class Calibration_HallView : public Calibration_HallViewBase
{
public:
    Calibration_HallView();
    virtual ~Calibration_HallView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
protected:
};

#endif // CALIBRATION_HALLVIEW_HPP
