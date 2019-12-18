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
typedef  int ULONG ;
struct TYPE_3__ {int /*<<< orphan*/  wszRfc1766; int /*<<< orphan*/  lcid; int /*<<< orphan*/  wszLocaleName; } ;
typedef  TYPE_1__ RFC1766INFO ;
typedef  int /*<<< orphan*/  IMultiLanguage2 ;
typedef  int /*<<< orphan*/  IEnumRfc1766 ;
typedef  scalar_t__ HRESULT ;
typedef  int /*<<< orphan*/  BSTR ;

/* Variables and functions */
 scalar_t__ IEnumRfc1766_Next (int /*<<< orphan*/ *,int,TYPE_1__*,int*) ; 
 int /*<<< orphan*/  IEnumRfc1766_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IMultiLanguage2_EnumRfc1766 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ IMultiLanguage2_GetRfc1766FromLcid (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LANG_NEUTRAL ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  SysFreeString (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/ * strstrW (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wine_dbgstr_w (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_rfc1766(IMultiLanguage2 *iML2)
{
    IEnumRfc1766 *pEnumRfc1766;
    RFC1766INFO info;
    ULONG n;
    HRESULT ret;
    BSTR rfcstr;

    ret = IMultiLanguage2_EnumRfc1766(iML2, LANG_NEUTRAL, &pEnumRfc1766);
    ok(ret == S_OK, "IMultiLanguage2_EnumRfc1766 error %08x\n", ret);

    while (1)
    {
        ret = IEnumRfc1766_Next(pEnumRfc1766, 1, &info, &n);
        if (ret != S_OK) break;

#ifdef DUMP_CP_INFO
        trace("lcid %04x rfc_name %s locale_name %s\n",
              info.lcid, wine_dbgstr_w(info.wszRfc1766), wine_dbgstr_w(info.wszLocaleName));
#endif

        ok(n == 1, "couldn't fetch 1 RFC1766INFO structure\n");

        /* verify the Rfc1766 value */
        ret = IMultiLanguage2_GetRfc1766FromLcid(iML2, info.lcid, &rfcstr);
        ok(ret == S_OK, "Expected S_OK, got %08x\n", ret);

        /* not an exact 1:1 correspondence between lcid and rfc1766 in the
         * mlang database, e.g., nb-no -> 1044 -> no */
        ok(strstrW(info.wszRfc1766, rfcstr) != NULL,
           "Expected matching locale names\n");

        SysFreeString(rfcstr);
    }
    IEnumRfc1766_Release(pEnumRfc1766);
}