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
	gauge1.setValue(value);
	gauge1.invalidate();

	//Unicode::snprintf(textAreaBuffer3, TEXTAREA_SIZE, "%d", value);
}