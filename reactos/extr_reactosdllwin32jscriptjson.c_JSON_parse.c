#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vdisp_t ;
typedef  int /*<<< orphan*/  script_ctx_t ;
typedef  int /*<<< orphan*/  jsval_t ;
typedef  int /*<<< orphan*/  jsstr_t ;
struct TYPE_4__ {int /*<<< orphan*/ * ctx; int /*<<< orphan*/  const* end; int /*<<< orphan*/  const* ptr; } ;
typedef  TYPE_1__ json_parse_ctx_t ;
typedef  int /*<<< orphan*/  WORD ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  E_FAIL ; 
 int /*<<< orphan*/  E_INVALIDARG ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FIXME (char*) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugstr_w (int /*<<< orphan*/  const*) ; 
 int jsstr_length (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jsstr_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jsval_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parse_json_value (TYPE_1__*,int /*<<< orphan*/ *) ; 
 scalar_t__ skip_spaces (TYPE_1__*) ; 
 int /*<<< orphan*/  to_flat_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/  const**) ; 

__attribute__((used)) static HRESULT JSON_parse(script_ctx_t *ctx, vdisp_t *jsthis, WORD flags, unsigned argc, jsval_t *argv, jsval_t *r)
{
    json_parse_ctx_t parse_ctx;
    const WCHAR *buf;
    jsstr_t *str;
    jsval_t ret;
    HRESULT hres;

    if(argc != 1) {
        FIXME("Unsupported args\n");
        return E_INVALIDARG;
    }

    hres = to_flat_string(ctx, argv[0], &str, &buf);
    if(FAILED(hres))
        return hres;

    TRACE("%s\n", debugstr_w(buf));

    parse_ctx.ptr = buf;
    parse_ctx.end = buf + jsstr_length(str);
    parse_ctx.ctx = ctx;
    hres = parse_json_value(&parse_ctx, &ret);
    jsstr_release(str);
    if(FAILED(hres))
        return hres;

    if(skip_spaces(&parse_ctx)) {
        FIXME("syntax error\n");
        jsval_release(ret);
        return E_FAIL;
    }

    if(r)
        *r = ret;
    else
        jsval_release(ret);
    return S_OK;
}