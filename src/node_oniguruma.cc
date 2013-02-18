#define BUILDING_NODE_EXTENSION
#include <string>
#include <cstring>
#include <sstream>
#include "node_oniguruma.h"
#include "macros.h"
#include <iostream>

using namespace v8;
using namespace node;
using namespace node_onig;

void NodeOniguruma::Init(Handle<Object> target) {
    HandleScope scope;
    Handle < FunctionTemplate > t = FunctionTemplate::New(New);
    t->SetClassName(String::NewSymbol("Oniguruma"));
    t->InstanceTemplate()->SetInternalFieldCount(1);

    NODE_SET_PROTOTYPE_METHOD(t, "exec", Search);
    //NODE_SET_PROTOTYPE_METHOD(t, "test", )

    Persistent < Function > constructor = Persistent < Function > ::New(t->GetFunction());
    target->Set(String::NewSymbol("Onig"), constructor);
}

NodeOniguruma::NodeOniguruma(const char* pattern_, OnigOptionType option_, OnigSyntaxType* syntax_, bool global_) :
        pattern((OnigUChar*) pattern_), option(option_), enc(ONIG_ENCODING_UTF8), syntax(syntax_), global(global_), lastIndex(
                0) {
    OnigErrorInfo err_info;
    int ret = onig_new(&regex, pattern, pattern + strlen((char*) pattern), option, enc, syntax, &err_info);
    if (ret != ONIG_NORMAL) {
        OnigUChar s[ONIG_MAX_ERROR_MESSAGE_LEN];
        onig_error_code_to_str(s, ret, &err_info);
        std::ostringstream oss;
        oss << "ERROR:" << s;
        throw oss.str().c_str();
    }

}

NodeOniguruma::~NodeOniguruma() {
    onig_free(regex);
}

Handle<Value> NodeOniguruma::New(const Arguments& args) {
    HandleScope scope;

    if (!args.IsConstructCall())
        return args.Callee()->NewInstance();
    try {
        uint32_t args_len = args.Length();
        if (args_len < 1) {
            throw "Too few arguments.";
        }
        REQ_STR_ARG(0);
        std::string pattern_str = *String::Utf8Value(args[0]->ToString());
        OnigSyntaxType* syn = ONIG_SYNTAX_DEFAULT;
        OnigOptionType opts = ONIG_OPTION_NONE;
        bool global_ = false;
        if (args_len > 1) {
            //Option parsing
            REQ_STR_ARG(1);
            std::string options = *String::Utf8Value(args[1]->ToString());
            // ignore case
            if (options.find('i') != std::string::npos) {
                opts |= ONIG_OPTION_IGNORECASE;
            }
            // global match option
            if (options.find('g') != std::string::npos) {
                global_ = true;
            }
            // multiline option
            if (options.find('m') != std::string::npos) {
                opts |= ONIG_OPTION_MULTILINE;
            }
            // Extended option
            if (options.find('x') != std::string::npos ){
                opts |= ONIG_OPTION_EXTEND;
            }
            // No encoding option
            if (options.find('n') != std::string::npos ){
                opts |= ONIG_OPTION_EXTEND;
            }
        }
        NodeOniguruma *onig = new NodeOniguruma(pattern_str.c_str(), opts, syn, global_);
        (onig)->Wrap(args.This());
        args.This()->Set(String::New("source"), String::New(pattern_str.c_str()), ReadOnly);
        args.This()->Set(String::New("global"), Boolean::New(onig->global), ReadOnly);
        args.This()->Set(String::New("ignoreCase"), Boolean::New(opts & ONIG_OPTION_IGNORECASE ? true : false),
                ReadOnly);
        args.This()->Set(String::New("multiline"), Boolean::New(opts & ONIG_OPTION_MULTILINE ? true : false), ReadOnly);
        args.This()->Set(String::New("lastIndex"), Integer::New(0), ReadOnly);
    } catch (const char *msg) {
        return ThrowException(Exception::Error(String::New(msg)));
    }
    return args.This();
}

int NodeOniguruma::Search(const char* target, unsigned int start_pos, OnigRegion* region) {
    OnigUChar* str = (OnigUChar*) target;
    unsigned char *start, *range, *end;
    start = str + start_pos;
    end = str + std::strlen(target);
    range = end;

    int ret = onig_search(regex, str, end, start, range, region, ONIG_OPTION_NONE);

    return ret;

}

Handle<Value> NodeOniguruma::Search(const Arguments& args) {
    HandleScope scope;
    REQ_STR_ARG(0);
    std::string target = *String::Utf8Value(args[0]->ToString());

    NodeOniguruma* onig = Unwrap < NodeOniguruma > (args.This());

    unsigned int match_pos = 0;
    if (onig->global) {
        match_pos = onig->lastIndex;
    }

    OnigRegion* region = onig_region_new();

    int ret = onig->Search(target.c_str(), match_pos, region);
    if (ret < 0) {
        return scope.Close(Null());
    } else {

        int* beg = region->beg;
        int* end = region->end;
        int match_size = region->num_regs;
        Local < Array > match_res(Array::New(match_size));
        for (int i = 0; i < match_size; i++) {
            std::string m_str = target.substr(*(beg + i), *(end + i) - *(beg + i));
            onig->lastIndex = *(end + i) + 1;
            match_res->Set(Integer::New(i), String::New(m_str.c_str()));
        }
        match_res->Set(String::New("index"), Integer::New(*beg), ReadOnly);
        match_res->Set(String::New("input"), String::New(target.c_str()), ReadOnly);

        return scope.Close(match_res);
    }
}
