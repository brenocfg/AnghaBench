#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  IDispatch_iface; } ;
typedef  int /*<<< orphan*/  MSIHANDLE ;
typedef  int /*<<< orphan*/  IDispatch ;
typedef  scalar_t__ HRESULT ;
typedef  TYPE_1__ AutomationObject ;

/* Variables and functions */
 int /*<<< orphan*/  Database_tid ; 
 scalar_t__ E_OUTOFMEMORY ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ init_automation_object (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* msi_alloc (int) ; 
 int /*<<< orphan*/  msi_free (TYPE_1__*) ; 

__attribute__((used)) static HRESULT create_database(MSIHANDLE msiHandle, IDispatch **dispatch)
{
    AutomationObject *database;
    HRESULT hr;

    TRACE("(%d %p)\n", msiHandle, dispatch);

    database = msi_alloc(sizeof(AutomationObject));
    if (!database) return E_OUTOFMEMORY;

    hr = init_automation_object(database, msiHandle, Database_tid);
    if (hr != S_OK)
    {
        msi_free(database);
        return hr;
    }

    *dispatch = &database->IDispatch_iface;

    return hr;
}