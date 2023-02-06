
#pragma once

typedef char* str;
typedef const char* c_str;

using Function = void* (*)(void*);

#define EXCEPT noexcept(false)
