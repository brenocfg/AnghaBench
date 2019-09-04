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
typedef  int /*<<< orphan*/  LPVOID ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  FIXME (char*) ; 
 int /*<<< orphan*/  FilterGraph_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

HRESULT FilterGraphNoThread_create(IUnknown *pUnkOuter, LPVOID *ppObj)
{
    FIXME("CLSID_FilterGraphNoThread partially implemented - Forwarding to CLSID_FilterGraph\n");
    return FilterGraph_create(pUnkOuter, ppObj);
}