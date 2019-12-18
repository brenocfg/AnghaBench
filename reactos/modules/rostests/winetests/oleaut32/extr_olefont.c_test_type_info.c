#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  char WCHAR ;
typedef  int /*<<< orphan*/  VARIANT ;
typedef  int UINT ;
struct TYPE_3__ {int /*<<< orphan*/ * rgvarg; scalar_t__ cArgs; int /*<<< orphan*/ * rgdispidNamedArgs; scalar_t__ cNamedArgs; } ;
typedef  int /*<<< orphan*/ * LPVOID ;
typedef  int /*<<< orphan*/  LCID ;
typedef  int /*<<< orphan*/  ITypeInfo ;
typedef  int /*<<< orphan*/  IFontDisp ;
typedef  int HRESULT ;
typedef  TYPE_1__ DISPPARAMS ;
typedef  int /*<<< orphan*/  BSTR ;

/* Variables and functions */
 int /*<<< orphan*/  DISPATCH_PROPERTYGET ; 
 int /*<<< orphan*/  DISPID_FONT_NAME ; 
 int IFontDisp_GetTypeInfo (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int IFontDisp_Invoke (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IFontDisp_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IID_IFontDisp ; 
 int /*<<< orphan*/  IID_NULL ; 
 int ITypeInfo_GetNames (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int*) ; 
 int /*<<< orphan*/  ITypeInfo_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LANG_ENGLISH ; 
 int /*<<< orphan*/  LOCALE_NEUTRAL ; 
 int /*<<< orphan*/  MAKELANGID (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAKELCID (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SORT_DEFAULT ; 
 int /*<<< orphan*/  SUBLANG_ENGLISH_US ; 
 int S_OK ; 
 int /*<<< orphan*/  SysFreeString (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VariantClear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VariantInit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lstrcmpiW (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  pOleCreateFontIndirect (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 

__attribute__((used)) static void test_type_info(void)
{
        LPVOID pvObj = NULL;
        HRESULT hres;
        IFontDisp*  fontdisp = NULL;
	ITypeInfo* pTInfo;
	WCHAR name_Name[] = {'N','a','m','e',0};
	BSTR names[3];
	UINT n;
        LCID en_us = MAKELCID(MAKELANGID(LANG_ENGLISH,SUBLANG_ENGLISH_US),
                SORT_DEFAULT);
        DISPPARAMS dispparams;
        VARIANT varresult;

        pOleCreateFontIndirect(NULL, &IID_IFontDisp, &pvObj);
        fontdisp = pvObj;

	hres = IFontDisp_GetTypeInfo(fontdisp, 0, en_us, &pTInfo);
	ok(hres == S_OK, "GTI returned 0x%08x instead of S_OK.\n", hres);
	ok(pTInfo != NULL, "GTI returned NULL.\n");

	hres = ITypeInfo_GetNames(pTInfo, DISPID_FONT_NAME, names, 3, &n);
	ok(hres == S_OK, "GetNames returned 0x%08x instead of S_OK.\n", hres);
	ok(n == 1, "GetNames returned %d names instead of 1.\n", n);
	ok(!lstrcmpiW(names[0],name_Name), "DISPID_FONT_NAME doesn't get 'Names'.\n");
	SysFreeString(names[0]);

	ITypeInfo_Release(pTInfo);

        dispparams.cNamedArgs = 0;
        dispparams.rgdispidNamedArgs = NULL;
        dispparams.cArgs = 0;
        dispparams.rgvarg = NULL;
        VariantInit(&varresult);
        hres = IFontDisp_Invoke(fontdisp, DISPID_FONT_NAME, &IID_NULL,
            LOCALE_NEUTRAL, DISPATCH_PROPERTYGET, &dispparams, &varresult,
            NULL, NULL);
        ok(hres == S_OK, "IFontDisp_Invoke return 0x%08x instead of S_OK.\n", hres);
        VariantClear(&varresult);

	IFontDisp_Release(fontdisp);
}