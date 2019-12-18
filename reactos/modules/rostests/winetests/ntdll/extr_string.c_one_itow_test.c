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
struct TYPE_8__ {char* Buffer; int value; int /*<<< orphan*/  base; } ;
typedef  TYPE_1__ ulong2str_t ;
typedef  char WCHAR ;
struct TYPE_9__ {int Length; int MaximumLength; char* Buffer; } ;
typedef  TYPE_2__ UNICODE_STRING ;
struct TYPE_10__ {char* Buffer; } ;
typedef  TYPE_3__ STRING ;
typedef  char* LPWSTR ;

/* Variables and functions */
 int LARGE_STRI_BUFFER_LENGTH ; 
 scalar_t__ memcmp (char*,char*,int) ; 
 int /*<<< orphan*/  ok (int,char*,int,int,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  pRtlFreeAnsiString (TYPE_3__*) ; 
 int /*<<< orphan*/  pRtlUnicodeStringToAnsiString (TYPE_3__*,TYPE_2__*,int) ; 
 char* p_itow (int,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void one_itow_test(int test_num, const ulong2str_t *ulong2str)
{
    int pos;
    WCHAR expected_wstr[LARGE_STRI_BUFFER_LENGTH + 1];
    WCHAR dest_wstr[LARGE_STRI_BUFFER_LENGTH + 1];
    UNICODE_STRING unicode_string;
    STRING ansi_str;
    int value;
    LPWSTR result;

    for (pos = 0; pos < LARGE_STRI_BUFFER_LENGTH; pos++) {
	expected_wstr[pos] = ulong2str->Buffer[pos];
    } /* for */
    expected_wstr[LARGE_STRI_BUFFER_LENGTH] = '\0';

    for (pos = 0; pos < LARGE_STRI_BUFFER_LENGTH; pos++) {
	dest_wstr[pos] = '-';
    } /* for */
    dest_wstr[LARGE_STRI_BUFFER_LENGTH] = '\0';
    unicode_string.Length = LARGE_STRI_BUFFER_LENGTH * sizeof(WCHAR);
    unicode_string.MaximumLength = unicode_string.Length + sizeof(WCHAR);
    unicode_string.Buffer = dest_wstr;
    value = ulong2str->value;
    result = p_itow(value, dest_wstr, ulong2str->base);
    pRtlUnicodeStringToAnsiString(&ansi_str, &unicode_string, 1);
    ok(result == dest_wstr,
       "(test %d): _itow(%d, [out], %d) has result %p, expected: %p\n",
       test_num, value, ulong2str->base, result, dest_wstr);
    ok(memcmp(dest_wstr, expected_wstr, LARGE_STRI_BUFFER_LENGTH * sizeof(WCHAR)) == 0,
       "(test %d): _itow(%d, [out], %d) assigns string \"%s\", expected: \"%s\"\n",
       test_num, value, ulong2str->base, ansi_str.Buffer, ulong2str->Buffer);
    pRtlFreeAnsiString(&ansi_str);
}