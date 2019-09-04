#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  script_ctx_t ;
typedef  int /*<<< orphan*/  jsval_t ;
typedef  int /*<<< orphan*/  jsdisp_t ;
struct TYPE_4__ {TYPE_1__* jsregexp; } ;
struct TYPE_3__ {int flags; } ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int REG_GLOB ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 int /*<<< orphan*/  jsval_bool (int) ; 
 TYPE_2__* regexp_from_jsdisp (int /*<<< orphan*/ *) ; 

__attribute__((used)) static HRESULT RegExp_get_global(script_ctx_t *ctx, jsdisp_t *jsthis, jsval_t *r)
{
    TRACE("\n");

    *r = jsval_bool(!!(regexp_from_jsdisp(jsthis)->jsregexp->flags & REG_GLOB));
    return S_OK;
}