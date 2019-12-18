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
struct TYPE_4__ {int Length; char* Buffer; } ;
typedef  TYPE_1__ UNICODE_STRING ;
typedef  int /*<<< orphan*/  RTL_RELATIVE_NAME_U ;
typedef  char* PWSTR ;
typedef  int /*<<< orphan*/  PCWSTR ;
typedef  char* LPCWSTR ;
typedef  int BOOLEAN ;

/* Variables and functions */
 int FALSE ; 
 int RtlDosPathNameToNtPathName_U (char*,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  check_result (int,char*) ; 
 scalar_t__ memcmp (char*,char*,size_t const) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  prucs (char*,TYPE_1__*) ; 
 scalar_t__ wcscmp (char*,char*) ; 
 size_t const wcslen (char*) ; 

__attribute__((used)) static void test2(LPCWSTR pwsz, LPCWSTR pwszExpected, LPCWSTR pwszExpectedPartName)
{
    UNICODE_STRING      NtName;
    PWSTR               PartName;
    RTL_RELATIVE_NAME_U RelativeName;
	BOOLEAN             bOK;

	bOK = RtlDosPathNameToNtPathName_U(pwsz, &NtName, (PCWSTR*)&PartName, &RelativeName);

	check_result(bOK, "RtlDosPathNameToNtPathName_U failed");
	if (!bOK) {
		printf("input: \"%S\"\n", pwsz);
		return;
	}

#if !defined(COMPILE_AS_ROSTEST) && defined(PRINT_INFO)
	printf("--------------------------\n");
	printf("in          : \"%S\"\n", pwsz);
	prucs("NtName", &NtName);
	printf("PartName    : \"%S\"\n", PartName ? PartName : L"(null)");
//	prucs("RelativeName", &RelativeName.RelativeName);
#endif

	// Disregarding input, output (NtName) shall always start with "\??\".
	bOK = NtName.Length >= 8 &&
	      memcmp(NtName.Buffer, L"\\??\\", 8) == 0;
	check_result(bOK, "NtName does not start with \"\\??\\\"");
	if (!bOK) {
		return;
	}

	if (pwszExpected) {
		PWSTR pwszActual = NtName.Buffer + 4;
		const size_t lenExp = wcslen(pwszExpected);
		const size_t lenAct = (NtName.Length - 8) / 2;
		bOK = (lenExp == lenAct) &&
		      memcmp(pwszActual, pwszExpected, lenExp * 2) == 0;
		check_result(bOK, "NtName does not match expected");
		if (!bOK)
		{
			printf("input:  : %2Iu chars \"%S\"\n", wcslen(pwsz), pwsz);
			printf("Expected: %2Iu chars \"%S\"\n", lenExp, pwszExpected);
			printf("Actual  : %2Iu chars \"%S\"\n", lenAct, lenAct ? pwszActual : L"(null)");
			return;
		}
	} else
	if (NtName.Length)
	{
		PWSTR pwszActual = NtName.Buffer + 4;
		const size_t lenAct = (NtName.Length - 8) / 2;
		check_result(FALSE, "Unexpected NtName (expected NULL)");
		printf("input:  : %2Iu chars \"%S\"\n", wcslen(pwsz), pwsz);
		printf("Actual  : %2Iu chars \"%S\"\n", lenAct, pwszActual);
	}

	if (pwszExpectedPartName) {
		const size_t lenExp = wcslen(pwszExpectedPartName);
		const size_t lenAct = PartName ? wcslen(PartName) : 0;
		bOK = (lenExp == lenAct) &&
		      wcscmp(PartName, pwszExpectedPartName) == 0;
		check_result(bOK, "PartName does not match expected");
		if (!bOK) {
			printf("input:  : %2Iu chars \"%S\"\n", wcslen(pwsz), pwsz);
			printf("Expected: %2Iu chars \"%S\"\n", lenExp, pwszExpectedPartName);
			printf("Actual  : %2Iu chars \"%S\"\n", lenAct, lenAct ? PartName : L"(null)");
			return;
		}
	} else
	if (PartName)
	{
		check_result(FALSE, "Unexpected PartName (expected NULL).");
		printf("input:  : %2Iu chars \"%S\"\n", wcslen(pwsz), pwsz);
		printf("Actual  : %2Iu chars %S\n", wcslen(PartName), PartName);
	}
}