#ifndef NODE_ICU_TRANSLITERATOR_H
#define NODE_ICU_TRANSLITERATOR_H

#include <napi.h>
#include <unicode/translit.h>
#include <unicode/rbnf.h>

using icu::FieldPosition;
using icu::RuleBasedNumberFormat;
using icu::Transliterator;
using icu::UnicodeString;

class RBT : public Napi::ObjectWrap<RBT> {
public:
  static Napi::Object Init(Napi::Env env, Napi::Object exports);

  RBT(const Napi::CallbackInfo& info);
  ~RBT();

private:
  static void Register(const Napi::CallbackInfo& info);
  Napi::Value Transliterate(const Napi::CallbackInfo& info);

  static Napi::FunctionReference constructor;
  Transliterator* t_;
};

class RBNF : public Napi::ObjectWrap<RBNF> {
public:
  static Napi::Object Init(Napi::Env env, Napi::Object exports);

  RBNF(const Napi::CallbackInfo& info);
  ~RBNF();

private:
  Napi::Value Format(const Napi::CallbackInfo& info);

  static Napi::FunctionReference constructor;
  RuleBasedNumberFormat* f_;
};

#endif
