#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  native_suffixW ;
typedef  int /*<<< orphan*/  native_prefixW ;
typedef  int /*<<< orphan*/  jsstr_t ;
typedef  char WCHAR ;
struct TYPE_5__ {char const* name; TYPE_1__* func_code; scalar_t__ value_proc; } ;
struct TYPE_4__ {int /*<<< orphan*/  source_len; int /*<<< orphan*/  source; } ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  TYPE_2__ FunctionInstance ;
typedef  int DWORD ;

/* Variables and functions */
 scalar_t__ ARRAY_SIZE (char const*) ; 
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/ * jsstr_alloc_buf (scalar_t__,char**) ; 
 int /*<<< orphan*/ * jsstr_alloc_len (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 int strlenW (char const*) ; 

__attribute__((used)) static HRESULT function_to_string(FunctionInstance *function, jsstr_t **ret)
{
    jsstr_t *str;

    static const WCHAR native_prefixW[] = {'\n','f','u','n','c','t','i','o','n',' '};
    static const WCHAR native_suffixW[] =
        {'(',')',' ','{','\n',' ',' ',' ',' ','[','n','a','t','i','v','e',' ','c','o','d','e',']','\n','}','\n'};

    if(function->value_proc) {
        DWORD name_len;
        WCHAR *ptr;

        name_len = strlenW(function->name);
        str = jsstr_alloc_buf(ARRAY_SIZE(native_prefixW) + ARRAY_SIZE(native_suffixW) + name_len, &ptr);
        if(!str)
            return E_OUTOFMEMORY;

        memcpy(ptr, native_prefixW, sizeof(native_prefixW));
        memcpy(ptr += ARRAY_SIZE(native_prefixW), function->name, name_len*sizeof(WCHAR));
        memcpy(ptr + name_len, native_suffixW, sizeof(native_suffixW));
    }else {
        str = jsstr_alloc_len(function->func_code->source, function->func_code->source_len);
        if(!str)
            return E_OUTOFMEMORY;
    }

    *ret = str;
    return S_OK;
}