#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  clsid ;
typedef  char WCHAR ;
typedef  int UINT ;
struct TYPE_11__ {int Data1; } ;
struct TYPE_10__ {int Data1; int Data2; } ;
typedef  int HRESULT ;
typedef  TYPE_1__ CLSID ;

/* Variables and functions */
 int CLSIDFromString (char*,TYPE_1__*) ; 
 TYPE_5__ CLSID_NULL ; 
 TYPE_5__ CLSID_StdFont ; 
 int CO_E_CLASSSTRING ; 
 TYPE_5__ IID_IClassFactory ; 
 int IsEqualCLSID (TYPE_1__*,TYPE_5__*) ; 
 int S_OK ; 
 char* cf_brokenW ; 
 int /*<<< orphan*/  lstrcpyW (char*,char*) ; 
 int lstrlenW (char*) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  ok_ole_success (int,char*) ; 
 int wine_dbgstr_guid (TYPE_1__*) ; 
 char* wszCLSID_StdFont ; 

__attribute__((used)) static void test_CLSIDFromString(void)
{
    CLSID clsid;
    WCHAR wszCLSID_Broken[50];
    UINT i;

    HRESULT hr = CLSIDFromString(wszCLSID_StdFont, &clsid);
    ok_ole_success(hr, "CLSIDFromString");
    ok(IsEqualCLSID(&clsid, &CLSID_StdFont), "clsid wasn't equal to CLSID_StdFont\n");

    memset(&clsid, 0xab, sizeof(clsid));
    hr = CLSIDFromString(NULL, &clsid);
    ok(hr == S_OK, "got 0x%08x\n", hr);
    ok(IsEqualCLSID(&clsid, &CLSID_NULL), "clsid wasn't equal to CLSID_NULL\n");

    /* string is longer, but starts with a valid CLSID */
    memset(&clsid, 0, sizeof(clsid));
    hr = CLSIDFromString(cf_brokenW, &clsid);
    ok(hr == CO_E_CLASSSTRING, "got 0x%08x\n", hr);
    ok(IsEqualCLSID(&clsid, &IID_IClassFactory), "got %s\n", wine_dbgstr_guid(&clsid));

    lstrcpyW(wszCLSID_Broken, wszCLSID_StdFont);
    for(i = lstrlenW(wszCLSID_StdFont); i < 49; i++)
        wszCLSID_Broken[i] = 'A';
    wszCLSID_Broken[i] = '\0';

    memset(&clsid, 0, sizeof(CLSID));
    hr = CLSIDFromString(wszCLSID_Broken, &clsid);
    ok(hr == CO_E_CLASSSTRING, "Got %08x\n", hr);
    ok(IsEqualCLSID(&clsid, &CLSID_StdFont), "clsid wasn't equal to CLSID_StdFont\n");

    wszCLSID_Broken[lstrlenW(wszCLSID_StdFont)-1] = 'A';
    memset(&clsid, 0, sizeof(CLSID));
    hr = CLSIDFromString(wszCLSID_Broken, &clsid);
    ok(hr == CO_E_CLASSSTRING, "Got %08x\n", hr);
    ok(IsEqualCLSID(&clsid, &CLSID_StdFont), "clsid wasn't equal to CLSID_StdFont\n");

    wszCLSID_Broken[lstrlenW(wszCLSID_StdFont)] = '\0';
    memset(&clsid, 0, sizeof(CLSID));
    hr = CLSIDFromString(wszCLSID_Broken, &clsid);
    ok(hr == CO_E_CLASSSTRING, "Got %08x\n", hr);
    ok(IsEqualCLSID(&clsid, &CLSID_StdFont), "clsid wasn't equal to CLSID_StdFont\n");

    wszCLSID_Broken[lstrlenW(wszCLSID_StdFont)-1] = '\0';
    memset(&clsid, 0, sizeof(CLSID));
    hr = CLSIDFromString(wszCLSID_Broken, &clsid);
    ok(hr == CO_E_CLASSSTRING, "Got %08x\n", hr);
    ok(IsEqualCLSID(&clsid, &CLSID_StdFont), "clsid wasn't equal to CLSID_StdFont\n");

    memset(&clsid, 0xcc, sizeof(CLSID));
    hr = CLSIDFromString(wszCLSID_Broken+1, &clsid);
    ok(hr == CO_E_CLASSSTRING, "Got %08x\n", hr);
    ok(IsEqualCLSID(&clsid, &CLSID_NULL), "clsid wasn't equal to CLSID_NULL\n");

    wszCLSID_Broken[9] = '*';
    memset(&clsid, 0xcc, sizeof(CLSID));
    hr = CLSIDFromString(wszCLSID_Broken, &clsid);
    ok(hr == CO_E_CLASSSTRING, "Got %08x\n", hr);
    ok(clsid.Data1 == CLSID_StdFont.Data1, "Got %08x\n", clsid.Data1);
    ok(clsid.Data2 == 0xcccc, "Got %04x\n", clsid.Data2);

    wszCLSID_Broken[3] = '*';
    memset(&clsid, 0xcc, sizeof(CLSID));
    hr = CLSIDFromString(wszCLSID_Broken, &clsid);
    ok(hr == CO_E_CLASSSTRING, "Got %08x\n", hr);
    ok(clsid.Data1 == 0xb, "Got %08x\n", clsid.Data1);
    ok(clsid.Data2 == 0xcccc, "Got %04x\n", clsid.Data2);

    wszCLSID_Broken[3] = '\0';
    memset(&clsid, 0xcc, sizeof(CLSID));
    hr = CLSIDFromString(wszCLSID_Broken, &clsid);
    ok(hr == CO_E_CLASSSTRING, "Got %08x\n", hr);
    ok(clsid.Data1 == 0xb, "Got %08x\n", clsid.Data1);
    ok(clsid.Data2 == 0xcccc, "Got %04x\n", clsid.Data2);
}