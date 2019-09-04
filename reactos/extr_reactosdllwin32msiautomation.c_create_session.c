#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  IDispatch_iface; } ;
struct TYPE_5__ {TYPE_4__ autoobj; int /*<<< orphan*/ * installer; } ;
typedef  TYPE_1__ SessionObject ;
typedef  int /*<<< orphan*/  MSIHANDLE ;
typedef  int /*<<< orphan*/  IDispatch ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 scalar_t__ E_OUTOFMEMORY ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  Session_tid ; 
 scalar_t__ init_automation_object (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* msi_alloc (int) ; 
 int /*<<< orphan*/  msi_free (TYPE_1__*) ; 

HRESULT create_session(MSIHANDLE msiHandle, IDispatch *installer, IDispatch **disp)
{
    SessionObject *session;
    HRESULT hr;

    session = msi_alloc(sizeof(SessionObject));
    if (!session) return E_OUTOFMEMORY;

    hr = init_automation_object(&session->autoobj, msiHandle, Session_tid);
    if (hr != S_OK)
    {
        msi_free(session);
        return hr;
    }

    session->installer = installer;
    *disp = &session->autoobj.IDispatch_iface;

    return hr;
}