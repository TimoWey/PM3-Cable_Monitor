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
	//textArea3.setWildcard1("test");
	gauge1.setValue(value);
	gauge1.invalidate();
}
