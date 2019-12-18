#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {char* Buffer; int Length; int MaximumLength; scalar_t__ result; int /*<<< orphan*/  base; int /*<<< orphan*/  value; } ;
typedef  TYPE_1__ int2str_t ;
typedef  char WCHAR ;
struct TYPE_10__ {int Length; int MaximumLength; char* Buffer; } ;
typedef  TYPE_2__ UNICODE_STRING ;
struct TYPE_11__ {scalar_t__ Buffer; } ;
typedef  TYPE_3__ STRING ;
typedef  scalar_t__ NTSTATUS ;

/* Variables and functions */
 scalar_t__ STATUS_BUFFER_OVERFLOW ; 
 scalar_t__ STATUS_SUCCESS ; 
 int STRI_BUFFER_LENGTH ; 
 scalar_t__ memcmp (char*,char*,int) ; 
 int /*<<< orphan*/  ok (int,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,...) ; 
 int /*<<< orphan*/  pRtlFreeAnsiString (TYPE_3__*) ; 
 scalar_t__ pRtlIntegerToUnicodeString (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  pRtlUnicodeStringToAnsiString (TYPE_3__*,TYPE_2__*,int) ; 

__attribute__((used)) static void one_RtlIntegerToUnicodeString_test(int test_num, const int2str_t *int2str)
{
    int pos;
    WCHAR expected_str_Buffer[STRI_BUFFER_LENGTH + 1];
    UNICODE_STRING expected_unicode_string;
    STRING expected_ansi_str;
    WCHAR str_Buffer[STRI_BUFFER_LENGTH + 1];
    UNICODE_STRING unicode_string;
    STRING ansi_str;
    NTSTATUS result;

    for (pos = 0; pos < STRI_BUFFER_LENGTH; pos++) {
	expected_str_Buffer[pos] = int2str->Buffer[pos];
    }
    expected_unicode_string.Length = int2str->Length * sizeof(WCHAR);
    expected_unicode_string.MaximumLength = int2str->MaximumLength * sizeof(WCHAR);
    expected_unicode_string.Buffer = expected_str_Buffer;
    pRtlUnicodeStringToAnsiString(&expected_ansi_str, &expected_unicode_string, 1);

    for (pos = 0; pos < STRI_BUFFER_LENGTH; pos++) {
	str_Buffer[pos] = '-';
    }
    unicode_string.Length = 0;
    unicode_string.MaximumLength = int2str->MaximumLength * sizeof(WCHAR);
    unicode_string.Buffer = str_Buffer;

    result = pRtlIntegerToUnicodeString(int2str->value, int2str->base, &unicode_string);
    pRtlUnicodeStringToAnsiString(&ansi_str, &unicode_string, 1);
    if (result == STATUS_BUFFER_OVERFLOW) {
	/* On BUFFER_OVERFLOW the string Buffer should be unchanged */
	for (pos = 0; pos < STRI_BUFFER_LENGTH; pos++) {
	    expected_str_Buffer[pos] = '-';
	}
	/* w2k: The native function has two reasons for BUFFER_OVERFLOW: */
	/* If the value is too large to convert: The Length is unchanged */
	/* If str is too small to hold the string: Set str->Length to the length */
	/* the string would have (which can be larger than the MaximumLength). */
	/* To allow all this in the tests we do the following: */
	if (expected_unicode_string.Length > 32 && unicode_string.Length == 0) {
	    /* The value is too large to convert only triggered when testing native */
	    expected_unicode_string.Length = 0;
	}
    } else {
	ok(result == int2str->result,
           "(test %d): RtlIntegerToUnicodeString(%u, %d, [out]) has result %x, expected: %x\n",
	   test_num, int2str->value, int2str->base, result, int2str->result);
	if (result == STATUS_SUCCESS) {
	    ok(unicode_string.Buffer[unicode_string.Length/sizeof(WCHAR)] == '\0',
               "(test %d): RtlIntegerToUnicodeString(%u, %d, [out]) string \"%s\" is not NULL terminated\n",
	       test_num, int2str->value, int2str->base, ansi_str.Buffer);
	}
    }
    ok(memcmp(unicode_string.Buffer, expected_unicode_string.Buffer, STRI_BUFFER_LENGTH * sizeof(WCHAR)) == 0,
       "(test %d): RtlIntegerToUnicodeString(%u, %d, [out]) assigns string \"%s\", expected: \"%s\"\n",
       test_num, int2str->value, int2str->base, ansi_str.Buffer, expected_ansi_str.Buffer);
    ok(unicode_string.Length == expected_unicode_string.Length,
       "(test %d): RtlIntegerToUnicodeString(%u, %d, [out]) string has Length %d, expected: %d\n",
       test_num, int2str->value, int2str->base, unicode_string.Length, expected_unicode_string.Length);
    ok(unicode_string.MaximumLength == expected_unicode_string.MaximumLength,
       "(test %d): RtlIntegerToUnicodeString(%u, %d, [out]) string has MaximumLength %d, expected: %d\n",
       test_num, int2str->value, int2str->base, unicode_string.MaximumLength, expected_unicode_string.MaximumLength);
    pRtlFreeAnsiString(&expected_ansi_str);
    pRtlFreeAnsiString(&ansi_str);
}