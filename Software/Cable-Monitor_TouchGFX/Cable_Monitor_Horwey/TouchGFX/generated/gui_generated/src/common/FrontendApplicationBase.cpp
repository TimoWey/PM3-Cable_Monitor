/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#include <new>
#include <gui_generated/common/FrontendApplicationBase.hpp>
#include <gui/common/FrontendHeap.hpp>
#include <touchgfx/transitions/NoTransition.hpp>
#include <texts/TextKeysAndLanguages.hpp>
#include <touchgfx/Texts.hpp>
#include <touchgfx/hal/HAL.hpp>
#include <platform/driver/lcd/LCD16bpp.hpp>
#include <gui/main_menu_screen/Main_MenuView.hpp>
#include <gui/main_menu_screen/Main_MenuPresenter.hpp>
#include <gui/measurement_screen/MeasurementView.hpp>
#include <gui/measurement_screen/MeasurementPresenter.hpp>
#include <gui/measurement_single_screen/Measurement_SingleView.hpp>
#include <gui/measurement_single_screen/Measurement_SinglePresenter.hpp>
#include <gui/measurement_single_display_screen/Measurement_Single_DisplayView.hpp>
#include <gui/measurement_single_display_screen/Measurement_Single_DisplayPresenter.hpp>
#include <gui/measurement_accurate_display_screen/Measurement_Accurate_DisplayView.hpp>
#include <gui/measurement_accurate_display_screen/Measurement_Accurate_DisplayPresenter.hpp>
#include <gui/measurement_accurate_screen/Measurement_AccurateView.hpp>
#include <gui/measurement_accurate_screen/Measurement_AccuratePresenter.hpp>
#include <gui/calibration_screen/CalibrationView.hpp>
#include <gui/calibration_screen/CalibrationPresenter.hpp>
#include <gui/project_info_screen/Project_InfoView.hpp>
#include <gui/project_info_screen/Project_InfoPresenter.hpp>

using namespace touchgfx;

FrontendApplicationBase::FrontendApplicationBase(Model& m, FrontendHeap& heap)
    : touchgfx::MVPApplication(),
      transitionCallback(),
      frontendHeap(heap),
      model(m)
{
    touchgfx::HAL::getInstance()->setDisplayOrientation(touchgfx::ORIENTATION_PORTRAIT);
    touchgfx::Texts::setLanguage(GB);
    reinterpret_cast<touchgfx::LCD16bpp&>(touchgfx::HAL::lcd()).enableTextureMapperAll();
    reinterpret_cast<touchgfx::LCD16bpp&>(touchgfx::HAL::lcd()).enableDecompressorL8_All();
}

/*
 * Screen Transition Declarations
 */

// Main_Menu

void FrontendApplicationBase::gotoMain_MenuScreenNoTransition()
{
    transitionCallback = touchgfx::Callback<FrontendApplicationBase>(this, &FrontendApplicationBase::gotoMain_MenuScreenNoTransitionImpl);
    pendingScreenTransitionCallback = &transitionCallback;
}

void FrontendApplicationBase::gotoMain_MenuScreenNoTransitionImpl()
{
    touchgfx::makeTransition<Main_MenuView, Main_MenuPresenter, touchgfx::NoTransition, Model >(&currentScreen, &currentPresenter, frontendHeap, &currentTransition, &model);
}

void FrontendApplicationBase::gotoMain_MenuScreenWipeTransitionWest()
{
    transitionCallback = touchgfx::Callback<FrontendApplicationBase>(this, &FrontendApplicationBase::gotoMain_MenuScreenWipeTransitionWestImpl);
    pendingScreenTransitionCallback = &transitionCallback;
}

void FrontendApplicationBase::gotoMain_MenuScreenWipeTransitionWestImpl()
{
    touchgfx::makeTransition<Main_MenuView, Main_MenuPresenter, touchgfx::WipeTransition<WEST>, Model >(&currentScreen, &currentPresenter, frontendHeap, &currentTransition, &model);
}

// Measurement

void FrontendApplicationBase::gotoMeasurementScreenWipeTransitionEast()
{
    transitionCallback = touchgfx::Callback<FrontendApplicationBase>(this, &FrontendApplicationBase::gotoMeasurementScreenWipeTransitionEastImpl);
    pendingScreenTransitionCallback = &transitionCallback;
}

