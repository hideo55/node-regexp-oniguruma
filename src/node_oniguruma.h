#ifndef NODE_ONIGURUMA_H_
#define NODE_ONIGURUMA_H_
#define BUILDING_NODE_EXTENSION

#include <oniguruma.h>
#include <node.h>
#include <map>

using namespace v8;
using namespace node;

namespace node_onig {

class NodeOniguruma: public ObjectWrap {
public:
    NodeOniguruma(const char* pattern, OnigOptionType option_, OnigSyntaxType* syntax_, bool global_);

    ~NodeOniguruma();

    static void Init(Handle<Object> target);

    static Handle<Value> New(const Arguments& args);

    static Handle<Value> Search(const Arguments& args);
    static Handle<Value> Match(const Arguments& args);

    static Handle<Value> getSource(const Arguments& args);
    static Handle<Value> getLastIndex(const Arguments& args);
    static Handle<Value> isGlobal(const Arguments& args);
    static Handle<Value> doesIgnoreCase(const Arguments& args);
    static Handle<Value> isMultiline(const Arguments& args);

private:
    regex_t* regex;
    const OnigUChar* pattern;
    OnigOptionType option;
    OnigEncoding enc;
    OnigSyntaxType* syntax;


    bool global;
    int lastIndex;

    int Search(const char* target, unsigned int start_pos, OnigRegion* region);
    int Match(const char* target, OnigRegion* region);
};

}

#endif /* NODE_ONIGURUMA_H_ */
