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
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/ * LPVOID ;
typedef  int /*<<< orphan*/ * LPOLESTR ;
typedef  int /*<<< orphan*/  LCID ;
typedef  int /*<<< orphan*/  IFontDisp ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int DISPID ;

/* Variables and functions */
 int /*<<< orphan*/  IFontDisp_GetIDsOfNames (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  IFontDisp_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IID_IFontDisp ; 
 int /*<<< orphan*/  IID_NULL ; 
 int /*<<< orphan*/  ok (int,char*,char const*,...) ; 
 int /*<<< orphan*/  pOleCreateFontIndirect (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 

__attribute__((used)) static void test_names_ids(WCHAR* w_name_1, const char* a_name_1,
                    WCHAR* w_name_2, const char* a_name_2,
                    LCID lcid, DISPID id_1, DISPID id_2,
                    HRESULT hres_expect, int numnames)
{
    LPVOID pvObj = NULL;
    IFontDisp *fontdisp = NULL;
    HRESULT hres;
    DISPID rgDispId[2] = {0xdeadbeef, 0xdeadbeef};
    LPOLESTR names[2] = {w_name_1, w_name_2};

    pOleCreateFontIndirect(NULL, &IID_IFontDisp, &pvObj);
    fontdisp = pvObj;

    hres = IFontDisp_GetIDsOfNames(fontdisp, &IID_NULL, names, numnames,
                                   lcid, rgDispId);

    /* test hres */
    ok(hres == hres_expect,
        "GetIDsOfNames: \"%s\", \"%s\" returns 0x%08x, expected 0x%08x.\n",
        a_name_1, a_name_2, hres, hres_expect);

    /* test first DISPID */
    ok(rgDispId[0]==id_1,
        "GetIDsOfNames: \"%s\" gets DISPID 0x%08x, expected 0x%08x.\n",
        a_name_1, rgDispId[0], id_1);

    /* test second DISPID is present */
    if (numnames == 2)
    {
        ok(rgDispId[1]==id_2,
            "GetIDsOfNames: ..., \"%s\" gets DISPID 0x%08x, expected 0x%08x.\n",
            a_name_2, rgDispId[1], id_2);
    }

   IFontDisp_Release(fontdisp);
}