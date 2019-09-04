#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  disp; } ;
struct TYPE_8__ {TYPE_1__ u; } ;
typedef  TYPE_2__ vdisp_t ;
typedef  int /*<<< orphan*/  script_ctx_t ;
typedef  int /*<<< orphan*/  jsstr_t ;
struct TYPE_9__ {int /*<<< orphan*/  str; } ;
typedef  TYPE_3__ StringInstance ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/ * jsstr_addref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jsval_disp (int /*<<< orphan*/ ) ; 
 TYPE_3__* string_this (TYPE_2__*) ; 
 int /*<<< orphan*/  to_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 

__attribute__((used)) static HRESULT get_string_val(script_ctx_t *ctx, vdisp_t *jsthis, jsstr_t **val)
{
    StringInstance *string;

    if((string = string_this(jsthis))) {
        *val = jsstr_addref(string->str);
        return S_OK;
    }

    return to_string(ctx, jsval_disp(jsthis->u.disp), val);
}