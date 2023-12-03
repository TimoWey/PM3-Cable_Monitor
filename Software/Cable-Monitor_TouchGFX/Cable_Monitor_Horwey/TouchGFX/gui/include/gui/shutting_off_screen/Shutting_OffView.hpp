#ifndef SHUTTING_OFFVIEW_HPP
#define SHUTTING_OFFVIEW_HPP

#include <gui_generated/shutting_off_screen/Shutting_OffViewBase.hpp>
#include <gui/shutting_off_screen/Shutting_OffPresenter.hpp>

class Shutting_OffView : public Shutting_OffViewBase
{
public:
    Shutting_OffView();
    virtual ~Shutting_OffView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
protected:
};

#endif // SHUTTING_OFFVIEW_HPP
