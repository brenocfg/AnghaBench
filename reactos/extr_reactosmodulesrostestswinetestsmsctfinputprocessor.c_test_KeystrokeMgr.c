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
struct TYPE_5__ {char uVKey; int /*<<< orphan*/  uModifiers; } ;
typedef  TYPE_1__ TF_PRESERVEDKEY ;
typedef  int /*<<< orphan*/  LPVOID ;
typedef  int /*<<< orphan*/  ITfKeystrokeMgr ;
typedef  int /*<<< orphan*/  ITfKeyEventSink ;
typedef  scalar_t__ HRESULT ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CLSID_PreservedKey ; 
 scalar_t__ CONNECT_E_ADVISELIMIT ; 
 scalar_t__ CONNECT_E_NOCONNECTION ; 
 scalar_t__ E_INVALIDARG ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  IID_ITfKeystrokeMgr ; 
 int /*<<< orphan*/  ITfKeyEventSink_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ ITfKeystrokeMgr_AdviseKeyEventSink (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ ITfKeystrokeMgr_IsPreservedKey (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*,scalar_t__*) ; 
 scalar_t__ ITfKeystrokeMgr_PreserveKey (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ITfKeystrokeMgr_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ ITfKeystrokeMgr_UnadviseKeyEventSink (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ ITfKeystrokeMgr_UnpreserveKey (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*) ; 
 scalar_t__ ITfThreadMgr_QueryInterface (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KeyEventSink_Constructor (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  SINK_EXPECTED ; 
 int SUCCEEDED (scalar_t__) ; 
 scalar_t__ S_FALSE ; 
 scalar_t__ S_OK ; 
 scalar_t__ TF_E_ALREADY_EXISTS ; 
 int /*<<< orphan*/  TF_MOD_SHIFT ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  cid ; 
 int /*<<< orphan*/  g_tm ; 
 int /*<<< orphan*/  ok (int,char*) ; 
 int /*<<< orphan*/  sink_check_ok (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  test_KEV_OnSetFocus ; 
 int /*<<< orphan*/  tid ; 

__attribute__((used)) static void test_KeystrokeMgr(void)
{
    ITfKeystrokeMgr *keymgr= NULL;
    HRESULT hr;
    TF_PRESERVEDKEY tfpk;
    BOOL preserved;
    ITfKeyEventSink *sink = NULL;

    KeyEventSink_Constructor(&sink);

    hr = ITfThreadMgr_QueryInterface(g_tm, &IID_ITfKeystrokeMgr, (LPVOID*)&keymgr);
    ok(SUCCEEDED(hr),"Failed to get IID_ITfKeystrokeMgr for ThreadMgr\n");

    tfpk.uVKey = 'A';
    tfpk.uModifiers = TF_MOD_SHIFT;

    test_KEV_OnSetFocus = SINK_EXPECTED;
    hr = ITfKeystrokeMgr_AdviseKeyEventSink(keymgr,tid,sink,TRUE);
    ok(SUCCEEDED(hr),"ITfKeystrokeMgr_AdviseKeyEventSink failed\n");
    sink_check_ok(&test_KEV_OnSetFocus,"KeyEventSink_OnSetFocus");
    hr = ITfKeystrokeMgr_AdviseKeyEventSink(keymgr,tid,sink,TRUE);
    ok(hr == CONNECT_E_ADVISELIMIT,"Wrong return, expected CONNECT_E_ADVISELIMIT\n");
    hr = ITfKeystrokeMgr_AdviseKeyEventSink(keymgr,cid,sink,TRUE);
    ok(hr == E_INVALIDARG,"Wrong return, expected E_INVALIDARG\n");

    hr =ITfKeystrokeMgr_PreserveKey(keymgr, 0, &CLSID_PreservedKey, &tfpk, NULL, 0);
    ok(hr==E_INVALIDARG,"ITfKeystrokeMgr_PreserveKey improperly succeeded\n");

    hr =ITfKeystrokeMgr_PreserveKey(keymgr, tid, &CLSID_PreservedKey, &tfpk, NULL, 0);
    ok(SUCCEEDED(hr),"ITfKeystrokeMgr_PreserveKey failed\n");

    hr =ITfKeystrokeMgr_PreserveKey(keymgr, tid, &CLSID_PreservedKey, &tfpk, NULL, 0);
    ok(hr == TF_E_ALREADY_EXISTS,"ITfKeystrokeMgr_PreserveKey improperly succeeded\n");

    preserved = FALSE;
    hr = ITfKeystrokeMgr_IsPreservedKey(keymgr, &CLSID_PreservedKey, &tfpk, &preserved);
    ok(hr == S_OK, "ITfKeystrokeMgr_IsPreservedKey failed\n");
    if (hr == S_OK) ok(preserved == TRUE,"misreporting preserved key\n");

    hr = ITfKeystrokeMgr_UnpreserveKey(keymgr, &CLSID_PreservedKey,&tfpk);
    ok(SUCCEEDED(hr),"ITfKeystrokeMgr_UnpreserveKey failed\n");

    hr = ITfKeystrokeMgr_IsPreservedKey(keymgr, &CLSID_PreservedKey, &tfpk, &preserved);
    ok(hr == S_FALSE, "ITfKeystrokeMgr_IsPreservedKey failed\n");
    if (hr == S_FALSE) ok(preserved == FALSE,"misreporting preserved key\n");

    hr = ITfKeystrokeMgr_UnpreserveKey(keymgr, &CLSID_PreservedKey,&tfpk);
    ok(hr==CONNECT_E_NOCONNECTION,"ITfKeystrokeMgr_UnpreserveKey improperly succeeded\n");

    hr = ITfKeystrokeMgr_UnadviseKeyEventSink(keymgr,tid);
    ok(SUCCEEDED(hr),"ITfKeystrokeMgr_UnadviseKeyEventSink failed\n");

    ITfKeystrokeMgr_Release(keymgr);
    ITfKeyEventSink_Release(sink);
}