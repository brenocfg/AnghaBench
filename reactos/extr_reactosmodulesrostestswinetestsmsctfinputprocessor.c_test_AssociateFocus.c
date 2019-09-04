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
typedef  int /*<<< orphan*/  ITfDocumentMgr ;
typedef  int /*<<< orphan*/ * HWND ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/ * CreateWindowA (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DestroyWindow (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/ * FOCUS_IGNORE ; 
 void* FOCUS_SAVE ; 
 int /*<<< orphan*/  ITfDocumentMgr_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ITfThreadMgr_AssociateFocus (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  ITfThreadMgr_CreateDocumentMgr (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  ITfThreadMgr_GetFocus (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  ITfThreadMgr_SetFocus (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 void* SINK_IGNORE ; 
 void* SINK_OPTIONAL ; 
 void* SINK_SAVE ; 
 void* SINK_UNEXPECTED ; 
 int SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SW_SHOWNORMAL ; 
 int /*<<< orphan*/  SetFocus (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ShowWindow (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  WS_POPUP ; 
 scalar_t__ broken (int) ; 
 int /*<<< orphan*/  g_tm ; 
 int /*<<< orphan*/  ok (int,char*) ; 
 int /*<<< orphan*/  processPendingMessages () ; 
 int /*<<< orphan*/  sink_check_ok (void**,char*) ; 
 int /*<<< orphan*/  sink_check_saved (void**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 void* test_ACP_GetSelection ; 
 void* test_ACP_GetStatus ; 
 void* test_ACP_RequestLock ; 
 int /*<<< orphan*/ * test_CurrentFocus ; 
 void* test_OnInitDocumentMgr ; 
 void* test_OnPopContext ; 
 void* test_OnPushContext ; 
 void* test_OnSetFocus ; 
 int /*<<< orphan*/ * test_PrevFocus ; 
 int /*<<< orphan*/  test_ShouldDeactivate ; 

__attribute__((used)) static void test_AssociateFocus(void)
{
    ITfDocumentMgr *dm1, *dm2, *olddm, *dmcheck, *dmorig;
    HWND wnd1, wnd2, wnd3;
    HRESULT hr;

    ITfThreadMgr_GetFocus(g_tm, &dmorig);
    test_CurrentFocus = NULL;
    test_PrevFocus = dmorig;
    test_OnSetFocus  = SINK_OPTIONAL; /* Doesn't always fire on Win7 */
    test_ACP_GetStatus = SINK_OPTIONAL;
    hr = ITfThreadMgr_SetFocus(g_tm,NULL);
    ok(SUCCEEDED(hr),"ITfThreadMgr_SetFocus failed\n");
    sink_check_ok(&test_OnSetFocus,"OnSetFocus");
    test_ACP_GetStatus = SINK_UNEXPECTED;
    ITfDocumentMgr_Release(dmorig);

    hr = ITfThreadMgr_CreateDocumentMgr(g_tm,&dm1);
    ok(SUCCEEDED(hr),"CreateDocumentMgr failed\n");

    hr = ITfThreadMgr_CreateDocumentMgr(g_tm,&dm2);
    ok(SUCCEEDED(hr),"CreateDocumentMgr failed\n");

    wnd1 = CreateWindowA("edit",NULL,WS_POPUP,0,0,200,60,NULL,NULL,NULL,NULL);
    ok(wnd1!=NULL,"Unable to create window 1\n");
    wnd2 = CreateWindowA("edit",NULL,WS_POPUP,0,65,200,60,NULL,NULL,NULL,NULL);
    ok(wnd2!=NULL,"Unable to create window 2\n");
    wnd3 = CreateWindowA("edit",NULL,WS_POPUP,0,130,200,60,NULL,NULL,NULL,NULL);
    ok(wnd3!=NULL,"Unable to create window 3\n");

    processPendingMessages();

    test_OnInitDocumentMgr = SINK_OPTIONAL; /* Vista and greater */
    test_OnPushContext = SINK_OPTIONAL; /* Vista and greater */
    test_OnSetFocus = SINK_OPTIONAL; /* Win7 */
    test_PrevFocus = NULL;
    test_CurrentFocus = FOCUS_IGNORE;

    ShowWindow(wnd1,SW_SHOWNORMAL);
    test_OnSetFocus = SINK_UNEXPECTED;
    SetFocus(wnd1);
    sink_check_ok(&test_OnInitDocumentMgr,"OnInitDocumentMgr");
    sink_check_ok(&test_OnPushContext,"OnPushContext");

    test_OnSetFocus  = SINK_OPTIONAL; /* Vista and greater */
    test_ACP_RequestLock = SINK_OPTIONAL; /* Win7 x64 */
    test_ACP_GetSelection = SINK_OPTIONAL; /* Win7 x64 */
    ITfThreadMgr_GetFocus(g_tm, &test_PrevFocus);
    test_CurrentFocus = FOCUS_IGNORE; /* This is a default system context */
    processPendingMessages();
    sink_check_ok(&test_OnSetFocus,"OnSetFocus");
    test_ACP_RequestLock = SINK_UNEXPECTED;
    test_ACP_GetSelection = SINK_UNEXPECTED;

    test_CurrentFocus = dm1;
    test_PrevFocus = FOCUS_IGNORE;
    test_OnSetFocus  = SINK_OPTIONAL;
    test_ShouldDeactivate = TRUE;
    hr = ITfThreadMgr_AssociateFocus(g_tm,wnd1,dm1,&olddm);
    ok(SUCCEEDED(hr),"AssociateFocus failed\n");
    sink_check_ok(&test_OnSetFocus,"OnSetFocus");
    test_ShouldDeactivate = FALSE;

    processPendingMessages();

    ITfThreadMgr_GetFocus(g_tm, &dmcheck);
    ok(dmcheck == dm1 || broken(dmcheck == dmorig /* Win7+ */), "Expected DocumentMgr not focused\n");
    ITfDocumentMgr_Release(dmcheck);

    /* We need to explicitly set focus on Win7+ */
    test_CurrentFocus = dm1;
    test_PrevFocus = FOCUS_IGNORE;
    test_OnSetFocus = SINK_OPTIONAL; /* Doesn't always fire on Win7+ */
    ITfThreadMgr_SetFocus(g_tm, dm1);
    sink_check_ok(&test_OnSetFocus, "OnSetFocus");

    hr = ITfThreadMgr_AssociateFocus(g_tm,wnd2,dm2,&olddm);
    ok(SUCCEEDED(hr),"AssociateFocus failed\n");
    processPendingMessages();
    ITfThreadMgr_GetFocus(g_tm, &dmcheck);
    ok(dmcheck == dm1, "Expected DocumentMgr not focused\n");
    ITfDocumentMgr_Release(dmcheck);

    hr = ITfThreadMgr_AssociateFocus(g_tm,wnd3,dm2,&olddm);
    ok(SUCCEEDED(hr),"AssociateFocus failed\n");
    processPendingMessages();
    ITfThreadMgr_GetFocus(g_tm, &dmcheck);
    ok(dmcheck == dm1, "Expected DocumentMgr not focused\n");
    ITfDocumentMgr_Release(dmcheck);

    test_CurrentFocus = FOCUS_SAVE;
    test_PrevFocus = FOCUS_SAVE;
    test_OnSetFocus = SINK_SAVE;
    test_ShouldDeactivate = TRUE; /* win 8/10 */
    ShowWindow(wnd2,SW_SHOWNORMAL);
    SetFocus(wnd2);
    sink_check_saved(&test_OnSetFocus,dm1,dm2,"OnSetFocus");
    test_CurrentFocus = FOCUS_IGNORE; /* occasional wine race */
    test_PrevFocus = FOCUS_IGNORE; /* occasional wine race */
    test_OnSetFocus = SINK_IGNORE; /* occasional wine race */
    test_ShouldDeactivate = FALSE;
    processPendingMessages();

    ShowWindow(wnd3,SW_SHOWNORMAL);
    SetFocus(wnd3);
    processPendingMessages();

    test_CurrentFocus = FOCUS_SAVE;
    test_PrevFocus = FOCUS_SAVE;
    test_OnSetFocus = SINK_SAVE;
    SetFocus(wnd1);
    processPendingMessages();
    sink_check_saved(&test_OnSetFocus,dm2,dm1,"OnSetFocus");

    hr = ITfThreadMgr_AssociateFocus(g_tm,wnd3,NULL,&olddm);
    ok(SUCCEEDED(hr),"AssociateFocus failed\n");
    ok(olddm == dm2, "incorrect old DocumentMgr returned\n");
    ITfDocumentMgr_Release(olddm);

    test_CurrentFocus = dmorig;
    test_PrevFocus = dm1;
    test_OnSetFocus  = SINK_OPTIONAL; /* Doesn't always fire on Win7+ */
    test_ACP_GetStatus = SINK_IGNORE;
    ITfThreadMgr_SetFocus(g_tm,dmorig);
    sink_check_ok(&test_OnSetFocus,"OnSetFocus");

    test_CurrentFocus = FOCUS_SAVE;
    test_PrevFocus = FOCUS_SAVE;
    test_OnSetFocus = SINK_SAVE;
    SetFocus(wnd3);
    processPendingMessages();
    sink_check_saved(&test_OnSetFocus,dmorig,FOCUS_IGNORE,"OnSetFocus"); /* CurrentFocus NULL on XP, system default on Vista */

    hr = ITfThreadMgr_AssociateFocus(g_tm,wnd2,NULL,&olddm);
    ok(SUCCEEDED(hr),"AssociateFocus failed\n");
    ok(olddm == dm2, "incorrect old DocumentMgr returned\n");
    ITfDocumentMgr_Release(olddm);
    hr = ITfThreadMgr_AssociateFocus(g_tm,wnd1,NULL,&olddm);
    ok(SUCCEEDED(hr),"AssociateFocus failed\n");
    ok(olddm == dm1, "incorrect old DocumentMgr returned\n");
    ITfDocumentMgr_Release(olddm);

    test_OnSetFocus = SINK_IGNORE; /* OnSetFocus fires a couple of times on Win7 */
    test_CurrentFocus = FOCUS_IGNORE;
    test_PrevFocus = FOCUS_IGNORE;
    SetFocus(wnd2);
    processPendingMessages();
    SetFocus(wnd1);
    processPendingMessages();
    test_OnSetFocus = SINK_UNEXPECTED;

    ITfDocumentMgr_Release(dm1);
    ITfDocumentMgr_Release(dm2);

    test_CurrentFocus = dmorig;
    test_PrevFocus = FOCUS_IGNORE;
    test_OnSetFocus  = SINK_OPTIONAL;
    test_ACP_GetStatus = SINK_IGNORE;
    ITfThreadMgr_SetFocus(g_tm,dmorig);
    sink_check_ok(&test_OnSetFocus,"OnSetFocus");

    test_OnSetFocus = SINK_IGNORE; /* OnSetFocus fires a couple of times on Win7 */
    test_CurrentFocus = FOCUS_IGNORE;
    test_PrevFocus = FOCUS_IGNORE;
    DestroyWindow(wnd1);
    DestroyWindow(wnd2);
    test_OnPopContext = SINK_OPTIONAL; /* Vista and greater */
    test_OnSetFocus = SINK_OPTIONAL; /* Vista and greater */
    ITfThreadMgr_GetFocus(g_tm, &test_PrevFocus);
    test_CurrentFocus = NULL;
    test_ShouldDeactivate = TRUE; /* Win7 */
    DestroyWindow(wnd3);
    test_ShouldDeactivate = FALSE;
    sink_check_ok(&test_OnSetFocus,"OnSetFocus");
    sink_check_ok(&test_OnPopContext,"OnPopContext");
}