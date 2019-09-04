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
typedef  int /*<<< orphan*/  vdisp_t ;
struct TYPE_4__ {int /*<<< orphan*/  member_0; } ;
struct TYPE_5__ {char* gap; int /*<<< orphan*/  stack; int /*<<< orphan*/  buf; int /*<<< orphan*/  buf_len; int /*<<< orphan*/  stack_top; TYPE_1__ member_7; int /*<<< orphan*/  member_6; int /*<<< orphan*/  member_5; int /*<<< orphan*/ * member_4; int /*<<< orphan*/  member_3; int /*<<< orphan*/  member_2; int /*<<< orphan*/ * member_1; int /*<<< orphan*/ * member_0; } ;
typedef  TYPE_2__ stringify_ctx_t ;
typedef  int /*<<< orphan*/  script_ctx_t ;
typedef  int /*<<< orphan*/  jsval_t ;
typedef  int /*<<< orphan*/  jsstr_t ;
typedef  int /*<<< orphan*/  WORD ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 scalar_t__ E_NOTIMPL ; 
 scalar_t__ E_OUTOFMEMORY ; 
 scalar_t__ FAILED (scalar_t__) ; 
 int /*<<< orphan*/  FIXME (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ SUCCEEDED (scalar_t__) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  debugstr_jsval (int /*<<< orphan*/ ) ; 
 int floor (double) ; 
 double get_number (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * get_string (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  heap_free (int /*<<< orphan*/ ) ; 
 scalar_t__ is_number (int /*<<< orphan*/ ) ; 
 scalar_t__ is_object_instance (int /*<<< orphan*/ ) ; 
 scalar_t__ is_string (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * jsstr_alloc_len (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jsstr_extract (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t,char*) ; 
 size_t jsstr_length (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jsval_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jsval_string (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jsval_undefined () ; 
 scalar_t__ maybe_to_primitive (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ stringify (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static HRESULT JSON_stringify(script_ctx_t *ctx, vdisp_t *jsthis, WORD flags, unsigned argc, jsval_t *argv, jsval_t *r)
{
    stringify_ctx_t stringify_ctx = {ctx, NULL,0,0, NULL,0,0, {0}};
    HRESULT hres;

    TRACE("\n");

    if(!argc) {
        if(r)
            *r = jsval_undefined();
        return S_OK;
    }

    if(argc >= 2 && is_object_instance(argv[1])) {
        FIXME("Replacer %s not yet supported\n", debugstr_jsval(argv[1]));
        return E_NOTIMPL;
    }

    if(argc >= 3) {
        jsval_t space_val;

        hres = maybe_to_primitive(ctx, argv[2], &space_val);
        if(FAILED(hres))
            return hres;

        if(is_number(space_val)) {
            double n = get_number(space_val);
            if(n >= 1) {
                int i, len;
                if(n > 10)
                    n = 10;
                len = floor(n);
                for(i=0; i < len; i++)
                    stringify_ctx.gap[i] = ' ';
                stringify_ctx.gap[len] = 0;
            }
        }else if(is_string(space_val)) {
            jsstr_t *space_str = get_string(space_val);
            size_t len = jsstr_length(space_str);
            if(len > 10)
                len = 10;
            jsstr_extract(space_str, 0, len, stringify_ctx.gap);
        }

        jsval_release(space_val);
    }

    hres = stringify(&stringify_ctx, argv[0]);
    if(SUCCEEDED(hres) && r) {
        assert(!stringify_ctx.stack_top);

        if(hres == S_OK) {
            jsstr_t *ret = jsstr_alloc_len(stringify_ctx.buf, stringify_ctx.buf_len);
            if(ret)
                *r = jsval_string(ret);
            else
                hres = E_OUTOFMEMORY;
        }else {
            *r = jsval_undefined();
        }
    }

    heap_free(stringify_ctx.buf);
    heap_free(stringify_ctx.stack);
    return hres;
}