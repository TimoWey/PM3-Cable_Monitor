#ifndef MEASUREMENTVIEW_HPP
#define MEASUREMENTVIEW_HPP

#include <gui_generated/measurement_screen/MeasurementViewBase.hpp>
#include <gui/measurement_screen/MeasurementPresenter.hpp>

class MeasurementView : public MeasurementViewBase
{
public:
    MeasurementView();
    virtual ~MeasurementView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
protected:
};

#endif // MEASUREMENTVIEW_HPP
