#include <gui/main_menu_screen/Main_MenuView.hpp>

Main_MenuView::Main_MenuView()
{

}

void Main_MenuView::setupScreen()
{
    Main_MenuViewBase::setupScreen();
}

void Main_MenuView::tearDownScreen()
{
    Main_MenuViewBase::tearDownScreen();
}

void Main_MenuView::setTimeoutValue(int value)
{
	//display the timeout value on the GUI
	Unicode::snprintf(textArea3Buffer, TEXTAREA3_SIZE, "%d", value);
	textArea3.invalidate();

	if(value == 0)
	{
		//application().gotoMeasurement_SingleScreenSlideTransitionWest();
		application().gotoShutting_OffScreenNoTransition();
	}
}
