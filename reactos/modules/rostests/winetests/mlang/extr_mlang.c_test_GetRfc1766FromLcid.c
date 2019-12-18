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
typedef  int /*<<< orphan*/  buffer ;
struct TYPE_3__ {char* broken_rfc; int /*<<< orphan*/  rfc1766; int /*<<< orphan*/  hr; int /*<<< orphan*/  lcid; } ;
typedef  int /*<<< orphan*/  IMultiLanguage2 ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  size_t DWORD ;
typedef  char CHAR ;
typedef  int /*<<< orphan*/ * BSTR ;

/* Variables and functions */
 size_t ARRAY_SIZE (TYPE_1__*) ; 
 int /*<<< orphan*/  CP_ACP ; 
 int /*<<< orphan*/  E_INVALIDARG ; 
 int /*<<< orphan*/  IMultiLanguage2_GetRfc1766FromLcid (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  LANG_ENGLISH ; 
 int /*<<< orphan*/  LCMAP_LOWERCASE ; 
 int /*<<< orphan*/  LCMapStringA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,char*,int) ; 
 int /*<<< orphan*/  LOCALE_USER_DEFAULT ; 
 int /*<<< orphan*/  MAKELANGID (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int MAX_RFC1766_NAME ; 
 int /*<<< orphan*/  SUBLANG_ENGLISH_US ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  SysFreeString (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WideCharToMultiByte (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ broken (int) ; 
 TYPE_1__* lcid_table ; 
 int /*<<< orphan*/  lstrcmpA (char*,char*) ; 
 scalar_t__ lstrlenA (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ok (int,char*,size_t,...) ; 

__attribute__((used)) static void test_GetRfc1766FromLcid(IMultiLanguage2 *iML2)
{
    CHAR expected[MAX_RFC1766_NAME];
    CHAR buffer[MAX_RFC1766_NAME + 1];
    DWORD i;
    HRESULT hr;
    BSTR rfcstr;

    for(i = 0; i < ARRAY_SIZE(lcid_table); i++) {
        buffer[0] = '\0';

        rfcstr = NULL;
        hr = IMultiLanguage2_GetRfc1766FromLcid(iML2, lcid_table[i].lcid, &rfcstr);
        ok(hr == lcid_table[i].hr,
            "#%02d: HRESULT 0x%x (expected 0x%x)\n", i, hr, lcid_table[i].hr);

        if (hr != S_OK)
            continue;   /* no result-string created */

        WideCharToMultiByte(CP_ACP, 0, rfcstr, -1, buffer, sizeof(buffer), NULL, NULL);
        LCMapStringA(LOCALE_USER_DEFAULT, LCMAP_LOWERCASE, lcid_table[i].rfc1766,
                    lstrlenA(lcid_table[i].rfc1766) + 1, expected, MAX_RFC1766_NAME);

        /* IE <6.0 return "x-kok" for LCID 0x457 ("kok") */
        ok( (!lstrcmpA(buffer, expected)) ||
            broken(!lstrcmpA(buffer, lcid_table[i].broken_rfc)),
            "#%02d: got '%s' (expected '%s')\n", i, buffer, expected);

        SysFreeString(rfcstr);
    }

    hr = IMultiLanguage2_GetRfc1766FromLcid(iML2, MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US), NULL);
    ok(hr == E_INVALIDARG, "got 0x%x (expected E_INVALIDARG)\n", hr);
}