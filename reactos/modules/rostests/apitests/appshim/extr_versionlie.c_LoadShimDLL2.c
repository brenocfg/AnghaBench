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
typedef  int /*<<< orphan*/ * tGETHOOKAPIS ;
typedef  int /*<<< orphan*/  PCWSTR ;
typedef  int /*<<< orphan*/  HMODULE ;

/* Variables and functions */
 scalar_t__ LoadShimDLL (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  skip (char*) ; 

tGETHOOKAPIS LoadShimDLL2(PCWSTR ShimDll)
{
    HMODULE module;
    tGETHOOKAPIS pGetHookAPIs;

    if (LoadShimDLL(ShimDll, &module, &pGetHookAPIs))
    {
        if (!pGetHookAPIs)
            skip("No GetHookAPIs found\n");
        return pGetHookAPIs;
    }
    return NULL;
}