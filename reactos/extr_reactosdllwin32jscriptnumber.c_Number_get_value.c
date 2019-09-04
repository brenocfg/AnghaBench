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
typedef  int /*<<< orphan*/  script_ctx_t ;
typedef  int /*<<< orphan*/  jsval_t ;
typedef  int /*<<< orphan*/  jsdisp_t ;
struct TYPE_4__ {int /*<<< orphan*/  value; } ;
typedef  TYPE_1__ NumberInstance ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_1__*) ; 
 int /*<<< orphan*/  jsval_number (int /*<<< orphan*/ ) ; 
 TYPE_1__* number_from_jsdisp (int /*<<< orphan*/ *) ; 

__attribute__((used)) static HRESULT Number_get_value(script_ctx_t *ctx, jsdisp_t *jsthis, jsval_t *r)
{
    NumberInstance *number = number_from_jsdisp(jsthis);

    TRACE("(%p)\n", number);

    *r = jsval_number(number->value);
    return S_OK;
}