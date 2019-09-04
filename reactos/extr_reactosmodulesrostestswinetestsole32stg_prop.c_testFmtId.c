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
typedef  int /*<<< orphan*/  fmtid ;
typedef  int WCHAR ;
typedef  scalar_t__ HRESULT ;
typedef  int FMTID ;

/* Variables and functions */
 int /*<<< orphan*/  CharUpperW (int*) ; 
 scalar_t__ E_INVALIDARG ; 
 int FMTID_DocSummaryInformation ; 
 int FMTID_SummaryInformation ; 
 int FMTID_UserDefinedProperties ; 
 int IID_IPropertySetStorage ; 
 scalar_t__ STG_E_INVALIDNAME ; 
 scalar_t__ S_OK ; 
 int lstrlenW (int*) ; 
 int /*<<< orphan*/  memcmp (int*,int*,int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 scalar_t__ pFmtIdToPropStgName (int*,int*) ; 
 scalar_t__ pPropStgNameToFmtId (int*,int*) ; 

__attribute__((used)) static void testFmtId(void)
{
    WCHAR szSummaryInfo[] = { 5,'S','u','m','m','a','r','y',
        'I','n','f','o','r','m','a','t','i','o','n',0 };
    WCHAR szDocSummaryInfo[] = { 5,'D','o','c','u','m','e','n','t',
        'S','u','m','m','a','r','y','I','n','f','o','r','m','a','t','i','o','n',
        0 };
    WCHAR szIID_IPropSetStg[] = { 5,'0','j','a','a','a','a','a',
        'a','A','a','a','a','a','a','d','a','A','a','a','a','a','a','a','a','G',
        'c',0 };
    WCHAR name[32];
    FMTID fmtid;
    HRESULT hr;

    if (pFmtIdToPropStgName) {
    hr = pFmtIdToPropStgName(NULL, name);
    ok(hr == E_INVALIDARG, "Expected E_INVALIDARG, got 0x%08x\n", hr);
    hr = pFmtIdToPropStgName(&FMTID_SummaryInformation, NULL);
    ok(hr == E_INVALIDARG, "Expected E_INVALIDARG, got 0x%08x\n", hr);
    hr = pFmtIdToPropStgName(&FMTID_SummaryInformation, name);
    ok(hr == S_OK, "FmtIdToPropStgName failed: 0x%08x\n", hr);
    ok(!memcmp(name, szSummaryInfo, (lstrlenW(szSummaryInfo) + 1) *
     sizeof(WCHAR)), "Got wrong name for FMTID_SummaryInformation\n");
    hr = pFmtIdToPropStgName(&FMTID_DocSummaryInformation, name);
    ok(hr == S_OK, "FmtIdToPropStgName failed: 0x%08x\n", hr);
    ok(!memcmp(name, szDocSummaryInfo, (lstrlenW(szDocSummaryInfo) + 1) *
     sizeof(WCHAR)), "Got wrong name for FMTID_DocSummaryInformation\n");
    hr = pFmtIdToPropStgName(&FMTID_UserDefinedProperties, name);
    ok(hr == S_OK, "FmtIdToPropStgName failed: 0x%08x\n", hr);
    ok(!memcmp(name, szDocSummaryInfo, (lstrlenW(szDocSummaryInfo) + 1) *
     sizeof(WCHAR)), "Got wrong name for FMTID_DocSummaryInformation\n");
    hr = pFmtIdToPropStgName(&IID_IPropertySetStorage, name);
    ok(hr == S_OK, "FmtIdToPropStgName failed: 0x%08x\n", hr);
    ok(!memcmp(name, szIID_IPropSetStg, (lstrlenW(szIID_IPropSetStg) + 1) *
     sizeof(WCHAR)), "Got wrong name for IID_IPropertySetStorage\n");
    }

    if(pPropStgNameToFmtId) {
    /* test args first */
    hr = pPropStgNameToFmtId(NULL, NULL);
    ok(hr == E_INVALIDARG, "Expected E_INVALIDARG, got 0x%08x\n", hr);
    hr = pPropStgNameToFmtId(NULL, &fmtid);
    ok(hr == STG_E_INVALIDNAME, "Expected STG_E_INVALIDNAME, got 0x%08x\n",
     hr);
    hr = pPropStgNameToFmtId(szDocSummaryInfo, NULL);
    ok(hr == E_INVALIDARG, "Expected E_INVALIDARG, got 0x%08x\n", hr);
    /* test the known format IDs */
    hr = pPropStgNameToFmtId(szSummaryInfo, &fmtid);
    ok(hr == S_OK, "PropStgNameToFmtId failed: 0x%08x\n", hr);
    ok(!memcmp(&fmtid, &FMTID_SummaryInformation, sizeof(fmtid)),
     "Got unexpected FMTID, expected FMTID_SummaryInformation\n");
    hr = pPropStgNameToFmtId(szDocSummaryInfo, &fmtid);
    ok(hr == S_OK, "PropStgNameToFmtId failed: 0x%08x\n", hr);
    ok(!memcmp(&fmtid, &FMTID_DocSummaryInformation, sizeof(fmtid)),
     "Got unexpected FMTID, expected FMTID_DocSummaryInformation\n");
    /* test another GUID */
    hr = pPropStgNameToFmtId(szIID_IPropSetStg, &fmtid);
    ok(hr == S_OK, "PropStgNameToFmtId failed: 0x%08x\n", hr);
    ok(!memcmp(&fmtid, &IID_IPropertySetStorage, sizeof(fmtid)),
     "Got unexpected FMTID, expected IID_IPropertySetStorage\n");
    /* now check case matching */
    CharUpperW(szDocSummaryInfo + 1);
    hr = pPropStgNameToFmtId(szDocSummaryInfo, &fmtid);
    ok(hr == S_OK, "PropStgNameToFmtId failed: 0x%08x\n", hr);
    ok(!memcmp(&fmtid, &FMTID_DocSummaryInformation, sizeof(fmtid)),
     "Got unexpected FMTID, expected FMTID_DocSummaryInformation\n");
    CharUpperW(szIID_IPropSetStg + 1);
    hr = pPropStgNameToFmtId(szIID_IPropSetStg, &fmtid);
    ok(hr == S_OK, "PropStgNameToFmtId failed: 0x%08x\n", hr);
    ok(!memcmp(&fmtid, &IID_IPropertySetStorage, sizeof(fmtid)),
     "Got unexpected FMTID, expected IID_IPropertySetStorage\n");
    }
}