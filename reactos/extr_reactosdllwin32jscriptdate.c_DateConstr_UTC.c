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
typedef  int /*<<< orphan*/  vdisp_t ;
typedef  int /*<<< orphan*/  script_ctx_t ;
typedef  int /*<<< orphan*/  jsval_t ;
typedef  int /*<<< orphan*/  WORD ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 int /*<<< orphan*/  date_utc (int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ *,double*) ; 
 int /*<<< orphan*/  jsval_number (double) ; 

__attribute__((used)) static HRESULT DateConstr_UTC(script_ctx_t *ctx, vdisp_t *jsthis, WORD flags, unsigned argc, jsval_t *argv,
        jsval_t *r)
{
    double n;
    HRESULT hres;

    TRACE("\n");

    hres = date_utc(ctx, argc, argv, &n);
    if(SUCCEEDED(hres) && r)
        *r = jsval_number(n);
    return hres;
}