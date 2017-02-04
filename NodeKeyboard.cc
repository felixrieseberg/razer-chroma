#include "NodeKeyboard.h"
#include <iostream>

using namespace std;
using v8::FunctionTemplate;

SDK* NodeKeyboard::SDKInstance = NULL;

COLORREF ColorFromObject(v8::Local<v8::Object> obj){
    Nan::MaybeLocal<v8::Value> R, G, B;

    R = Nan::Get(obj, Nan::New("red").ToLocalChecked());
    G = Nan::Get(obj, Nan::New("green").ToLocalChecked());
    B = Nan::Get(obj, Nan::New("blue").ToLocalChecked());

    unsigned int Rint = (unsigned int)Nan::To<uint32_t>(R.ToLocalChecked()).FromMaybe(0);
    unsigned int Gint = (unsigned int)Nan::To<uint32_t>(G.ToLocalChecked()).FromMaybe(0);
    unsigned int Bint = (unsigned int)Nan::To<uint32_t>(B.ToLocalChecked()).FromMaybe(0);

    return RGB(Rint,Gint,Bint);
};

NAN_METHOD(NodeKeyboard::SetStatic) {
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

NAN_METHOD(NodeKeyboard::SetNone) {
    try {
        SDKInstance->CreateKeyboardEffect(ChromaSDK::Keyboard::CHROMA_NONE, NULL, NULL);
    } catch (...) {
        cout << "caught exception" << endl;  // this code is never called.
        cout << SDKInstance << endl;
    }
}

NAN_METHOD(NodeKeyboard::SetWave) {
    ChromaSDK::Keyboard::WAVE_EFFECT_TYPE Effect = {};

	v8::String::Utf8Value direction(info[0]->ToString());

	if (0 == std::strcmp(*direction, "leftToRight"))
	{
        Effect.Direction = Effect.DIRECTION_LEFT_TO_RIGHT;
	} else if (0 == std::strcmp(*direction, "rightToLeft"))
	{
		Effect.Direction = Effect.DIRECTION_RIGHT_TO_LEFT;
	} else
	{
		Effect.DIRECTION_NONE;
	}

    try {
        SDKInstance->CreateKeyboardEffect(ChromaSDK::Keyboard::CHROMA_WAVE, &Effect, NULL);
    } catch (...) {
        cout << "caught exception" << endl;  // this code is never called.
        cout << SDKInstance << endl;
    }
}

NAN_METHOD(NodeKeyboard::SetBreathing) {
    v8::Local<v8::Object> colorObj1 = info[0]->ToObject();
    v8::Local<v8::Object> colorObj2 = info[1]->ToObject();
    COLORREF crefColor1 = ColorFromObject(colorObj1);
    COLORREF crefColor2 = ColorFromObject(colorObj2);

    try {
        ChromaSDK::Keyboard::BREATHING_EFFECT_TYPE Effect = {};
		Effect.Type = Effect.TWO_COLORS;
		Effect.Color1 = crefColor1;
		Effect.Color2 = crefColor2;
        SDKInstance->CreateKeyboardEffect(ChromaSDK::Keyboard::CHROMA_BREATHING, &Effect, NULL);
    } catch (...) {
        cout << "caught exception" << endl;  // this code is never called.
        cout<<SDKInstance<<endl;
    }
}

NAN_METHOD(NodeKeyboard::SetBreathingRandom) {
    try {
        ChromaSDK::Keyboard::BREATHING_EFFECT_TYPE Effect = {};
		Effect.Type = Effect.RANDOM_COLORS;
        SDKInstance->CreateKeyboardEffect(ChromaSDK::Keyboard::CHROMA_BREATHING, &Effect, NULL);
    } catch (...) {
        cout << "caught exception" << endl;  // this code is never called.
        cout<<SDKInstance<<endl;
    }
}

NAN_METHOD(NodeKeyboard::SetStarlight) {
	v8::Local<v8::Object> colorObj1 = info[0]->ToObject();
	v8::Local<v8::Object> colorObj2 = info[1]->ToObject();
	COLORREF crefColor1 = ColorFromObject(colorObj1);
	COLORREF crefColor2 = ColorFromObject(colorObj2);

    try {
        ChromaSDK::Keyboard::STARLIGHT_EFFECT_TYPE Effect = {};
		Effect.Type = Effect.TWO_COLORS;
		Effect.Color1 = crefColor1;
		Effect.Color2 = crefColor2;
		Effect.Duration = Effect.DURATION_SHORT;
        SDKInstance->CreateKeyboardEffect(ChromaSDK::Keyboard::CHROMA_CUSTOM, &Effect, NULL);
    } catch (...) {
        cout << "caught exception" << endl;  // this code is never called.
        cout<<SDKInstance<<endl;
    }
}

NAN_METHOD(NodeKeyboard::SetReactive) {
    v8::Local<v8::Object> obj = info[0]->ToObject();
    COLORREF crefColor = ColorFromObject(obj);

    try {
        ChromaSDK::Keyboard::REACTIVE_EFFECT_TYPE Effect = {};
        Effect.Color = crefColor;
		Effect.Duration = Effect.DURATION_MEDIUM;
        SDKInstance->CreateKeyboardEffect(ChromaSDK::Keyboard::CHROMA_REACTIVE, &Effect, NULL);
    } catch (...) {
        cout << "caught exception" << endl;  // this code is never called.
        cout<<SDKInstance<<endl;
    }
};

NAN_METHOD(NodeKeyboard::SetSpectrumCycling) {
	try {
		ChromaSDK::Keyboard::CUSTOM_EFFECT_TYPE Effect = {};
		SDKInstance->CreateKeyboardEffect(ChromaSDK::Keyboard::CHROMA_SPECTRUMCYCLING, &Effect, NULL);
	}
	catch (...) {
		cout << "caught exception" << endl;  // this code is never called.
		cout << SDKInstance << endl;
	}
};

void NodeKeyboard::Init(v8::Local<v8::Object> target, SDK* instance) {
  NodeKeyboard::SDKInstance = instance;

  v8::Local<v8::Object> obj = Nan::New<v8::Object>();

  Nan::Set(obj, Nan::New("setStatic").ToLocalChecked(),
    Nan::GetFunction(Nan::New<FunctionTemplate>(NodeKeyboard::SetStatic)).ToLocalChecked());
  Nan::Set(obj, Nan::New("setNone").ToLocalChecked(),
    Nan::GetFunction(Nan::New<FunctionTemplate>(NodeKeyboard::SetNone)).ToLocalChecked());
  Nan::Set(obj, Nan::New("setCustom").ToLocalChecked(),
    Nan::GetFunction(Nan::New<FunctionTemplate>(NodeKeyboard::SetCustom)).ToLocalChecked());
  Nan::Set(obj, Nan::New("setWave").ToLocalChecked(),
    Nan::GetFunction(Nan::New<FunctionTemplate>(NodeKeyboard::SetWave)).ToLocalChecked());
  Nan::Set(obj, Nan::New("setBreathing").ToLocalChecked(),
    Nan::GetFunction(Nan::New<FunctionTemplate>(NodeKeyboard::SetBreathing)).ToLocalChecked());
  Nan::Set(obj, Nan::New("setBreathingRandom").ToLocalChecked(),
    Nan::GetFunction(Nan::New<FunctionTemplate>(NodeKeyboard::SetBreathingRandom)).ToLocalChecked());
  Nan::Set(obj, Nan::New("setStarlight").ToLocalChecked(),
    Nan::GetFunction(Nan::New<FunctionTemplate>(NodeKeyboard::SetStarlight)).ToLocalChecked());
  Nan::Set(obj, Nan::New("setReactive").ToLocalChecked(),
    Nan::GetFunction(Nan::New<FunctionTemplate>(NodeKeyboard::SetReactive)).ToLocalChecked());
  Nan::Set(obj, Nan::New("setSpectrumCycling").ToLocalChecked(),
	  Nan::GetFunction(Nan::New<FunctionTemplate>(NodeKeyboard::SetSpectrumCycling)).ToLocalChecked());
  Nan::Set(target, Nan::New("Keyboard").ToLocalChecked(), obj);
}

