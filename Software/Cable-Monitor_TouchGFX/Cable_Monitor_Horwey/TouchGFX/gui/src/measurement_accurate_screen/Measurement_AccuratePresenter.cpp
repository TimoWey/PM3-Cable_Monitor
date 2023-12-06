#include <gui/measurement_accurate_screen/Measurement_AccurateView.hpp>
#include <gui/measurement_accurate_screen/Measurement_AccuratePresenter.hpp>

Measurement_AccuratePresenter::Measurement_AccuratePresenter(Measurement_AccurateView& v)
    : view(v)
{

}

void Measurement_AccuratePresenter::activate()
{

}

void Measurement_AccuratePresenter::deactivate()
{

}

void Measurement_AccuratePresenter::setTimeoutValue(int value)
{
	view.setTimeoutValue(value);
}
