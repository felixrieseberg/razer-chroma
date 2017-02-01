#include "NodeKeyboard.h"
#include <iostream>

using namespace std;
using v8::FunctionTemplate;

SDK* NodeKeyboard::SDKInstance = NULL;

COLORREF ColorFromObject(v8::Local<v8::Object> obj){
    Nan::MaybeLocal<v8::Value> R, G, B;

    R = Nan::Get(obj, Nan::New("Red").ToLocalChecked());
    G = Nan::Get(obj, Nan::New("Green").ToLocalChecked());
    B = Nan::Get(obj, Nan::New("Blue").ToLocalChecked());

    unsigned int Rint = (unsigned int)Nan::To<uint32_t>(R.ToLocalChecked()).FromMaybe(0);
    unsigned int Gint = (unsigned int)Nan::To<uint32_t>(G.ToLocalChecked()).FromMaybe(0);
    unsigned int Bint = (unsigned int)Nan::To<uint32_t>(B.ToLocalChecked()).FromMaybe(0);

    return RGB(Rint,Gint,Bint);
};

NAN_METHOD(NodeKeyboard::Set) {
    v8::Local<v8::Object> obj = info[0]->ToObject();
    COLORREF crefColor = ColorFromObject(obj);

    try {
        ChromaSDK::Keyboard::STATIC_EFFECT_TYPE Effect = {};
        Effect.Color = crefColor;
        SDKInstance->CreateKeyboardEffect(ChromaSDK::Keyboard::CHROMA_STATIC, &Effect, NULL);
    } catch (...) {
        cout << "caught exception" << endl;  // this code is never called.
        cout<<SDKInstance<<endl;
    }
};

NAN_METHOD(NodeKeyboard::SetCustom) {
    ChromaSDK::Keyboard::CUSTOM_EFFECT_TYPE Effect = {};

    v8::Local<v8::Object> obj = info[0]->ToObject();
    v8::Local<v8::Array> rows = v8::Local<v8::Array>::Cast(obj);

    for (unsigned int r = 0; r < rows->Length(); ++r) {
        v8::Local<v8::Array> cols = v8::Local<v8::Array>::Cast(rows->Get(r));
        for (unsigned int c = 0; c < cols->Length(); ++c) {
            v8::Local<v8::Object> obj = cols->Get(c)->ToObject();
            Effect.Color[r][c] = ColorFromObject(obj);
        }
    }

    try {
        SDKInstance->CreateKeyboardEffect(ChromaSDK::Keyboard::CHROMA_CUSTOM, &Effect, NULL);
    } catch (...) {
        cout << "caught exception" << endl;  // this code is never called.
        cout << SDKInstance << endl;
    }
}

void NodeKeyboard::Init(v8::Local<v8::Object> target, SDK* instance) {
  NodeKeyboard::SDKInstance = instance;

  v8::Local<v8::Object> obj = Nan::New<v8::Object>();

  Nan::Set(obj, Nan::New("Set").ToLocalChecked(),
    Nan::GetFunction(Nan::New<FunctionTemplate>(NodeKeyboard::Set)).ToLocalChecked());
  Nan::Set(obj, Nan::New("SetCustom").ToLocalChecked(),
    Nan::GetFunction(Nan::New<FunctionTemplate>(NodeKeyboard::SetCustom)).ToLocalChecked());
  Nan::Set(target, Nan::New("Keyboard").ToLocalChecked(), obj);
}

