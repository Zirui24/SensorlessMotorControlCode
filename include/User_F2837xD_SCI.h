/*
 * User_F2837xD__SCI.h
 *
 *  Created on: 2019Äê4ÔÂ12ÈÕ
 *      Author: Downstream
 */

#ifndef INCLUDE_USER_F2837XD_SCI_H_
#define INCLUDE_USER_F2837XD_SCI_H_

void Configure_Sci_A(void);
void InitSciaGPIO(void);
void scia_init_fifo(void);
void scia_ximt(unsigned char send);
void shanwai_sci(short *data);



#endif /* INCLUDE_USER_F2837XD_SCI_H_ */
