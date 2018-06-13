#include <nan.h>
#include <unicode/translit.h>
#include <string>

class NodeTransliterator : public Nan::ObjectWrap {

public:

  static
  NAN_MODULE_INIT(Init) {
    v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(New);
    tpl->SetClassName(Nan::New("Transliterator").ToLocalChecked());
    tpl->InstanceTemplate()->SetInternalFieldCount(1);

    Nan::SetPrototypeMethod(tpl, "transliterate", Transliterate);

    constructor().Reset(Nan::GetFunction(tpl).ToLocalChecked());
    Nan::Set(target, Nan::New("Transliterator").ToLocalChecked(), Nan::GetFunction(tpl).ToLocalChecked());
  }

  NodeTransliterator(icu::UnicodeString rules, UTransDirection dir) {
    UParseError pError;
    UErrorCode status = U_ZERO_ERROR;

    t = icu::Transliterator::createFromRules("RBT", rules, dir, pError, status);

    if (U_FAILURE(status)) {
        Nan::ThrowError(u_errorName(status));
    }

  }

  ~NodeTransliterator() {
    delete t;
  }

private:
  static
  NAN_METHOD(New) {
    if (info.IsConstructCall()) {
      v8::String::Value rules(v8::Isolate::GetCurrent(), info[0]);
      UTransDirection dir = Nan::To<bool>(info[1]).FromJust() ? UTRANS_FORWARD : UTRANS_REVERSE;
      NodeTransliterator *obj = new NodeTransliterator(*rules, dir);
      obj->Wrap(info.This());
      info.GetReturnValue().Set(info.This());
    } else {
      const int argc = 1;
      v8::Local<v8::Value> argv[argc] = {info[0]};
      v8::Local<v8::Function> cons = Nan::New(constructor());
      info.GetReturnValue().Set(Nan::NewInstance(cons, argc, argv).ToLocalChecked());
    }
  }

  static
  NAN_METHOD(Transliterate) {
    NodeTransliterator *obj = Nan::ObjectWrap::Unwrap<NodeTransliterator>(info.This());
    v8::String::Value v8_str(v8::Isolate::GetCurrent(), info[0]);
    icu::UnicodeString u_str(*v8_str);
    obj->t->transliterate(u_str);
    info.GetReturnValue().Set(Nan::New<v8::String>((const uint16_t *)u_str.getTerminatedBuffer()).ToLocalChecked());
  }

  static inline Nan::Persistent<v8::Function>& constructor() {
    static Nan::Persistent<v8::Function> my_constructor;
    return my_constructor;
  }

  icu::Transliterator *t;
};

NAN_MODULE_INIT(Init) {
  NodeTransliterator::Init(target);
}

NODE_MODULE(node_icu_transliterator, Init);
