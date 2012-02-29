#define BUILDING_NODE_EXTENSION
#include "node_oniguruma.h"

using namespace node_onig;

namespace {
void Initialize(v8::Handle<v8::Object> target) {
    v8::HandleScope scope;
    NodeOniguruma::Init(target);
}
}

NODE_MODULE(oniguruma,Initialize);
