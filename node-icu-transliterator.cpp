#include <nan.h>
#include <unicode/translit.h>
#include <unicode/rbnf.h>

using icu::FieldPosition;
using icu::RuleBasedNumberFormat;
using icu::Transliterator;
using icu::UnicodeString;

class RBT : public Nan::ObjectWrap {

public:

  static NAN_MODULE_INIT(Init) {
    v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(New);
    tpl->SetClassName(Nan::New("RBT").ToLocalChecked());
    tpl->InstanceTemplate()->SetInternalFieldCount(1);

    Nan::SetMethod(tpl, "register", Register);
    Nan::SetPrototypeMethod(tpl, "transliterate", Transliterate);

    constructor().Reset(Nan::GetFunction(tpl).ToLocalChecked());
    Nan::Set(target, Nan::New("RBT").ToLocalChecked(), Nan::GetFunction(tpl).ToLocalChecked());
  }

  RBT() : t_(NULL) {}

  ~RBT() {
    if (t_) delete t_;
  }

private:
  static NAN_METHOD(New) {
    if (info.IsConstructCall()) {
      int32_t type = Nan::To<int32_t>(info[0]).FromJust();
      v8::String::Value str(v8::Isolate::GetCurrent(), info[1]);
      UTransDirection dir = Nan::To<bool>(info[2]).FromJust() ? UTRANS_FORWARD : UTRANS_REVERSE;

      UParseError pError;
      UErrorCode status = U_ZERO_ERROR;
      RBT *obj = new RBT();

      if (type == 1) obj->t_ = Transliterator::createInstance(*str, dir, pError, status);
      else obj->t_ = Transliterator::createFromRules("RBT", *str, dir, pError, status);

      if (U_FAILURE(status)) {
          Nan::ThrowError(u_errorName(status));
      }

      obj->Wrap(info.This());
      info.GetReturnValue().Set(info.This());
    } else {
      const int argc = 1;
      v8::Local<v8::Value> argv[argc] = {info[0]};
      v8::Local<v8::Function> cons = Nan::New(constructor());
      info.GetReturnValue().Set(Nan::NewInstance(cons, argc, argv).ToLocalChecked());
    }
  }

  static NAN_METHOD(Register) {
    v8::String::Value id(v8::Isolate::GetCurrent(), info[0]);
    v8::String::Value rules(v8::Isolate::GetCurrent(), info[1]);

    UParseError pError;
    UErrorCode status = U_ZERO_ERROR;
    Transliterator *t = Transliterator::createFromRules(*id, *rules, UTRANS_FORWARD, pError, status);

    if (U_FAILURE(status)) {
        Nan::ThrowError(u_errorName(status));
    }

    Transliterator::registerInstance(t);
  }

  static NAN_METHOD(Transliterate) {
    RBT *obj = Nan::ObjectWrap::Unwrap<RBT>(info.This());
    v8::String::Value v8_str(v8::Isolate::GetCurrent(), info[0]);
    UnicodeString u_str(*v8_str);
    obj->t_->transliterate(u_str);
    info.GetReturnValue().Set(Nan::New<v8::String>((const uint16_t *)u_str.getTerminatedBuffer()).ToLocalChecked());
  }

  static inline Nan::Persistent<v8::Function>& constructor() {
    static Nan::Persistent<v8::Function> my_constructor;
    return my_constructor;
  }

  Transliterator *t_;
};

class RBNF : public Nan::ObjectWrap {

public:

  static NAN_MODULE_INIT(Init) {
    v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(New);
    tpl->SetClassName(Nan::New("RBNF").ToLocalChecked());
    tpl->InstanceTemplate()->SetInternalFieldCount(1);

    Nan::SetPrototypeMethod(tpl, "format", Format);

    constructor().Reset(Nan::GetFunction(tpl).ToLocalChecked());
    Nan::Set(target, Nan::New("RBNF").ToLocalChecked(), Nan::GetFunction(tpl).ToLocalChecked());
  }

  RBNF(UnicodeString rules) {
    UParseError pError;
    UErrorCode status = U_ZERO_ERROR;

    f_ = new RuleBasedNumberFormat(rules, pError, status);

    if (U_FAILURE(status)) {
        Nan::ThrowError(u_errorName(status));
    }

  }

  ~RBNF() {
    delete f_;
  }

private:
  static NAN_METHOD(New) {
    if (info.IsConstructCall()) {
      v8::String::Value rules(v8::Isolate::GetCurrent(), info[0]);
      RBNF *obj = new RBNF(*rules);
      obj->Wrap(info.This());
      info.GetReturnValue().Set(info.This());
    } else {
      const int argc = 1;
      v8::Local<v8::Value> argv[argc] = {info[0]};
      v8::Local<v8::Function> cons = Nan::New(constructor());
      info.GetReturnValue().Set(Nan::NewInstance(cons, argc, argv).ToLocalChecked());
    }
  }

  static NAN_METHOD(Format) {
    UnicodeString str;
    FieldPosition pos(FieldPosition::DONT_CARE);
    RBNF *obj = Nan::ObjectWrap::Unwrap<RBNF>(info.This());
    obj->f_->format(Nan::To<double>(info[0]).FromJust(), str, pos);
    info.GetReturnValue().Set(Nan::New<v8::String>((const uint16_t *)str.getTerminatedBuffer()).ToLocalChecked());
  }

  static inline Nan::Persistent<v8::Function>& constructor() {
    static Nan::Persistent<v8::Function> my_constructor;
    return my_constructor;
  }

  RuleBasedNumberFormat *f_;
};

NAN_MODULE_INIT(Init) {
  RBT::Init(target);
  RBNF::Init(target);
}

NODE_MODULE(node_icu_transliterator, Init);
