/*
 * usbd_midi_if.h
 *
 *  Created on: Dec 28, 2020
 *      Author: vincent
 */

#ifndef APP_USBD_MIDI_IF_H_
#define APP_USBD_MIDI_IF_H_

#ifdef __cplusplus
 extern "C" {
#endif

#include "usbd_midi.h"

extern USBD_MIDI_ItfTypeDef USBD_MIDI_Interface_fops_FS;

void MIDI_Message_Received(uint8_t status, uint8_t data1, uint8_t data2);



#ifdef __cplusplus
}
#endif




#endif /* APP_USBD_MIDI_IF_H_ */