void FrontendApplicationBase::gotoMeasurementScreenWipeTransitionEastImpl()
{
    touchgfx::makeTransition<MeasurementView, MeasurementPresenter, touchgfx::WipeTransition<EAST>, Model >(&currentScreen, &currentPresenter, frontendHeap, &currentTransition, &model);
}

void FrontendApplicationBase::gotoMeasurementScreenWipeTransitionWest()
{
    transitionCallback = touchgfx::Callback<FrontendApplicationBase>(this, &FrontendApplicationBase::gotoMeasurementScreenWipeTransitionWestImpl);
    pendingScreenTransitionCallback = &transitionCallback;
}

void FrontendApplicationBase::gotoMeasurementScreenWipeTransitionWestImpl()
{
    touchgfx::makeTransition<MeasurementView, MeasurementPresenter, touchgfx::WipeTransition<WEST>, Model >(&currentScreen, &currentPresenter, frontendHeap, &currentTransition, &model);
}

// Measurement_Single

void FrontendApplicationBase::gotoMeasurement_SingleScreenWipeTransitionEast()
{
    transitionCallback = touchgfx::Callback<FrontendApplicationBase>(this, &FrontendApplicationBase::gotoMeasurement_SingleScreenWipeTransitionEastImpl);
    pendingScreenTransitionCallback = &transitionCallback;
}

void FrontendApplicationBase::gotoMeasurement_SingleScreenWipeTransitionEastImpl()
{
    touchgfx::makeTransition<Measurement_SingleView, Measurement_SinglePresenter, touchgfx::WipeTransition<EAST>, Model >(&currentScreen, &currentPresenter, frontendHeap, &currentTransition, &model);
}

void FrontendApplicationBase::gotoMeasurement_SingleScreenSlideTransitionWest()
{
    transitionCallback = touchgfx::Callback<FrontendApplicationBase>(this, &FrontendApplicationBase::gotoMeasurement_SingleScreenSlideTransitionWestImpl);
    pendingScreenTransitionCallback = &transitionCallback;
}

void FrontendApplicationBase::gotoMeasurement_SingleScreenSlideTransitionWestImpl()
{
    touchgfx::makeTransition<Measurement_SingleView, Measurement_SinglePresenter, touchgfx::SlideTransition<WEST>, Model >(&currentScreen, &currentPresenter, frontendHeap, &currentTransition, &model);
}

// Measurement_Single_Display

void FrontendApplicationBase::gotoMeasurement_Single_DisplayScreenSlideTransitionEast()
{
    transitionCallback = touchgfx::Callback<FrontendApplicationBase>(this, &FrontendApplicationBase::gotoMeasurement_Single_DisplayScreenSlideTransitionEastImpl);
    pendingScreenTransitionCallback = &transitionCallback;
}

void FrontendApplicationBase::gotoMeasurement_Single_DisplayScreenSlideTransitionEastImpl()
{
    touchgfx::makeTransition<Measurement_Single_DisplayView, Measurement_Single_DisplayPresenter, touchgfx::SlideTransition<EAST>, Model >(&currentScreen, &currentPresenter, frontendHeap, &currentTransition, &model);
}

// Calibration

void FrontendApplicationBase::gotoCalibrationScreenWipeTransitionEast()
{
    transitionCallback = touchgfx::Callback<FrontendApplicationBase>(this, &FrontendApplicationBase::gotoCalibrationScreenWipeTransitionEastImpl);
    pendingScreenTransitionCallback = &transitionCallback;
}

void FrontendApplicationBase::gotoCalibrationScreenWipeTransitionEastImpl()
{
    touchgfx::makeTransition<CalibrationView, CalibrationPresenter, touchgfx::WipeTransition<EAST>, Model >(&currentScreen, &currentPresenter, frontendHeap, &currentTransition, &model);
}

// Project_Info

void FrontendApplicationBase::gotoProject_InfoScreenWipeTransitionEast()
{
    transitionCallback = touchgfx::Callback<FrontendApplicationBase>(this, &FrontendApplicationBase::gotoProject_InfoScreenWipeTransitionEastImpl);
    pendingScreenTransitionCallback = &transitionCallback;
}

void FrontendApplicationBase::gotoProject_InfoScreenWipeTransitionEastImpl()
{
    touchgfx::makeTransition<Project_InfoView, Project_InfoPresenter, touchgfx::WipeTransition<EAST>, Model >(&currentScreen, &currentPresenter, frontendHeap, &currentTransition, &model);
}
