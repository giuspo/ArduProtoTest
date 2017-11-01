/*
 * Defines.h
 *
 *  Created on: 22 ott 2017
 *      Author: giulio
 */
#ifndef DEFINES_H_
#define DEFINES_H_

#define JSON_BUFF_SIZE (JSON_OBJECT_SIZE(2) + 20)

#define CMD_TAG         "cmd"
#define ADDR_TAG        "addr"
#define ERR_RESP_TAG    "err"

#define OK_CMD      "Ok"
#define ERR_CMD     "Err"
#define ON_CMD      "On"
#define OFF_CMD     "Off"

#define LED_ADDR    0x01

enum EErrCode
{
  NO_ERR = 0,
  MALFORMED_ERR,
  NO_RECOGNIZED_ERR,
};

#endif /* DEFINES_H_ */
