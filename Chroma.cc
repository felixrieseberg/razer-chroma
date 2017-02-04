#include "SDK.h"
#include "NodeKeyboard.h"
#include <iostream>

using namespace std;
using v8::FunctionTemplate;

SDK SDKInstance;

NAN_METHOD(Initialize) {
    if (SDKInstance.m_ChromaSDKModule == NULL) {
        SDKInstance.m_ChromaSDKModule = LoadLibrary("RzChromaSDK64.dll");
        if (SDKInstance.m_ChromaSDKModule == NULL)
        {
          SDKInstance.m_ChromaSDKModule = LoadLibrary("RzChromaSDK.dll");
        }
    }

    if (SDKInstance.Init == NULL && SDKInstance.m_ChromaSDKModule!=NULL) {
        RZRESULT Result = RZRESULT_INVALID;
        SDKInstance.Init = (INIT)GetProcAddress(SDKInstance.m_ChromaSDKModule, "Init");

        if (SDKInstance.Init)
        {
          Result = SDKInstance.Init();

          if (Result == RZRESULT_SUCCESS)
          {

              SDKInstance.CreateEffect = (CREATEEFFECT)GetProcAddress (SDKInstance.m_ChromaSDKModule, "CreateEffect");
              SDKInstance.CreateKeyboardEffect = (CREATEKEYBOARDEFFECT)GetProcAddress (SDKInstance.m_ChromaSDKModule, "CreateKeyboardEffect");
              SDKInstance.CreateMouseEffect = (CREATEMOUSEEFFECT)GetProcAddress (SDKInstance.m_ChromaSDKModule, "CreateMouseEffect");
              SDKInstance.CreateHeadsetEffect = (CREATEHEADSETEFFECT)GetProcAddress (SDKInstance.m_ChromaSDKModule, "CreateHeadsetEffect");
              SDKInstance.CreateMousepadEffect = (CREATEMOUSEPADEFFECT)GetProcAddress (SDKInstance.m_ChromaSDKModule, "CreateMousepadEffect");
              SDKInstance.CreateKeypadEffect = (CREATEKEYPADEFFECT)GetProcAddress (SDKInstance.m_ChromaSDKModule, "CreateKeypadEffect");
              SDKInstance.SetEffect = (SETEFFECT)GetProcAddress (SDKInstance.m_ChromaSDKModule, "SetEffect");
              SDKInstance.DeleteEffect = (DELETEEFFECT)GetProcAddress (SDKInstance.m_ChromaSDKModule, "DeleteEffect");
              SDKInstance.QueryDevice = (QUERYDEVICE)GetProcAddress (SDKInstance.m_ChromaSDKModule, "QueryDevice");

              if (SDKInstance.CreateEffect &&
              SDKInstance.CreateKeyboardEffect &&
              SDKInstance.CreateMouseEffect &&
              SDKInstance.CreateHeadsetEffect &&
              SDKInstance.CreateMousepadEffect &&
              SDKInstance.CreateKeypadEffect &&
              SDKInstance.SetEffect &&
              SDKInstance.DeleteEffect &&
              SDKInstance.QueryDevice)
              {
                info.GetReturnValue().Set(true);
                return;
              }
          }
        }
    }

    info.GetReturnValue().Set(false);
}

NAN_METHOD(Terminate) {
    if (SDKInstance.m_ChromaSDKModule != NULL)
    {
        RZRESULT Result = RZRESULT_INVALID;
        UNINIT UnInit = (UNINIT)GetProcAddress (SDKInstance.m_ChromaSDKModule, "UnInit");
        if (UnInit)
        {
            Result = UnInit();
        }

        bool success = FreeLibrary (SDKInstance.m_ChromaSDKModule);
        SDKInstance.m_ChromaSDKModule = NULL;

        info.GetReturnValue().Set(success);
        return;
    }

    info.GetReturnValue().Set(false);
}

NAN_MODULE_INIT(InitAll) {
  SDKInstance = SDK();

  Nan::Set(target, Nan::New("initialize").ToLocalChecked(),
    Nan::GetFunction(Nan::New<FunctionTemplate>(Initialize)).ToLocalChecked());
  Nan::Set(target, Nan::New("terminate").ToLocalChecked(),
    Nan::GetFunction(Nan::New<FunctionTemplate>(Terminate)).ToLocalChecked());

  NodeKeyboard::Init(target, &SDKInstance);
}

NODE_MODULE(Chroma, InitAll)
