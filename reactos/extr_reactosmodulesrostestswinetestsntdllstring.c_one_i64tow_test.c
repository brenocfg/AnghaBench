#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {char* Buffer; int mask; int /*<<< orphan*/  base; int /*<<< orphan*/  value; } ;
typedef  TYPE_1__ ulonglong2str_t ;
typedef  char WCHAR ;
struct TYPE_9__ {int Length; int MaximumLength; char* Buffer; } ;
typedef  TYPE_2__ UNICODE_STRING ;
struct TYPE_10__ {char* Buffer; } ;
typedef  TYPE_3__ STRING ;
typedef  char* LPWSTR ;

/* Variables and functions */
 int LARGE_STRI_BUFFER_LENGTH ; 
 scalar_t__ memcmp (char*,char*,int) ; 
 int /*<<< orphan*/  ok (int,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  pRtlFreeAnsiString (TYPE_3__*) ; 
 int /*<<< orphan*/  pRtlUnicodeStringToAnsiString (TYPE_3__*,TYPE_2__*,int) ; 
 char* p_i64tow (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wine_dbgstr_longlong (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void one_i64tow_test(int test_num, const ulonglong2str_t *ulonglong2str)
{
    int pos;
    WCHAR expected_wstr[LARGE_STRI_BUFFER_LENGTH + 1];
    WCHAR dest_wstr[LARGE_STRI_BUFFER_LENGTH + 1];
    UNICODE_STRING unicode_string;
    STRING ansi_str;
    LPWSTR result;

    for (pos = 0; pos < LARGE_STRI_BUFFER_LENGTH; pos++) {
	expected_wstr[pos] = ulonglong2str->Buffer[pos];
    } /* for */
    expected_wstr[LARGE_STRI_BUFFER_LENGTH] = '\0';

    for (pos = 0; pos < LARGE_STRI_BUFFER_LENGTH; pos++) {
	dest_wstr[pos] = '-';
    } /* for */
    dest_wstr[LARGE_STRI_BUFFER_LENGTH] = '\0';
    unicode_string.Length = LARGE_STRI_BUFFER_LENGTH * sizeof(WCHAR);
    unicode_string.MaximumLength = unicode_string.Length + sizeof(WCHAR);
    unicode_string.Buffer = dest_wstr;

    result = p_i64tow(ulonglong2str->value, dest_wstr, ulonglong2str->base);
    pRtlUnicodeStringToAnsiString(&ansi_str, &unicode_string, 1);
    ok(result == dest_wstr,
       "(test %d): _i64tow(0x%s, [out], %d) has result %p, expected: %p\n",
       test_num, wine_dbgstr_longlong(ulonglong2str->value), ulonglong2str->base, result, dest_wstr);
    if (ulonglong2str->mask & 0x04) {
	if (memcmp(dest_wstr, expected_wstr, LARGE_STRI_BUFFER_LENGTH * sizeof(WCHAR)) != 0) {
	    for (pos = 0; pos < LARGE_STRI_BUFFER_LENGTH; pos++) {
		expected_wstr[pos] = ulonglong2str[1].Buffer[pos];
	    } /* for */
	    expected_wstr[LARGE_STRI_BUFFER_LENGTH] = '\0';
	    if (memcmp(dest_wstr, expected_wstr, LARGE_STRI_BUFFER_LENGTH * sizeof(WCHAR)) != 0) {
		ok(memcmp(dest_wstr, expected_wstr, LARGE_STRI_BUFFER_LENGTH * sizeof(WCHAR)) == 0,
                   "(test %d): _i64tow(0x%s, [out], %d) assigns string \"%s\", expected: \"%s\"\n",
		   test_num, wine_dbgstr_longlong(ulonglong2str->value),
		   ulonglong2str->base, ansi_str.Buffer, ulonglong2str->Buffer);
	    } /* if */
	} /* if */
    } else {
	ok(memcmp(dest_wstr, expected_wstr, LARGE_STRI_BUFFER_LENGTH * sizeof(WCHAR)) == 0,
           "(test %d): _i64tow(0x%s, [out], %d) assigns string \"%s\", expected: \"%s\"\n",
	   test_num, wine_dbgstr_longlong(ulonglong2str->value),
	   ulonglong2str->base, ansi_str.Buffer, ulonglong2str->Buffer);
    } /* if */
    pRtlFreeAnsiString(&ansi_str);
}