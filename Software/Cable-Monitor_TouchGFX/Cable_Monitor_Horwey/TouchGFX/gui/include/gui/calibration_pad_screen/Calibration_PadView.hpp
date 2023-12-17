#ifndef CALIBRATION_PADVIEW_HPP
#define CALIBRATION_PADVIEW_HPP

#include <gui_generated/calibration_pad_screen/Calibration_PadViewBase.hpp>
#include <gui/calibration_pad_screen/Calibration_PadPresenter.hpp>

class Calibration_PadView : public Calibration_PadViewBase
{
public:
    Calibration_PadView();
    virtual ~Calibration_PadView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
    virtual void setTimeoutValue(int value);
    virtual void Load_FLASH_Values();
protected:
};

#endif // CALIBRATION_PADVIEW_HPP
