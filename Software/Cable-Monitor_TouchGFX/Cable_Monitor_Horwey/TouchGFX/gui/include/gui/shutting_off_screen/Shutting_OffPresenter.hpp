#ifndef SHUTTING_OFFPRESENTER_HPP
#define SHUTTING_OFFPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class Shutting_OffView;

class Shutting_OffPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    Shutting_OffPresenter(Shutting_OffView& v);

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

    virtual ~Shutting_OffPresenter() {}

private:
    Shutting_OffPresenter();

    Shutting_OffView& view;
};

#endif // SHUTTING_OFFPRESENTER_HPP
