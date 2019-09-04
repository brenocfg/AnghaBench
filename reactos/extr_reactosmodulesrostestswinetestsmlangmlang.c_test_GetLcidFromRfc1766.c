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
struct TYPE_3__ {int broken_lcid; int lcid; int /*<<< orphan*/  hr; int /*<<< orphan*/  rfc1766; } ;
typedef  int LCID ;
typedef  int /*<<< orphan*/  IMultiLanguage2 ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  size_t DWORD ;
typedef  int /*<<< orphan*/  BSTR ;

/* Variables and functions */
 size_t ARRAY_SIZE (TYPE_1__*) ; 
 int /*<<< orphan*/  CP_ACP ; 
 int /*<<< orphan*/  E_FAIL ; 
 int /*<<< orphan*/  E_INVALIDARG ; 
 int /*<<< orphan*/  IMultiLanguage2_GetLcidFromRfc1766 (int /*<<< orphan*/ *,int*,char*) ; 
 int /*<<< orphan*/  IMultiLanguage2_GetRfc1766FromLcid (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MAX_RFC1766_NAME ; 
 int /*<<< orphan*/  MultiByteToWideChar (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_FALSE ; 
 int /*<<< orphan*/  S_OK ; 
 scalar_t__ broken (int) ; 
 TYPE_1__* lcid_table ; 
 int /*<<< orphan*/  ok (int,char*,size_t,...) ; 
 int /*<<< orphan*/  ok_w2 (char*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_GetLcidFromRfc1766(IMultiLanguage2 *iML2)
{
    WCHAR rfc1766W[MAX_RFC1766_NAME + 1];
    LCID lcid;
    HRESULT ret;
    DWORD i;

    static WCHAR en[] = { 'e','n',0 };
    static WCHAR en_them[] = { 'e','n','-','t','h','e','m',0 };
    static WCHAR english[] = { 'e','n','g','l','i','s','h',0 };


    for(i = 0; i < ARRAY_SIZE(lcid_table); i++) {
        lcid = -1;
        MultiByteToWideChar(CP_ACP, 0, lcid_table[i].rfc1766, -1, rfc1766W, MAX_RFC1766_NAME);
        ret = IMultiLanguage2_GetLcidFromRfc1766(iML2, &lcid, rfc1766W);

        /* IE <6.0 guess 0x412 (ko) from "kok" */
        ok((ret == lcid_table[i].hr) ||
            broken(lcid_table[i].broken_lcid && (ret == S_FALSE)),
            "#%02d: HRESULT 0x%x (expected 0x%x)\n", i, ret, lcid_table[i].hr);

        ok((lcid == lcid_table[i].lcid) ||
            broken(lcid == lcid_table[i].broken_lcid),   /* IE <6.0 */
            "#%02d: got LCID 0x%x (expected 0x%x)\n", i, lcid, lcid_table[i].lcid);
    }


    ret = IMultiLanguage2_GetLcidFromRfc1766(iML2, NULL, en);
    ok(ret == E_INVALIDARG, "GetLcidFromRfc1766 returned: %08x\n", ret);

    ret = IMultiLanguage2_GetLcidFromRfc1766(iML2, &lcid, NULL);
    ok(ret == E_INVALIDARG, "GetLcidFromRfc1766 returned: %08x\n", ret);

    ret = IMultiLanguage2_GetLcidFromRfc1766(iML2, &lcid, en_them);
    ok((ret == E_FAIL || ret == S_FALSE), "GetLcidFromRfc1766 returned: %08x\n", ret);
    if (ret == S_FALSE)
    {
        BSTR rfcstr;
        static WCHAR en[] = {'e','n',0};

        ret = IMultiLanguage2_GetRfc1766FromLcid(iML2, lcid, &rfcstr);
        ok(ret == S_OK, "Expected S_OK, got %08x\n", ret);
        ok_w2("Expected \"%s\",  got \"%s\"n", en, rfcstr);
    }

    ret = IMultiLanguage2_GetLcidFromRfc1766(iML2, &lcid, english);
    ok((ret == E_FAIL || ret == S_FALSE), "GetLcidFromRfc1766 returned: %08x\n", ret);
    if (ret == S_FALSE)
    {
        BSTR rfcstr;
        static WCHAR en[] = {'e','n',0};

        ret = IMultiLanguage2_GetRfc1766FromLcid(iML2, lcid, &rfcstr);
        ok(ret == S_OK, "Expected S_OK, got %08x\n", ret);
        ok_w2("Expected \"%s\",  got \"%s\"n", en, rfcstr);
    }

}