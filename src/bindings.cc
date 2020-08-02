/*
 * Copyright 2018 Robin Andersson <me@robinwassen.com>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <node.h>
#include <node_buffer.h>

#include "./electronwallpaper.h"

namespace bindings {
  using v8::Boolean;
  using v8::Exception;
  using v8::FunctionCallbackInfo;
  using v8::HandleScope;
  using v8::Isolate;
  using v8::Local;
  using v8::Object;
  using v8::String;
  using v8::Value;
  using v8::Uint8Array;

  using electronwallpaper::AttachWindow;

  Local<String> MaybeLocalStringToLocalString(v8::MaybeLocal<String> str) {
    v8::Local<v8::String> v8String;
    bool b = str.ToLocal(&v8String);
    if (b) {
      return v8String;
    }
    return v8String;
  }

  Local<Object> MaybeLocalObjectToLocalObject(v8::MaybeLocal<Object> obj) {
    v8::Local<v8::Object> v8Obj;
    bool b = obj.ToLocal(&v8Obj);
    if (b) {
      return v8Obj;
    }
    return v8Obj;
  }

  void AttachWindowExport(const FunctionCallbackInfo<Value>& args) {

    Isolate* isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);

    v8::Local<v8::Context> context = v8::Context::New(isolate);

    if (args.Length() < 1) {
      isolate->ThrowException(Exception::TypeError(MaybeLocalStringToLocalString(v8::String::NewFromUtf8(isolate, "Expected one argument"))));
      return;
    }

    if (!args[0]->IsObject()) {
      Local<String> message = MaybeLocalStringToLocalString(String::NewFromUtf8(isolate, "Expected first argument to be a window handle buffer"));
      isolate->ThrowException(Exception::TypeError(message));
      return;
    }

    unsigned char* windowHandleBuffer = (unsigned char*)node::Buffer::Data(MaybeLocalObjectToLocalObject(args[0]->ToObject(context)));
    // unsigned char* windowHandleBuffer = args[0].As<Uint8Array>();

    AttachWindow(windowHandleBuffer);
  }

  void Initialize(Local<Object> exports) {
    NODE_SET_METHOD(exports, "attachWindow", AttachWindowExport);
  }
}  // namespace bindings

NODE_MODULE(module_name, bindings::Initialize)
