******************************************************************************
* @file    readme.txt
* @author  MCD Application Team
* @version 3.1
* @date    16-DEC-2022   
* @brief  MB1075 board design project package
******************************************************************************
* COPYRIGHT(c) 2022 STMicroelectronics
*
* The Open Platform License Agreement (“Agreement”) is a binding legal contract
* between you ("You") and STMicroelectronics International N.V. (“ST”), a
* company incorporated under the laws of the Netherlands acting for the purpose
* of this Agreement through its Swiss branch 39, Chemin du Champ des Filles,
* 1228 Plan-les-Ouates, Geneva, Switzerland.
*
* By using the enclosed reference designs, schematics, PC board layouts, and
* documentation, in hardcopy or CAD tool file format (collectively, the
* “Reference Material”), You are agreeing to be bound by the terms and
* conditions of this Agreement. Do not use the Reference Material until You
* have read and agreed to this Agreement terms and conditions. The use of
* the Reference Material automatically implies the acceptance of the Agreement
* terms and conditions.
*
* The complete Open Platform License Agreement can be found on www.st.com/opla.
******************************************************************************

========================
* 1.0 - 06-September-2013
========================
    + First official release.
    + MB1075.PCB is CADSTAR format

========================
* 2.0 - 12-JUN-2020
========================
    + Change files structure
    + Add MB1075C folder with main following changes
        +STM32F103C8T6 replaced by STM32F103CBT6 for ST-LINK/V2-B
        +mbed-enabled, SB11 and SB15 closed
        +version B & C share same design,only update the silkscreen of gerber file 

       +Add MB1075D folder
          +this is an internal only revision.

========================
* 3.0 - 30-SEP-2020
========================
    + Add MB1075E folder with main following changes
        +U3: L3GD20 replace by I3G4250D and  add R75, C54
        +keep old STMPE811QTR and add SX8651 for 2 footprints, and add U9, C55 and R74 for SX8651, keep the original STMPE811QTR circuit
        +CN5: SF-TC240T-9370-T replace by FRD240C48003-B: swap pin1 and pin3 for YU and YD,  connect pin8 with 3V
        +update solder bridge:
– OFF: SB3, SB5, SB7, SB13, SB18
– ON: SB4, SB6, SB8, SB14, SB19
        +update CN6 footprint

========================
* 3.1 - 16-DEC-2022 
========================
    + Update templates.

******************* (C) COPYRIGHT 2022 STMicroelectronics *****END OF FILE
