/*
 * User_F2837xD_EPWM.h
 *
 *  Created on: 2019Äê4ÔÂ12ÈÕ
 *      Author: Downstream
 */

#ifndef INCLUDE_USER_F2837XD_EPWM_EQEP_H_
#define INCLUDE_USER_F2837XD_EPWM_EQEP_H_

void reset_pull_up(void);
void ConfigureEQep(void);
void ConfigureEPwm(void);

interrupt void OffsetISR(void);
interrupt void MainISR(void);

void OneShot_Protection(void);
void PosEncoderSuite(void);

#endif /* INCLUDE_USER_F2837XD_EPWM_EQEP_H_ */
