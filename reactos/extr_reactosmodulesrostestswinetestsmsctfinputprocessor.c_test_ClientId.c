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
typedef  scalar_t__ TfClientId ;
typedef  int /*<<< orphan*/  LPVOID ;
typedef  int /*<<< orphan*/  ITfClientId ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  GUID ;

/* Variables and functions */
 int /*<<< orphan*/  CLSID_FakeService ; 
 int /*<<< orphan*/  CoCreateGuid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GUID_NULL ; 
 int /*<<< orphan*/  IID_ITfClientId ; 
 int /*<<< orphan*/  ITfClientId_GetClientId (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  ITfClientId_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ITfThreadMgr_QueryInterface (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int SUCCEEDED (int /*<<< orphan*/ ) ; 
 scalar_t__ cid ; 
 int /*<<< orphan*/  g_tm ; 
 int /*<<< orphan*/  ok (int,char*) ; 
 scalar_t__ tid ; 

__attribute__((used)) static void test_ClientId(void)
{
    ITfClientId *pcid;
    TfClientId id1,id2;
    HRESULT hr;
    GUID g2;

    hr = ITfThreadMgr_QueryInterface(g_tm, &IID_ITfClientId, (LPVOID*)&pcid);
    ok(SUCCEEDED(hr),"Unable to acquire ITfClientId interface\n");

    CoCreateGuid(&g2);

    hr = ITfClientId_GetClientId(pcid,&GUID_NULL,&id1);
    ok(SUCCEEDED(hr),"GetClientId failed\n");
    hr = ITfClientId_GetClientId(pcid,&GUID_NULL,&id2);
    ok(SUCCEEDED(hr),"GetClientId failed\n");
    ok(id1==id2,"Id's for GUID_NULL do not match\n");
    hr = ITfClientId_GetClientId(pcid,&CLSID_FakeService,&id2);
    ok(SUCCEEDED(hr),"GetClientId failed\n");
    ok(id2!=id1,"Id matches GUID_NULL\n");
    ok(id2==tid,"Id for CLSID_FakeService not matching tid\n");
    ok(id2!=cid,"Id for CLSID_FakeService matching cid\n");
    hr = ITfClientId_GetClientId(pcid,&g2,&id2);
    ok(SUCCEEDED(hr),"GetClientId failed\n");
    ok(id2!=id1,"Id matches GUID_NULL\n");
    ok(id2!=tid,"Id for random guid matching tid\n");
    ok(id2!=cid,"Id for random guid matching cid\n");
    ITfClientId_Release(pcid);
}