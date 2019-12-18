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
struct TYPE_3__ {int lcid; char* broken_rfc; int /*<<< orphan*/  rfc1766; int /*<<< orphan*/  hr; scalar_t__ broken_lcid; } ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  size_t DWORD ;
typedef  char CHAR ;

/* Variables and functions */
 size_t ARRAY_SIZE (TYPE_1__*) ; 
 int /*<<< orphan*/  E_FAIL ; 
 int /*<<< orphan*/  E_INVALIDARG ; 
 int LANG_ENGLISH ; 
 int /*<<< orphan*/  LCMAP_LOWERCASE ; 
 int /*<<< orphan*/  LCMapStringA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,char*,int) ; 
 int /*<<< orphan*/  LOCALE_USER_DEFAULT ; 
 int MAX_RFC1766_NAME ; 
 int /*<<< orphan*/  S_OK ; 
 scalar_t__ broken (int) ; 
 TYPE_1__* lcid_table ; 
 int /*<<< orphan*/  lstrcmpA (char*,char*) ; 
 scalar_t__ lstrlenA (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (char*,char,int) ; 
 int /*<<< orphan*/  ok (int,char*,size_t,...) ; 
 int /*<<< orphan*/  pLcidToRfc1766A (int,char*,int) ; 

__attribute__((used)) static void test_LcidToRfc1766(void)
{
    CHAR expected[MAX_RFC1766_NAME];
    CHAR buffer[MAX_RFC1766_NAME * 2];
    HRESULT hr;
    DWORD i;

    for(i = 0; i < ARRAY_SIZE(lcid_table); i++) {

        memset(buffer, '#', sizeof(buffer)-1);
        buffer[sizeof(buffer)-1] = '\0';

        hr = pLcidToRfc1766A(lcid_table[i].lcid, buffer, MAX_RFC1766_NAME);

        /* IE <5.0 does not recognize 0x180c (fr-mc) and 0x457 (kok) */
        ok( (hr == lcid_table[i].hr) ||
            broken(lcid_table[i].broken_lcid && (hr == E_FAIL)),
            "#%02d: HRESULT 0x%x (expected 0x%x)\n", i, hr, lcid_table[i].hr);

        if (hr != S_OK)
            continue;

        LCMapStringA(LOCALE_USER_DEFAULT, LCMAP_LOWERCASE, lcid_table[i].rfc1766,
                    lstrlenA(lcid_table[i].rfc1766) + 1, expected, MAX_RFC1766_NAME);

        /* IE <6.0 return "x-kok" for LCID 0x457 ("kok") */
        /* IE <5.0 return "fr" for LCID 0x180c ("fr-mc") */
        ok( (!lstrcmpA(buffer, expected)) ||
            broken(!lstrcmpA(buffer, lcid_table[i].broken_rfc)),
            "#%02d: got '%s' (expected '%s')\n", i, buffer, expected);

    }

    memset(buffer, '#', sizeof(buffer)-1);
    buffer[sizeof(buffer)-1] = '\0';
    hr = pLcidToRfc1766A(-1, buffer, MAX_RFC1766_NAME);
    ok(hr == E_FAIL, "got 0x%08x and '%s' (expected E_FAIL)\n", hr, buffer);

    hr = pLcidToRfc1766A(LANG_ENGLISH, NULL, MAX_RFC1766_NAME);
    ok(hr == E_INVALIDARG, "got 0x%08x (expected E_INVALIDARG)\n", hr);

    memset(buffer, '#', sizeof(buffer)-1);
    buffer[sizeof(buffer)-1] = '\0';
    hr = pLcidToRfc1766A(LANG_ENGLISH, buffer, -1);
    ok(hr == E_INVALIDARG, "got 0x%08x and '%s' (expected E_INVALIDARG)\n", hr, buffer);

    memset(buffer, '#', sizeof(buffer)-1);
    buffer[sizeof(buffer)-1] = '\0';
    hr = pLcidToRfc1766A(LANG_ENGLISH, buffer, 0);
    ok(hr == E_INVALIDARG, "got 0x%08x and '%s' (expected E_INVALIDARG)\n", hr, buffer);
}