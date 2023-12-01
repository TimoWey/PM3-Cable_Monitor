#ifndef MEASUREMENT_SINGLE_DISPLAYPRESENTER_HPP
#define MEASUREMENT_SINGLE_DISPLAYPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class Measurement_Single_DisplayView;

class Measurement_Single_DisplayPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    Measurement_Single_DisplayPresenter(Measurement_Single_DisplayView& v);

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

    virtual ~Measurement_Single_DisplayPresenter() {}

private:
    Measurement_Single_DisplayPresenter();

    Measurement_Single_DisplayView& view;
};

#endif // MEASUREMENT_SINGLE_DISPLAYPRESENTER_HPP
