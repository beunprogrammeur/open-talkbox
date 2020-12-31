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

void MIDI_CC_Received(uint8_t channel, uint8_t code, uint8_t value);
void MIDI_Note_On_Received(uint8_t channel, uint8_t key, uint8_t velocity);
void MIDI_Note_Off_received(uint8_t channel, uint8_t key);


#ifdef __cplusplus
}
#endif




#endif /* APP_USBD_MIDI_IF_H_ */
