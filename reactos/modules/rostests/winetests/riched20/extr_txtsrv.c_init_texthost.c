#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_7__ {int refCount; TYPE_2__ ITextHost_iface; } ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  int /*<<< orphan*/  ITextServices ;
typedef  TYPE_1__ ITextHostTestImpl ;
typedef  TYPE_2__ ITextHost ;
typedef  scalar_t__ HRESULT ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 TYPE_1__* CoTaskMemAlloc (int) ; 
 int /*<<< orphan*/  CoTaskMemFree (TYPE_1__*) ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ IUnknown_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void**) ; 
 int /*<<< orphan*/  IUnknown_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  itextHostVtbl ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__,...) ; 
 scalar_t__ pCreateTextServices (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  pIID_ITextServices ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static BOOL init_texthost(ITextServices **txtserv, ITextHost **ret)
{
    ITextHostTestImpl *dummyTextHost;
    IUnknown *init;
    HRESULT result;

    dummyTextHost = CoTaskMemAlloc(sizeof(*dummyTextHost));
    if (dummyTextHost == NULL) {
        win_skip("Insufficient memory to create ITextHost interface\n");
        return FALSE;
    }
    dummyTextHost->ITextHost_iface.lpVtbl = &itextHostVtbl;
    dummyTextHost->refCount = 1;

    /* MSDN states that an IUnknown object is returned by
       CreateTextServices which is then queried to obtain a
       ITextServices object. */
    result = pCreateTextServices(NULL, &dummyTextHost->ITextHost_iface, &init);
    ok(result == S_OK, "Did not return S_OK when created (result =  %x)\n", result);
    if (result != S_OK) {
        CoTaskMemFree(dummyTextHost);
        win_skip("CreateTextServices failed.\n");
        return FALSE;
    }

    result = IUnknown_QueryInterface(init, pIID_ITextServices, (void**)txtserv);
    ok((result == S_OK) && (*txtserv != NULL), "Querying interface failed (result = %x, txtserv = %p)\n", result, *txtserv);
    IUnknown_Release(init);
    if (!((result == S_OK) && (*txtserv != NULL))) {
        CoTaskMemFree(dummyTextHost);
        win_skip("Could not retrieve ITextServices interface\n");
        return FALSE;
    }

    *ret = &dummyTextHost->ITextHost_iface;
    return TRUE;
}