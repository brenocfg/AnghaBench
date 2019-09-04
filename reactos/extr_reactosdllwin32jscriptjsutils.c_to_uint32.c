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
typedef  int /*<<< orphan*/  UINT32 ;
typedef  int /*<<< orphan*/  INT32 ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_int32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

HRESULT to_uint32(script_ctx_t *ctx, jsval_t val, UINT32 *ret)
{
    INT32 n;
    HRESULT hres;

    hres = to_int32(ctx, val, &n);
    if(SUCCEEDED(hres))
        *ret = n;
    return hres;
}