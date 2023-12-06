/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#ifndef FRONTENDAPPLICATIONBASE_HPP
#define FRONTENDAPPLICATIONBASE_HPP

#include <mvp/MVPApplication.hpp>
#include <gui/model/Model.hpp>

class FrontendHeap;

class FrontendApplicationBase : public touchgfx::MVPApplication
{
public:
    FrontendApplicationBase(Model& m, FrontendHeap& heap);
    virtual ~FrontendApplicationBase() { }

    virtual void changeToStartScreen()
    {
        gotoMain_MenuScreenNoTransition();
    }

    // Main_Menu
    void gotoMain_MenuScreenNoTransition();

    void gotoMain_MenuScreenWipeTransitionWest();

    // Measurement
    void gotoMeasurementScreenWipeTransitionEast();

    void gotoMeasurementScreenWipeTransitionWest();

    // Measurement_Single
    void gotoMeasurement_SingleScreenWipeTransitionEast();

    // Measurement_Single_Display_1P
    void gotoMeasurement_Single_Display_1PScreenWipeTransitionEast();

    // Measurement_Single_Display_3P
    void gotoMeasurement_Single_Display_3PScreenWipeTransitionEast();

    // Measurement_Accurate
    void gotoMeasurement_AccurateScreenWipeTransitionEast();

    void gotoMeasurement_AccurateScreenWipeTransitionWest();

    // Measurement_Accurate_Display
    void gotoMeasurement_Accurate_DisplayScreenWipeTransitionEast();

    // Measurement_Accurate_Display_2
    void gotoMeasurement_Accurate_Display_2ScreenWipeTransitionEast();

    // Calibration
    void gotoCalibrationScreenWipeTransitionEast();

    void gotoCalibrationScreenWipeTransitionWest();

    // Calibration_Pad
    void gotoCalibration_PadScreenWipeTransitionEast();

    // Project_Info
    void gotoProject_InfoScreenWipeTransitionEast();

    // Shutting_Off
    void gotoShutting_OffScreenNoTransition();

protected:
    touchgfx::Callback<FrontendApplicationBase> transitionCallback;
    FrontendHeap& frontendHeap;
    Model& model;

    // Main_Menu
    void gotoMain_MenuScreenNoTransitionImpl();

    void gotoMain_MenuScreenWipeTransitionWestImpl();

    // Measurement
    void gotoMeasurementScreenWipeTransitionEastImpl();

    void gotoMeasurementScreenWipeTransitionWestImpl();

    // Measurement_Single
    void gotoMeasurement_SingleScreenWipeTransitionEastImpl();

    // Measurement_Single_Display_1P
    void gotoMeasurement_Single_Display_1PScreenWipeTransitionEastImpl();

    // Measurement_Single_Display_3P
    void gotoMeasurement_Single_Display_3PScreenWipeTransitionEastImpl();

    // Measurement_Accurate
    void gotoMeasurement_AccurateScreenWipeTransitionEastImpl();

    void gotoMeasurement_AccurateScreenWipeTransitionWestImpl();

    // Measurement_Accurate_Display
    void gotoMeasurement_Accurate_DisplayScreenWipeTransitionEastImpl();

    // Measurement_Accurate_Display_2
    void gotoMeasurement_Accurate_Display_2ScreenWipeTransitionEastImpl();

    // Calibration
    void gotoCalibrationScreenWipeTransitionEastImpl();

    void gotoCalibrationScreenWipeTransitionWestImpl();

    // Calibration_Pad
    void gotoCalibration_PadScreenWipeTransitionEastImpl();

    // Project_Info
    void gotoProject_InfoScreenWipeTransitionEastImpl();

    // Shutting_Off
    void gotoShutting_OffScreenNoTransitionImpl();
};

#endif // FRONTENDAPPLICATIONBASE_HPP
