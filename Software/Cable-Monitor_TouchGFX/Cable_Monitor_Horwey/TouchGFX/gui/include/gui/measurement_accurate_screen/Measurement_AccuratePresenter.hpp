#ifndef MEASUREMENT_ACCURATEPRESENTER_HPP
#define MEASUREMENT_ACCURATEPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class Measurement_AccurateView;

class Measurement_AccuratePresenter : public touchgfx::Presenter, public ModelListener
{
public:
    Measurement_AccuratePresenter(Measurement_AccurateView& v);

    /**
     * The activate function is called automatically when this screen is "switched in"
     * (ie. made active). Initialization logic can be placed here.
     */
    virtual void activate();

    /**
     * The deactivate function is called automatically when this screen is "switched out"
     * (ie. made inactive). Teardown functionality can be placed here.
     */
    virtual void deactivate();

    virtual ~Measurement_AccuratePresenter() {}

private:
    Measurement_AccuratePresenter();

    Measurement_AccurateView& view;
};

#endif // MEASUREMENT_ACCURATEPRESENTER_HPP
