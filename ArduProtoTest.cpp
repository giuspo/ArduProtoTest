#include <Arduino.h>
#include <ArduinoJson.h>

#include "Defines.h"

StaticJsonBuffer<JSON_BUFF_SIZE> _gJsonBuffer;

Stream *_gptMainStream = NULL;

void sendErrResp(EErrCode eErr)
{
  _gJsonBuffer.clear();

  JsonObject &ptResp = _gJsonBuffer.createObject();

  ptResp[CMD_TAG] = ERR_CMD;
  ptResp[ERR_RESP_TAG] = (int)eErr;

  ptResp.printTo(*_gptMainStream);
}

void sendOkResp()
{
  _gJsonBuffer.clear();

  JsonObject &ptResp = _gJsonBuffer.createObject();

  ptResp[CMD_TAG] = OK_CMD;

  ptResp.printTo(*_gptMainStream);
}

bool parseCommand(EErrCode &eErr)
{
  _gJsonBuffer.clear();
  JsonObject &ptObject = _gJsonBuffer.parseObject(*_gptMainStream);

  if(!ptObject.success())
  {
    eErr = NO_RECOGNIZED_ERR;

    return false;
  }

  const char *prgcCmd = ptObject[CMD_TAG];

  if(0 == strcmp(prgcCmd, ON_CMD))
  {
    byte byAddr = ptObject[ADDR_TAG];

    if(LED_ADDR == byAddr)
    {
      digitalWrite(LED_BUILTIN, 1);
    }

    sendOkResp();

    return true;
  }

  if(0 == strcmp(prgcCmd, OFF_CMD))
  {
    byte byAddr = ptObject[ADDR_TAG];

    if(LED_ADDR == byAddr)
    {
      digitalWrite(LED_BUILTIN, 0);
    }

    sendOkResp();

    return true;
  }

  return false;
}

void setup()
{
  _gptMainStream = &Serial;
  pinMode(LED_BUILTIN, OUTPUT);

  Serial.begin(9600);
  Serial.println("ArduProtoTest Ok...");
}

void loop()
{
  EErrCode eErr = NO_ERR;

  if(0 < Serial.available())
  {
    if(!parseCommand(eErr))
    {
      sendErrResp(eErr);

      return;
    }
  }
}

