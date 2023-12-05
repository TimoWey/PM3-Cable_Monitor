#ifndef PROJECT_INFOPRESENTER_HPP
#define PROJECT_INFOPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class Project_InfoView;

class Project_InfoPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    Project_InfoPresenter(Project_InfoView& v);

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

    virtual ~Project_InfoPresenter() {}

    virtual void setTimeoutValue(int value);

private:
    Project_InfoPresenter();

    Project_InfoView& view;
};

#endif // PROJECT_INFOPRESENTER_HPP
