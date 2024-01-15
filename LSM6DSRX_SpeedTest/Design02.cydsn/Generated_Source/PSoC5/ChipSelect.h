/*******************************************************************************
* File Name: ChipSelect.h  
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

#if !defined(CY_PINS_ChipSelect_H) /* Pins ChipSelect_H */
#define CY_PINS_ChipSelect_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "ChipSelect_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 ChipSelect__PORT == 15 && ((ChipSelect__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    ChipSelect_Write(uint8 value);
void    ChipSelect_SetDriveMode(uint8 mode);
uint8   ChipSelect_ReadDataReg(void);
uint8   ChipSelect_Read(void);
void    ChipSelect_SetInterruptMode(uint16 position, uint16 mode);
uint8   ChipSelect_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the ChipSelect_SetDriveMode() function.
     *  @{
     */
        #define ChipSelect_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define ChipSelect_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define ChipSelect_DM_RES_UP          PIN_DM_RES_UP
        #define ChipSelect_DM_RES_DWN         PIN_DM_RES_DWN
        #define ChipSelect_DM_OD_LO           PIN_DM_OD_LO
        #define ChipSelect_DM_OD_HI           PIN_DM_OD_HI
        #define ChipSelect_DM_STRONG          PIN_DM_STRONG
        #define ChipSelect_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define ChipSelect_MASK               ChipSelect__MASK
#define ChipSelect_SHIFT              ChipSelect__SHIFT
#define ChipSelect_WIDTH              1u

/* Interrupt constants */
#if defined(ChipSelect__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in ChipSelect_SetInterruptMode() function.
     *  @{
     */
        #define ChipSelect_INTR_NONE      (uint16)(0x0000u)
        #define ChipSelect_INTR_RISING    (uint16)(0x0001u)
        #define ChipSelect_INTR_FALLING   (uint16)(0x0002u)
        #define ChipSelect_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define ChipSelect_INTR_MASK      (0x01u) 
#endif /* (ChipSelect__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define ChipSelect_PS                     (* (reg8 *) ChipSelect__PS)
/* Data Register */
#define ChipSelect_DR                     (* (reg8 *) ChipSelect__DR)
/* Port Number */
#define ChipSelect_PRT_NUM                (* (reg8 *) ChipSelect__PRT) 
/* Connect to Analog Globals */                                                  
#define ChipSelect_AG                     (* (reg8 *) ChipSelect__AG)                       
/* Analog MUX bux enable */
#define ChipSelect_AMUX                   (* (reg8 *) ChipSelect__AMUX) 
/* Bidirectional Enable */                                                        
#define ChipSelect_BIE                    (* (reg8 *) ChipSelect__BIE)
/* Bit-mask for Aliased Register Access */
#define ChipSelect_BIT_MASK               (* (reg8 *) ChipSelect__BIT_MASK)
/* Bypass Enable */
#define ChipSelect_BYP                    (* (reg8 *) ChipSelect__BYP)
/* Port wide control signals */                                                   
#define ChipSelect_CTL                    (* (reg8 *) ChipSelect__CTL)
/* Drive Modes */
#define ChipSelect_DM0                    (* (reg8 *) ChipSelect__DM0) 
#define ChipSelect_DM1                    (* (reg8 *) ChipSelect__DM1)
#define ChipSelect_DM2                    (* (reg8 *) ChipSelect__DM2) 
/* Input Buffer Disable Override */
#define ChipSelect_INP_DIS                (* (reg8 *) ChipSelect__INP_DIS)
/* LCD Common or Segment Drive */
#define ChipSelect_LCD_COM_SEG            (* (reg8 *) ChipSelect__LCD_COM_SEG)
/* Enable Segment LCD */
#define ChipSelect_LCD_EN                 (* (reg8 *) ChipSelect__LCD_EN)
/* Slew Rate Control */
#define ChipSelect_SLW                    (* (reg8 *) ChipSelect__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define ChipSelect_PRTDSI__CAPS_SEL       (* (reg8 *) ChipSelect__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define ChipSelect_PRTDSI__DBL_SYNC_IN    (* (reg8 *) ChipSelect__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define ChipSelect_PRTDSI__OE_SEL0        (* (reg8 *) ChipSelect__PRTDSI__OE_SEL0) 
#define ChipSelect_PRTDSI__OE_SEL1        (* (reg8 *) ChipSelect__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define ChipSelect_PRTDSI__OUT_SEL0       (* (reg8 *) ChipSelect__PRTDSI__OUT_SEL0) 
#define ChipSelect_PRTDSI__OUT_SEL1       (* (reg8 *) ChipSelect__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define ChipSelect_PRTDSI__SYNC_OUT       (* (reg8 *) ChipSelect__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(ChipSelect__SIO_CFG)
    #define ChipSelect_SIO_HYST_EN        (* (reg8 *) ChipSelect__SIO_HYST_EN)
    #define ChipSelect_SIO_REG_HIFREQ     (* (reg8 *) ChipSelect__SIO_REG_HIFREQ)
    #define ChipSelect_SIO_CFG            (* (reg8 *) ChipSelect__SIO_CFG)
    #define ChipSelect_SIO_DIFF           (* (reg8 *) ChipSelect__SIO_DIFF)
#endif /* (ChipSelect__SIO_CFG) */

/* Interrupt Registers */
#if defined(ChipSelect__INTSTAT)
    #define ChipSelect_INTSTAT            (* (reg8 *) ChipSelect__INTSTAT)
    #define ChipSelect_SNAP               (* (reg8 *) ChipSelect__SNAP)
    
	#define ChipSelect_0_INTTYPE_REG 		(* (reg8 *) ChipSelect__0__INTTYPE)
#endif /* (ChipSelect__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_ChipSelect_H */


/* [] END OF FILE */
