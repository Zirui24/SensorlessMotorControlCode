/*
 * User_F2837xD_DAC.h
 *
 *  Created on: 2019Äê4ÔÂ11ÈÕ
 *      Author: Downstream
 */

#ifndef INCLUDE_USER_F2837XD_DAC_H_
#define INCLUDE_USER_F2837XD_DAC_H_

#include "F2837xD_device.h"



//definitions for selecting DAC reference
#define DACA            1
#define DACB            2
#define DACC            3


//definitions for selecting DAC reference
#define REFERENCE_VDAC  0
#define REFERENCE_VREF  1

//specify configuration
#define REFERENCE   REFERENCE_VDAC
#define DAC_NUM     DACA


void Configure_DAC();
void ConfigureDAC_single(Uint16 dac_num);
void DAC_Output(Uint16 dac_num,Uint16 DAC_value);

#endif /* INCLUDE_USER_F2837XD_DAC_H_ */
