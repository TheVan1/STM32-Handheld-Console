/*
 * ssd_1306_drivers.h
 *
 *  Created on: 16 Dec 2025
 *      Author: Vanessa
 */

/* 
this is a really ugly header file, but its written to compile both for C and C++
as we need to be able to call I2C_SSD1306_Screen_Init from C, and the others from C++
*/

#ifndef INC_SSD_1306_H
#define INC_SSD_1306_H

#include <stdint.h>

#ifdef __cplusplus
#include <array>
#endif /* __cplusplus */
#endif /* INC_SSD_1306_H_ */

#ifndef __SSD_1306_h
#define __SSD_1306_h

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

void I2C_SSD1306_Screen_Init(I2C_HandleTypeDef *hi2c);

#ifdef __cplusplus
}


void I2C_SSD1306_Update_Whole_Display(std::array<std::array<uint8_t, 8>, 128>* frame);
void I2C_SSD1306_Screen_Transmit(uint16_t data_len, uint8_t *data);

#endif /* __cplusplus */
#endif /*__SSD_1306_H*/
