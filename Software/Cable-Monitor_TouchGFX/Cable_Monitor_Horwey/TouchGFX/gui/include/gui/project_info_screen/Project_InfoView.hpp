#ifndef PROJECT_INFOVIEW_HPP
#define PROJECT_INFOVIEW_HPP

#include <gui_generated/project_info_screen/Project_InfoViewBase.hpp>
#include <gui/project_info_screen/Project_InfoPresenter.hpp>

class Project_InfoView : public Project_InfoViewBase
{
public:
    Project_InfoView();
    virtual ~Project_InfoView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
    virtual void setTimeoutValue(int value);
protected:
};

#endif // PROJECT_INFOVIEW_HPP
