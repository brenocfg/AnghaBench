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
typedef  int /*<<< orphan*/  bufW ;
typedef  int /*<<< orphan*/  bufA ;
typedef  char WCHAR ;
typedef  size_t UINT ;
typedef  char* LPCWSTR ;
typedef  char* LPCSTR ;
typedef  int /*<<< orphan*/  INT ;
typedef  int /*<<< orphan*/  IMultiLanguage2 ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 size_t ARRAY_SIZE (char*) ; 
 int CP_UNICODE ; 
 int /*<<< orphan*/  E_FAIL ; 
 int /*<<< orphan*/  IMultiLanguage2_ConvertStringFromUnicode (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,char*,size_t*,char*,size_t*) ; 
 int /*<<< orphan*/  IMultiLanguage2_ConvertStringToUnicode (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,char*,size_t*,char*,size_t*) ; 
 size_t MultiByteToWideChar (int,int /*<<< orphan*/ ,char*,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_OK ; 
 size_t WideCharToMultiByte (int,int /*<<< orphan*/ ,char*,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lstrcmpA (char*,char*) ; 
 int /*<<< orphan*/  lstrcmpW (char*,char*) ; 
 int lstrlenA (char*) ; 
 size_t lstrlenW (char*) ; 
 int /*<<< orphan*/  memcmp (char*,char*,int) ; 
 int /*<<< orphan*/  memset (char*,char,int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  pConvertINetMultiByteToUnicode (int /*<<< orphan*/ *,int,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void test_multibyte_to_unicode_translations(IMultiLanguage2 *iML2)
{
    /* these APIs are broken regarding constness of the input buffer */
    char stringA[] = "Just a test string\0"; /* double 0 for CP_UNICODE tests */
    WCHAR stringW[] = {'J','u','s','t',' ','a',' ','t','e','s','t',' ','s','t','r','i','n','g',0};
    char bufA[256];
    WCHAR bufW[256];
    UINT lenA, lenW, expected_len;
    HRESULT ret;

    /* IMultiLanguage2_ConvertStringToUnicode tests */

    memset(bufW, 'x', sizeof(bufW));
    lenA = 0;
    lenW = ARRAY_SIZE(bufW);
    ret = IMultiLanguage2_ConvertStringToUnicode(iML2, NULL, 1252, stringA, &lenA, bufW, &lenW);
    ok(ret == S_OK, "IMultiLanguage2_ConvertStringToUnicode failed: %08x\n", ret);
    ok(lenA == 0, "expected lenA 0, got %u\n", lenA);
    ok(lenW == 0, "expected lenW 0, got %u\n", lenW);

    memset(bufW, 'x', sizeof(bufW));
    lenA = -1;
    lenW = ARRAY_SIZE(bufW);
    ret = IMultiLanguage2_ConvertStringToUnicode(iML2, NULL, 1252, stringA, &lenA, bufW, &lenW);
    ok(ret == S_OK, "IMultiLanguage2_ConvertStringToUnicode failed: %08x\n", ret);
    ok(lenA == lstrlenA(stringA), "expected lenA %u, got %u\n", lstrlenA(stringA), lenA);
    ok(lenW == lstrlenW(stringW), "expected lenW %u, got %u\n", lstrlenW(stringW), lenW);
    if (lenW < ARRAY_SIZE(bufW)) {
       /* can only happen if the convert call fails */
       ok(bufW[lenW] != 0, "buf should not be 0 terminated\n");
       bufW[lenW] = 0; /* -1 doesn't include 0 terminator */
    }
    ok(!lstrcmpW(bufW, stringW), "bufW/stringW mismatch\n");

    memset(bufW, 'x', sizeof(bufW));
    lenA = -1;
    lenW = 5;
    ret = IMultiLanguage2_ConvertStringToUnicode(iML2, NULL, 1252, stringA, &lenA, bufW, &lenW);
    ok(ret == E_FAIL, "IMultiLanguage2_ConvertStringToUnicode should fail: %08x\n", ret);
    ok(lenW == 0, "expected lenW 0, got %u\n", lenW);
    /* still has to do partial conversion */
    ok(!memcmp(bufW, stringW, 5 * sizeof(WCHAR)), "bufW/stringW mismatch\n");

    memset(bufW, 'x', sizeof(bufW));
    lenA = -1;
    lenW = ARRAY_SIZE(bufW);
    ret = IMultiLanguage2_ConvertStringToUnicode(iML2, NULL, CP_UNICODE, stringA, &lenA, bufW, &lenW);
    ok(ret == S_OK, "IMultiLanguage2_ConvertStringToUnicode failed: %08x\n", ret);
    ok(lenA == lstrlenA(stringA), "expected lenA %u, got %u\n", lstrlenA(stringA), lenA);
    ok(lenW == lstrlenW(stringW)/(int)sizeof(WCHAR), "wrong lenW %u\n", lenW);
    ok(bufW[lenW] != 0, "buf should not be 0 terminated\n");
    bufW[lenW] = 0; /* -1 doesn't include 0 terminator */
    ok(!lstrcmpA((LPCSTR)bufW, stringA), "bufW/stringA mismatch\n");

    memset(bufW, 'x', sizeof(bufW));
    lenA = lstrlenA(stringA);
    lenW = 0;
    ret = IMultiLanguage2_ConvertStringToUnicode(iML2, NULL, 1252, stringA, &lenA, NULL, &lenW);
    ok(ret == S_OK, "IMultiLanguage2_ConvertStringToUnicode failed: %08x\n", ret);
    ok(lenA == lstrlenA(stringA), "expected lenA %u, got %u\n", lstrlenA(stringA), lenA);
    expected_len = MultiByteToWideChar(1252, 0, stringA, lenA, NULL, 0);
    ok(lenW == expected_len, "expected lenW %u, got %u\n", expected_len, lenW);

    memset(bufW, 'x', sizeof(bufW));
    lenA = lstrlenA(stringA);
    lenW = ARRAY_SIZE(bufW);
    ret = pConvertINetMultiByteToUnicode(NULL, 1252, stringA, (INT *)&lenA, NULL, (INT *)&lenW);
    ok(ret == S_OK, "ConvertINetMultiByteToUnicode failed: %08x\n", ret);
    ok(lenA == lstrlenA(stringA), "expected lenA %u, got %u\n", lstrlenA(stringA), lenA);
    expected_len = MultiByteToWideChar(1252, 0, stringA, lenA, NULL, 0);
    ok(lenW == expected_len, "expected lenW %u, got %u\n", expected_len, lenW);

    memset(bufW, 'x', sizeof(bufW));
    lenA = lstrlenA(stringA);
    lenW = 0;
    ret = pConvertINetMultiByteToUnicode(NULL, 1252, stringA, (INT *)&lenA, NULL, (INT *)&lenW);
    ok(ret == S_OK, "ConvertINetMultiByteToUnicode failed: %08x\n", ret);
    ok(lenA == lstrlenA(stringA), "expected lenA %u, got %u\n", lstrlenA(stringA), lenA);
    expected_len = MultiByteToWideChar(1252, 0, stringA, lenA, NULL, 0);
    ok(lenW == expected_len, "expected lenW %u, got %u\n", expected_len, lenW);

    /* IMultiLanguage2_ConvertStringFromUnicode tests */

    memset(bufA, 'x', sizeof(bufA));
    lenW = 0;
    lenA = sizeof(bufA);
    ret = IMultiLanguage2_ConvertStringFromUnicode(iML2, NULL, 1252, stringW, &lenW, bufA, &lenA);
    ok(ret == S_OK, "IMultiLanguage2_ConvertStringFromUnicode failed: %08x\n", ret);
    ok(lenA == 0, "expected lenA 0, got %u\n", lenA);
    ok(lenW == 0, "expected lenW 0, got %u\n", lenW);

    memset(bufA, 'x', sizeof(bufA));
    lenW = -1;
    lenA = sizeof(bufA);
    ret = IMultiLanguage2_ConvertStringFromUnicode(iML2, NULL, 1252, stringW, &lenW, bufA, &lenA);
    ok(ret == S_OK, "IMultiLanguage2_ConvertStringFromUnicode failed: %08x\n", ret);
    ok(lenA == lstrlenA(stringA), "expected lenA %u, got %u\n", lstrlenA(stringA), lenA);
    ok(lenW == lstrlenW(stringW), "expected lenW %u, got %u\n", lstrlenW(stringW), lenW);
    ok(bufA[lenA] != 0, "buf should not be 0 terminated\n");
    bufA[lenA] = 0; /* -1 doesn't include 0 terminator */
    ok(!lstrcmpA(bufA, stringA), "bufA/stringA mismatch\n");

    memset(bufA, 'x', sizeof(bufA));
    lenW = -1;
    lenA = 5;
    ret = IMultiLanguage2_ConvertStringFromUnicode(iML2, NULL, 1252, stringW, &lenW, bufA, &lenA);
    ok(ret == E_FAIL, "IMultiLanguage2_ConvertStringFromUnicode should fail: %08x\n", ret);
    ok(lenA == 0, "expected lenA 0, got %u\n", lenA);
    /* still has to do partial conversion */
    ok(!memcmp(bufA, stringA, 5), "bufW/stringW mismatch\n");

    memset(bufA, 'x', sizeof(bufA));
    lenW = -1;
    lenA = sizeof(bufA);
    ret = IMultiLanguage2_ConvertStringFromUnicode(iML2, NULL, CP_UNICODE, stringW, &lenW, bufA, &lenA);
    ok(ret == S_OK, "IMultiLanguage2_ConvertStringFromUnicode failed: %08x\n", ret);
    ok(lenA == lstrlenA(stringA) * (int)sizeof(WCHAR), "wrong lenA %u\n", lenA);
    ok(lenW == lstrlenW(stringW), "expected lenW %u, got %u\n", lstrlenW(stringW), lenW);
    ok(bufA[lenA] != 0 && bufA[lenA+1] != 0, "buf should not be 0 terminated\n");
    bufA[lenA] = 0; /* -1 doesn't include 0 terminator */
    bufA[lenA+1] = 0; /* sizeof(WCHAR) */
    ok(!lstrcmpW((LPCWSTR)bufA, stringW), "bufA/stringW mismatch\n");

    memset(bufA, 'x', sizeof(bufA));
    lenW = lstrlenW(stringW);
    lenA = 0;
    ret = IMultiLanguage2_ConvertStringFromUnicode(iML2, NULL, 1252, stringW, &lenW, NULL, &lenA);
    ok(ret == S_OK, "IMultiLanguage2_ConvertStringFromUnicode failed: %08x\n", ret);
    ok(lenW == lstrlenW(stringW), "expected lenW %u, got %u\n", lstrlenW(stringW), lenW);
    expected_len = WideCharToMultiByte(1252, 0, stringW, lenW, NULL, 0, NULL, NULL);
    ok(lenA == expected_len, "expected lenA %u, got %u\n", expected_len, lenA);
}