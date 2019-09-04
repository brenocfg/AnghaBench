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
struct TYPE_3__ {size_t cNamedArgs; scalar_t__* rgdispidNamedArgs; scalar_t__ rgvarg; } ;
typedef  int /*<<< orphan*/  IDispatch ;
typedef  size_t DWORD ;
typedef  TYPE_1__ DISPPARAMS ;

/* Variables and functions */
 scalar_t__ DISPID_THIS ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 scalar_t__ VT_DISPATCH ; 
 int /*<<< orphan*/ * V_DISPATCH (scalar_t__) ; 
 scalar_t__ V_VT (scalar_t__) ; 
 int /*<<< orphan*/  WARN (char*) ; 

__attribute__((used)) static IDispatch *get_this(DISPPARAMS *dp)
{
    DWORD i;

    for(i=0; i < dp->cNamedArgs; i++) {
        if(dp->rgdispidNamedArgs[i] == DISPID_THIS) {
            if(V_VT(dp->rgvarg+i) == VT_DISPATCH)
                return V_DISPATCH(dp->rgvarg+i);

            WARN("This is not VT_DISPATCH\n");
            return NULL;
        }
    }

    TRACE("no this passed\n");
    return NULL;
}