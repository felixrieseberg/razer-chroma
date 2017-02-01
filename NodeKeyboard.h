#ifndef NODE_KEYBOARD_H
#define NODE_KEYBOARD_H

#include "SDK.h"

class NodeKeyboard{
  public:
    static void Init(v8::Local<v8::Object> target, SDK* instance);
  private:
    static NAN_METHOD(Set);
    static NAN_METHOD(SetCustom);
    static SDK* SDKInstance;
};

#endif
