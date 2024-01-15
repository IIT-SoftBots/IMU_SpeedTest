/*******************************************************************************
* File Name: ChipSelect_2.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_ChipSelect_2_H) /* Pins ChipSelect_2_H */
#define CY_PINS_ChipSelect_2_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "ChipSelect_2_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 ChipSelect_2__PORT == 15 && ((ChipSelect_2__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    ChipSelect_2_Write(uint8 value);
void    ChipSelect_2_SetDriveMode(uint8 mode);
uint8   ChipSelect_2_ReadDataReg(void);
uint8   ChipSelect_2_Read(void);
void    ChipSelect_2_SetInterruptMode(uint16 position, uint16 mode);
uint8   ChipSelect_2_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the ChipSelect_2_SetDriveMode() function.
     *  @{
     */
        #define ChipSelect_2_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define ChipSelect_2_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define ChipSelect_2_DM_RES_UP          PIN_DM_RES_UP
        #define ChipSelect_2_DM_RES_DWN         PIN_DM_RES_DWN
        #define ChipSelect_2_DM_OD_LO           PIN_DM_OD_LO
        #define ChipSelect_2_DM_OD_HI           PIN_DM_OD_HI
        #define ChipSelect_2_DM_STRONG          PIN_DM_STRONG
        #define ChipSelect_2_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define ChipSelect_2_MASK               ChipSelect_2__MASK
#define ChipSelect_2_SHIFT              ChipSelect_2__SHIFT
#define ChipSelect_2_WIDTH              1u

/* Interrupt constants */
#if defined(ChipSelect_2__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in ChipSelect_2_SetInterruptMode() function.
     *  @{
     */
        #define ChipSelect_2_INTR_NONE      (uint16)(0x0000u)
        #define ChipSelect_2_INTR_RISING    (uint16)(0x0001u)
        #define ChipSelect_2_INTR_FALLING   (uint16)(0x0002u)
        #define ChipSelect_2_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define ChipSelect_2_INTR_MASK      (0x01u) 
#endif /* (ChipSelect_2__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define ChipSelect_2_PS                     (* (reg8 *) ChipSelect_2__PS)
/* Data Register */
#define ChipSelect_2_DR                     (* (reg8 *) ChipSelect_2__DR)
/* Port Number */
#define ChipSelect_2_PRT_NUM                (* (reg8 *) ChipSelect_2__PRT) 
/* Connect to Analog Globals */                                                  
#define ChipSelect_2_AG                     (* (reg8 *) ChipSelect_2__AG)                       
/* Analog MUX bux enable */
#define ChipSelect_2_AMUX                   (* (reg8 *) ChipSelect_2__AMUX) 
/* Bidirectional Enable */                                                        
#define ChipSelect_2_BIE                    (* (reg8 *) ChipSelect_2__BIE)
/* Bit-mask for Aliased Register Access */
#define ChipSelect_2_BIT_MASK               (* (reg8 *) ChipSelect_2__BIT_MASK)
/* Bypass Enable */
#define ChipSelect_2_BYP                    (* (reg8 *) ChipSelect_2__BYP)
/* Port wide control signals */                                                   
#define ChipSelect_2_CTL                    (* (reg8 *) ChipSelect_2__CTL)
/* Drive Modes */
#define ChipSelect_2_DM0                    (* (reg8 *) ChipSelect_2__DM0) 
#define ChipSelect_2_DM1                    (* (reg8 *) ChipSelect_2__DM1)
#define ChipSelect_2_DM2                    (* (reg8 *) ChipSelect_2__DM2) 
/* Input Buffer Disable Override */
#define ChipSelect_2_INP_DIS                (* (reg8 *) ChipSelect_2__INP_DIS)
/* LCD Common or Segment Drive */
#define ChipSelect_2_LCD_COM_SEG            (* (reg8 *) ChipSelect_2__LCD_COM_SEG)
/* Enable Segment LCD */
#define ChipSelect_2_LCD_EN                 (* (reg8 *) ChipSelect_2__LCD_EN)
/* Slew Rate Control */
#define ChipSelect_2_SLW                    (* (reg8 *) ChipSelect_2__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define ChipSelect_2_PRTDSI__CAPS_SEL       (* (reg8 *) ChipSelect_2__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define ChipSelect_2_PRTDSI__DBL_SYNC_IN    (* (reg8 *) ChipSelect_2__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define ChipSelect_2_PRTDSI__OE_SEL0        (* (reg8 *) ChipSelect_2__PRTDSI__OE_SEL0) 
#define ChipSelect_2_PRTDSI__OE_SEL1        (* (reg8 *) ChipSelect_2__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define ChipSelect_2_PRTDSI__OUT_SEL0       (* (reg8 *) ChipSelect_2__PRTDSI__OUT_SEL0) 
#define ChipSelect_2_PRTDSI__OUT_SEL1       (* (reg8 *) ChipSelect_2__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define ChipSelect_2_PRTDSI__SYNC_OUT       (* (reg8 *) ChipSelect_2__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(ChipSelect_2__SIO_CFG)
    #define ChipSelect_2_SIO_HYST_EN        (* (reg8 *) ChipSelect_2__SIO_HYST_EN)
    #define ChipSelect_2_SIO_REG_HIFREQ     (* (reg8 *) ChipSelect_2__SIO_REG_HIFREQ)
    #define ChipSelect_2_SIO_CFG            (* (reg8 *) ChipSelect_2__SIO_CFG)
    #define ChipSelect_2_SIO_DIFF           (* (reg8 *) ChipSelect_2__SIO_DIFF)
#endif /* (ChipSelect_2__SIO_CFG) */

/* Interrupt Registers */
#if defined(ChipSelect_2__INTSTAT)
    #define ChipSelect_2_INTSTAT            (* (reg8 *) ChipSelect_2__INTSTAT)
    #define ChipSelect_2_SNAP               (* (reg8 *) ChipSelect_2__SNAP)
    
	#define ChipSelect_2_0_INTTYPE_REG 		(* (reg8 *) ChipSelect_2__0__INTTYPE)
#endif /* (ChipSelect_2__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_ChipSelect_2_H */


/* [] END OF FILE */
