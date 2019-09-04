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
struct TYPE_3__ {int /*<<< orphan*/  IObjContext_iface; int /*<<< orphan*/  IContextCallback_iface; int /*<<< orphan*/  IComThreadingInfo_iface; } ;
typedef  int /*<<< orphan*/  REFIID ;
typedef  int /*<<< orphan*/ * LPVOID ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  TYPE_1__ Context ;

/* Variables and functions */
 int /*<<< orphan*/  E_NOINTERFACE ; 
 int /*<<< orphan*/  FIXME (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IID_IComThreadingInfo ; 
 int /*<<< orphan*/  IID_IContextCallback ; 
 int /*<<< orphan*/  IID_IObjContext ; 
 int /*<<< orphan*/  IID_IUnknown ; 
 int /*<<< orphan*/  IUnknown_AddRef (int /*<<< orphan*/ *) ; 
 scalar_t__ IsEqualIID (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  debugstr_guid (int /*<<< orphan*/ ) ; 

__attribute__((used)) static HRESULT Context_QueryInterface(Context *iface, REFIID riid, LPVOID *ppv)
{
    *ppv = NULL;

    if (IsEqualIID(riid, &IID_IComThreadingInfo) ||
        IsEqualIID(riid, &IID_IUnknown))
    {
        *ppv = &iface->IComThreadingInfo_iface;
    }
    else if (IsEqualIID(riid, &IID_IContextCallback))
    {
        *ppv = &iface->IContextCallback_iface;
    }
    else if (IsEqualIID(riid, &IID_IObjContext))
    {
        *ppv = &iface->IObjContext_iface;
    }

    if (*ppv)
    {
        IUnknown_AddRef((IUnknown*)*ppv);
        return S_OK;
    }

    FIXME("interface not implemented %s\n", debugstr_guid(riid));
    return E_NOINTERFACE;
}