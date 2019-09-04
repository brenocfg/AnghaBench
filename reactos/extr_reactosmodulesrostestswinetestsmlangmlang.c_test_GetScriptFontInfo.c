#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sfi ;
typedef  int UINT ;
struct TYPE_4__ {scalar_t__ scripts; int* wszFont; } ;
typedef  TYPE_1__ SCRIPTFONTINFO ;
typedef  int /*<<< orphan*/  IMLangFontLink2 ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  GetLastError () ; 
 scalar_t__ IMLangFontLink2_GetScriptFontInfo (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,TYPE_1__*) ; 
 int /*<<< orphan*/  SCRIPTCONTF_FIXED_FONT ; 
 int /*<<< orphan*/  SCRIPTCONTF_PROPORTIONAL_FONT ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  sidAsciiLatin ; 

__attribute__((used)) static void test_GetScriptFontInfo(IMLangFontLink2 *font_link)
{
    HRESULT hr;
    UINT nfonts;
    SCRIPTFONTINFO sfi[1];

    nfonts = 0;
    hr = IMLangFontLink2_GetScriptFontInfo(font_link, sidAsciiLatin, 0, &nfonts, NULL);
    ok(hr == S_OK, "GetScriptFontInfo failed %u\n", GetLastError());
    ok(nfonts, "unexpected result\n");

    nfonts = 0;
    hr = IMLangFontLink2_GetScriptFontInfo(font_link, sidAsciiLatin, SCRIPTCONTF_FIXED_FONT, &nfonts, NULL);
    ok(hr == S_OK, "GetScriptFontInfo failed %u\n", GetLastError());
    ok(nfonts, "unexpected result\n");

    nfonts = 0;
    hr = IMLangFontLink2_GetScriptFontInfo(font_link, sidAsciiLatin, SCRIPTCONTF_PROPORTIONAL_FONT, &nfonts, NULL);
    ok(hr == S_OK, "GetScriptFontInfo failed %u\n", GetLastError());
    ok(nfonts, "unexpected result\n");

    nfonts = 1;
    memset(sfi, 0, sizeof(sfi));
    hr = IMLangFontLink2_GetScriptFontInfo(font_link, sidAsciiLatin, SCRIPTCONTF_FIXED_FONT, &nfonts, sfi);
    ok(hr == S_OK, "GetScriptFontInfo failed %u\n", GetLastError());
    ok(nfonts == 1, "got %u, expected 1\n", nfonts);
    ok(sfi[0].scripts != 0, "unexpected result\n");
    ok(sfi[0].wszFont[0], "unexpected result\n");

    nfonts = 1;
    memset(sfi, 0, sizeof(sfi));
    hr = IMLangFontLink2_GetScriptFontInfo(font_link, sidAsciiLatin, SCRIPTCONTF_PROPORTIONAL_FONT, &nfonts, sfi);
    ok(hr == S_OK, "GetScriptFontInfo failed %u\n", GetLastError());
    ok(nfonts == 1, "got %u, expected 1\n", nfonts);
    ok(sfi[0].scripts != 0, "unexpected result\n");
    ok(sfi[0].wszFont[0], "unexpected result\n");
}