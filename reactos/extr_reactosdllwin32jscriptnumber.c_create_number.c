#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  script_ctx_t ;
typedef  int /*<<< orphan*/  jsdisp_t ;
struct TYPE_3__ {double value; int /*<<< orphan*/  dispex; } ;
typedef  TYPE_1__ NumberInstance ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  alloc_number (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__**) ; 

HRESULT create_number(script_ctx_t *ctx, double value, jsdisp_t **ret)
{
    NumberInstance *number;
    HRESULT hres;

    hres = alloc_number(ctx, NULL, &number);
    if(FAILED(hres))
        return hres;

    number->value = value;

    *ret = &number->dispex;
    return S_OK;
}