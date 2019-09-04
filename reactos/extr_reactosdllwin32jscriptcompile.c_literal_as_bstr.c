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
struct TYPE_4__ {int /*<<< orphan*/  dval; int /*<<< orphan*/  wstr; } ;
struct TYPE_5__ {int type; TYPE_1__ u; } ;
typedef  TYPE_2__ literal_t ;
typedef  int /*<<< orphan*/  jsstr_t ;
typedef  int /*<<< orphan*/  compiler_ctx_t ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  scalar_t__ BSTR ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT_UNREACHABLE ; 
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  FAILED (int /*<<< orphan*/ ) ; 
#define  LT_DOUBLE 129 
#define  LT_STRING 128 
 int /*<<< orphan*/  S_OK ; 
 scalar_t__ compiler_alloc_bstr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ compiler_alloc_bstr_len (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  double_to_string (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  jsstr_flush (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  jsstr_length (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jsstr_release (int /*<<< orphan*/ *) ; 

__attribute__((used)) static HRESULT literal_as_bstr(compiler_ctx_t *ctx, literal_t *literal, BSTR *str)
{
    switch(literal->type) {
    case LT_STRING:
        *str = compiler_alloc_bstr(ctx, literal->u.wstr);
        break;
    case LT_DOUBLE: {
        jsstr_t *jsstr;
        HRESULT hres;

        hres = double_to_string(literal->u.dval, &jsstr);
        if(FAILED(hres))
            return hres;

        *str = compiler_alloc_bstr_len(ctx, NULL, jsstr_length(jsstr));
        if(*str)
            jsstr_flush(jsstr, *str);
        jsstr_release(jsstr);
        break;
    }
    DEFAULT_UNREACHABLE;
    }

    return *str ? S_OK : E_OUTOFMEMORY;
}