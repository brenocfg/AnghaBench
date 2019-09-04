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
struct TYPE_3__ {scalar_t__ lLbound; scalar_t__ cElements; } ;
typedef  TYPE_1__ SAFEARRAYBOUND ;
typedef  int /*<<< orphan*/  SAFEARRAY ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/ * SafeArrayCreate (int /*<<< orphan*/ ,int,TYPE_1__*) ; 
 scalar_t__ SafeArrayDestroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  VT_INT_PTR ; 
 int /*<<< orphan*/  has_int_ptr ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 
 int /*<<< orphan*/  trace (char*) ; 

__attribute__((used)) static void check_for_VT_INT_PTR(void)
{
    /* Set a global flag if VT_INT_PTR is supported */

    SAFEARRAY* a;
    SAFEARRAYBOUND bound;
    bound.cElements	= 0;
    bound.lLbound	= 0;
    a = SafeArrayCreate(VT_INT_PTR, 1, &bound);
    if (a) {
        HRESULT hres;
        trace("VT_INT_PTR is supported\n");
        has_int_ptr = TRUE;
        hres = SafeArrayDestroy(a);
        ok(hres == S_OK, "got 0x%08x\n", hres);
    }
    else {
        trace("VT_INT_PTR is not supported\n");
        has_int_ptr = FALSE;
    }        
}