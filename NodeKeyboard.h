#ifndef NODE_KEYBOARD_H
#define NODE_KEYBOARD_H

#include "SDK.h"

class NodeKeyboard{
  public:
    static void Init(v8::Local<v8::Object> target, SDK* instance);
  private:
    static NAN_METHOD(SetStatic);
    static NAN_METHOD(SetCustom);
    static NAN_METHOD(SetNone);
    static NAN_METHOD(SetWave);
    static NAN_METHOD(SetBreathing);
    static NAN_METHOD(SetBreathingRandom);
    static NAN_METHOD(SetStarlight);
    static NAN_METHOD(SetReactive);
    static NAN_METHOD(SetSpectrumCycling);
    static SDK* SDKInstance;
};

#endif
