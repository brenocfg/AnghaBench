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
typedef  int /*<<< orphan*/  IUnknown ;
typedef  int /*<<< orphan*/  IOleCommandTarget ;
typedef  scalar_t__ HRESULT ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  BindToStorage ; 
 int /*<<< orphan*/  CGID_MSHTML ; 
 int /*<<< orphan*/  CHECK_CALLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CHECK_CALLED_BROKEN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CLEAR_CALLED (int /*<<< orphan*/ ) ; 
 int EXPECT_SETTITLE ; 
 int EXPECT_UPDATEUI ; 
 int /*<<< orphan*/  Exec_ShellDocView_37 ; 
 int /*<<< orphan*/  Exec_ShellDocView_84 ; 
 scalar_t__ FAILED (scalar_t__) ; 
 int /*<<< orphan*/  GetClassID ; 
 int /*<<< orphan*/  GetDisplayName ; 
 int /*<<< orphan*/  GetHostInfo ; 
 int /*<<< orphan*/  HideUI ; 
 int /*<<< orphan*/  IDM_EDITMODE ; 
 int /*<<< orphan*/  IID_IOleCommandTarget ; 
 scalar_t__ IOleCommandTarget_Exec (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IOleCommandTarget_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IUnknown_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  InPlaceFrame_SetBorderSpace ; 
 int /*<<< orphan*/  InPlaceUIWindow_SetActiveObject ; 
 int /*<<< orphan*/  Invoke_AMBIENT_OFFLINEIFNOTCONNECTED ; 
 int /*<<< orphan*/  Invoke_AMBIENT_SILENT ; 
 int /*<<< orphan*/  Invoke_OnReadyStateChange_Loading ; 
 int /*<<< orphan*/  IsSystemMoniker ; 
 int /*<<< orphan*/  LD_DOLOAD ; 
 int /*<<< orphan*/  OLECMDEXECOPT_DODEFAULT ; 
 int /*<<< orphan*/  OnChanged_READYSTATE ; 
 int /*<<< orphan*/  SET_EXPECT (int /*<<< orphan*/ ) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  SetStatusText ; 
 int /*<<< orphan*/  ShowUI ; 
 void* TRUE ; 
 void* editmode ; 
 int /*<<< orphan*/ * expect_status_text ; 
 int /*<<< orphan*/  load_state ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 
 void* readystate_set_loading ; 
 int /*<<< orphan*/  test_timer (int) ; 

__attribute__((used)) static void test_exec_editmode(IUnknown *unk, BOOL loaded)
{
    IOleCommandTarget *cmdtrg;
    HRESULT hres;

    hres = IUnknown_QueryInterface(unk, &IID_IOleCommandTarget, (void**)&cmdtrg);
    ok(hres == S_OK, "QueryInterface(IID_IOleCommandTarget) failed: %08x\n", hres);
    if(FAILED(hres))
        return;

    editmode = TRUE;

    if(loaded) {
        load_state = LD_DOLOAD;
        SET_EXPECT(GetClassID);
    }
    SET_EXPECT(SetStatusText);
    SET_EXPECT(Exec_ShellDocView_37);
    SET_EXPECT(GetHostInfo);
    if(loaded)
        SET_EXPECT(GetDisplayName);
    SET_EXPECT(Invoke_AMBIENT_SILENT);
    SET_EXPECT(Invoke_AMBIENT_OFFLINEIFNOTCONNECTED);
    SET_EXPECT(OnChanged_READYSTATE);
    SET_EXPECT(Invoke_OnReadyStateChange_Loading);
    SET_EXPECT(IsSystemMoniker);
    SET_EXPECT(Exec_ShellDocView_84);
    if(loaded)
        SET_EXPECT(BindToStorage);
    SET_EXPECT(InPlaceUIWindow_SetActiveObject);
    SET_EXPECT(HideUI);
    SET_EXPECT(ShowUI);
    SET_EXPECT(InPlaceFrame_SetBorderSpace);

    expect_status_text = NULL;
    readystate_set_loading = TRUE;

    hres = IOleCommandTarget_Exec(cmdtrg, &CGID_MSHTML, IDM_EDITMODE,
            OLECMDEXECOPT_DODEFAULT, NULL, NULL);
    ok(hres == S_OK, "Exec failed: %08x\n", hres);

    if(loaded)
        CHECK_CALLED(GetClassID);
    CHECK_CALLED(SetStatusText);
    CHECK_CALLED(Exec_ShellDocView_37);
    CHECK_CALLED(GetHostInfo);
    if(loaded)
        CHECK_CALLED(GetDisplayName);
    CHECK_CALLED(Invoke_AMBIENT_SILENT);
    CHECK_CALLED(Invoke_AMBIENT_OFFLINEIFNOTCONNECTED);
    CHECK_CALLED(OnChanged_READYSTATE);
    CHECK_CALLED(Invoke_OnReadyStateChange_Loading);
    CLEAR_CALLED(IsSystemMoniker); /* IE7 */
    CHECK_CALLED_BROKEN(Exec_ShellDocView_84);
    if(loaded)
        CHECK_CALLED(BindToStorage);
    CHECK_CALLED(InPlaceUIWindow_SetActiveObject);
    CHECK_CALLED(HideUI);
    CHECK_CALLED(ShowUI);
    CHECK_CALLED(InPlaceFrame_SetBorderSpace);

    test_timer(EXPECT_UPDATEUI|EXPECT_SETTITLE);

    IOleCommandTarget_Release(cmdtrg);

    hres = IOleCommandTarget_Exec(cmdtrg, &CGID_MSHTML, IDM_EDITMODE,
            OLECMDEXECOPT_DODEFAULT, NULL, NULL);
    ok(hres == S_OK, "Exec failed: %08x\n", hres);
}