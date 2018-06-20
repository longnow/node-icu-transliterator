#include "node-icu-transliterator.h"

// RBT

Napi::FunctionReference RBT::constructor;

Napi::Object RBT::Init(Napi::Env env, Napi::Object exports) {
  Napi::HandleScope scope(env);

  Napi::Function ctor = DefineClass(env, "RBT", {
    StaticMethod("register", &RBT::Register),
    InstanceMethod("transliterate", &RBT::Transliterate),
  });

  constructor = Napi::Persistent(ctor);
  constructor.SuppressDestruct();
  exports.Set("RBT", ctor);
  return exports;
}

RBT::RBT(const Napi::CallbackInfo& info) : Napi::ObjectWrap<RBT>(info) {
  int32_t type = info[0].As<Napi::Number>().Int32Value();
  UnicodeString str(info[1].As<Napi::String>().Utf16Value().data());
  UTransDirection dir = info[2].As<Napi::Boolean>().Value() ? UTRANS_FORWARD : UTRANS_REVERSE;

  UParseError pError;
  UErrorCode status = U_ZERO_ERROR;

  if (type == 1) t_ = Transliterator::createInstance(str, dir, pError, status);
  else t_ = Transliterator::createFromRules("RBT", str, dir, pError, status);

  if (U_FAILURE(status)) {
    Napi::Error::New(info.Env(), u_errorName(status)).ThrowAsJavaScriptException();
  }
}

RBT::~RBT() {
  if (t_) delete t_;
}

void RBT::Register(const Napi::CallbackInfo& info) {
  UnicodeString id(info[0].As<Napi::String>().Utf16Value().data());
  UnicodeString rules(info[1].As<Napi::String>().Utf16Value().data());

  UParseError pError;
  UErrorCode status = U_ZERO_ERROR;
  Transliterator* t = Transliterator::createFromRules(id, rules, UTRANS_FORWARD, pError, status);

  if (U_FAILURE(status)) {
    Napi::Error::New(info.Env(), u_errorName(status)).ThrowAsJavaScriptException();
  }

  Transliterator::registerInstance(t);
}

Napi::Value RBT::Transliterate(const Napi::CallbackInfo& info) {
  UnicodeString str(info[0].As<Napi::String>().Utf16Value().data());
  t_->transliterate(str);
  return Napi::String::New(info.Env(), str.getTerminatedBuffer());
};

// RBNF

Napi::FunctionReference RBNF::constructor;

Napi::Object RBNF::Init(Napi::Env env, Napi::Object exports) {
  Napi::HandleScope scope(env);

  Napi::Function ctor = DefineClass(env, "RBNF", {
    InstanceMethod("format", &RBNF::Format),
  });

  constructor = Napi::Persistent(ctor);
  constructor.SuppressDestruct();
  exports.Set("RBNF", ctor);
  return exports;
}

RBNF::RBNF(const Napi::CallbackInfo& info) : Napi::ObjectWrap<RBNF>(info) {
  UnicodeString rules(info[0].As<Napi::String>().Utf16Value().data());

  UParseError pError;
  UErrorCode status = U_ZERO_ERROR;

  f_ = new RuleBasedNumberFormat(rules, pError, status);

  if (U_FAILURE(status)) {
    Napi::Error::New(info.Env(), u_errorName(status)).ThrowAsJavaScriptException();
  }
}

RBNF::~RBNF() {
  if (f_) delete f_;
}

Napi::Value RBNF::Format(const Napi::CallbackInfo& info) {
  UnicodeString str;
  FieldPosition pos(FieldPosition::DONT_CARE);
  f_->format(info[0].As<Napi::Number>().DoubleValue(), str, pos);
  return Napi::String::New(info.Env(), str.getTerminatedBuffer());
}

// init

Napi::Object Init(Napi::Env env, Napi::Object exports) {
  RBT::Init(env, exports);
  RBNF::Init(env, exports);
  return exports;
}

NODE_API_MODULE(node_icu_transliterator, Init);
