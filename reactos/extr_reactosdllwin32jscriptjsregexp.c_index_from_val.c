#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  script_ctx_t ;
typedef  int /*<<< orphan*/  jsval_t ;
typedef  double INT ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_ei (int /*<<< orphan*/ *) ; 
 double floor (double) ; 
 scalar_t__ is_int32 (double) ; 
 int /*<<< orphan*/  to_number (int /*<<< orphan*/ *,int /*<<< orphan*/ ,double*) ; 

__attribute__((used)) static INT index_from_val(script_ctx_t *ctx, jsval_t v)
{
    double n;
    HRESULT hres;

    hres = to_number(ctx, v, &n);
    if(FAILED(hres)) {
        clear_ei(ctx); /* FIXME: Move ignoring exceptions to to_primitive */
        return 0;
    }

    n = floor(n);
    return is_int32(n) ? n : 0;
}