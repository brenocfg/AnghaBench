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
typedef  int /*<<< orphan*/  ITfDocumentMgr ;
typedef  int /*<<< orphan*/  ITfContext ;
typedef  int /*<<< orphan*/  ITfCompartmentMgr ;
typedef  int /*<<< orphan*/  ITfCompartment ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  CLSID_FakeService ; 
 int /*<<< orphan*/  GUID_COMPARTMENT_PERSISTMENUENABLED ; 
 int /*<<< orphan*/  GUID_COMPARTMENT_SPEECH_OPENCLOSE ; 
 int /*<<< orphan*/  IID_ITfCompartmentMgr ; 
 int /*<<< orphan*/  ITfCompartmentMgr_ClearCompartment (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ITfCompartmentMgr_GetCompartment (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  ITfCompartmentMgr_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ITfCompartment_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ITfContext_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ITfContext_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ITfDocumentMgr_GetTop (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  ITfDocumentMgr_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ITfDocumentMgr_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ITfThreadMgr_GetFocus (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  ITfThreadMgr_GetGlobalCompartment (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  ITfThreadMgr_QueryInterface (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enum_compartments (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_tm ; 
 int /*<<< orphan*/  ok (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  tid ; 

__attribute__((used)) static void test_Compartments(void)
{
    ITfContext *cxt;
    ITfDocumentMgr *dm;
    ITfCompartmentMgr *cmpmgr;
    ITfCompartment *cmp;
    HRESULT hr;

    ITfThreadMgr_GetFocus(g_tm, &dm);
    ITfDocumentMgr_GetTop(dm,&cxt);

    /* Global */
    hr = ITfThreadMgr_GetGlobalCompartment(g_tm, &cmpmgr);
    ok(SUCCEEDED(hr),"GetGlobalCompartment failed\n");
    hr = ITfCompartmentMgr_GetCompartment(cmpmgr, &GUID_COMPARTMENT_SPEECH_OPENCLOSE, &cmp);
    ok(SUCCEEDED(hr),"GetCompartment failed\n");
    ITfCompartment_Release(cmp);
    enum_compartments(cmpmgr,&GUID_COMPARTMENT_SPEECH_OPENCLOSE,NULL);
    ITfCompartmentMgr_Release(cmpmgr);

    /* Thread */
    hr = ITfThreadMgr_QueryInterface(g_tm, &IID_ITfCompartmentMgr, (LPVOID*)&cmpmgr);
    ok(SUCCEEDED(hr),"ThreadMgr QI for IID_ITfCompartmentMgr failed\n");
    hr = ITfCompartmentMgr_GetCompartment(cmpmgr, &CLSID_FakeService, &cmp);
    ok(SUCCEEDED(hr),"GetCompartment failed\n");
    enum_compartments(cmpmgr,&CLSID_FakeService,&GUID_COMPARTMENT_SPEECH_OPENCLOSE);
    ITfCompartmentMgr_ClearCompartment(cmpmgr,tid,&CLSID_FakeService);
    enum_compartments(cmpmgr,NULL,&CLSID_FakeService);
    ITfCompartmentMgr_Release(cmpmgr);
    ITfCompartment_Release(cmp);

    /* DocumentMgr */
    hr = ITfDocumentMgr_QueryInterface(dm, &IID_ITfCompartmentMgr, (LPVOID*)&cmpmgr);
    ok(SUCCEEDED(hr),"DocumentMgr QI for IID_ITfCompartmentMgr failed\n");

    hr = ITfCompartmentMgr_GetCompartment(cmpmgr, &GUID_COMPARTMENT_PERSISTMENUENABLED, &cmp);
    ok(SUCCEEDED(hr),"GetCompartment failed\n");
    enum_compartments(cmpmgr,&GUID_COMPARTMENT_PERSISTMENUENABLED,&GUID_COMPARTMENT_SPEECH_OPENCLOSE);
    ITfCompartmentMgr_Release(cmpmgr);

    /* Context */
    hr = ITfContext_QueryInterface(cxt, &IID_ITfCompartmentMgr, (LPVOID*)&cmpmgr);
    ok(SUCCEEDED(hr),"Context QI for IID_ITfCompartmentMgr failed\n");
    enum_compartments(cmpmgr,NULL,&GUID_COMPARTMENT_PERSISTMENUENABLED);
    ITfCompartmentMgr_Release(cmpmgr);

    ITfContext_Release(cxt);
    ITfDocumentMgr_Release(dm);
}