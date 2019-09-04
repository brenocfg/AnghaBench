#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  jsdisp; } ;
struct TYPE_6__ {TYPE_1__ u; } ;
typedef  TYPE_2__ vdisp_t ;
typedef  int /*<<< orphan*/  script_ctx_t ;
typedef  int /*<<< orphan*/  jsval_t ;
typedef  int /*<<< orphan*/  WORD ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  DISPATCH_METHOD ; 
 int /*<<< orphan*/  E_FAIL ; 
 int /*<<< orphan*/  FIXME (char*) ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 int /*<<< orphan*/  is_jsdisp (TYPE_2__*) ; 
 int /*<<< orphan*/  jsdisp_call_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  toStringW ; 

__attribute__((used)) static HRESULT Object_toLocaleString(script_ctx_t *ctx, vdisp_t *jsthis, WORD flags, unsigned argc, jsval_t *argv,
        jsval_t *r)
{
    TRACE("\n");

    if(!is_jsdisp(jsthis)) {
        FIXME("Host object this\n");
        return E_FAIL;
    }

    return jsdisp_call_name(jsthis->u.jsdisp, toStringW, DISPATCH_METHOD, 0, NULL, r);
}