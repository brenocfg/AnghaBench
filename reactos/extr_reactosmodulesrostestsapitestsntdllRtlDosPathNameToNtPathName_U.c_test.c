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
typedef  int /*<<< orphan*/ * LPCWSTR ;

/* Variables and functions */
 int /*<<< orphan*/  swprintf (int /*<<< orphan*/ *,char*,char const*) ; 
 int /*<<< orphan*/  test2 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void test(const char* psz, const char* pszExpected, const char* pszExpectedPartName)
{
	WCHAR wszTmp1[512];
	WCHAR wszTmp2[512];
	WCHAR wszTmp3[512];
	LPCWSTR p2 = 0;
	LPCWSTR p3 = 0;
	swprintf(wszTmp1, L"%S", psz);
	if (pszExpected) {
		swprintf(wszTmp2, L"%S", pszExpected);
		p2 = wszTmp2;
	}
	if (pszExpectedPartName) {
		swprintf(wszTmp3, L"%S", pszExpectedPartName);
		p3 = wszTmp3;
	}
	test2(wszTmp1, p2, p3);
}