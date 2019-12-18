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
struct TYPE_9__ {int value; char* Buffer; int Length; int MaximumLength; int base; scalar_t__ result; } ;
typedef  TYPE_1__ largeint2str_t ;
typedef  char WCHAR ;
struct TYPE_10__ {int Length; int MaximumLength; char* Buffer; } ;
typedef  TYPE_2__ UNICODE_STRING ;
struct TYPE_11__ {int /*<<< orphan*/  Buffer; } ;
typedef  TYPE_3__ STRING ;
typedef  scalar_t__ NTSTATUS ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int LARGE_STRI_BUFFER_LENGTH ; 
 scalar_t__ STATUS_BUFFER_OVERFLOW ; 
 scalar_t__ STATUS_SUCCESS ; 
 scalar_t__ memcmp (char*,char*,int) ; 
 int /*<<< orphan*/  ok (int,char*,int,int /*<<< orphan*/ ,int,scalar_t__,...) ; 
 int /*<<< orphan*/  pRtlFreeAnsiString (TYPE_3__*) ; 
 scalar_t__ pRtlInt64ToUnicodeString (int,int,TYPE_2__*) ; 
 int /*<<< orphan*/  pRtlUnicodeStringToAnsiString (TYPE_3__*,TYPE_2__*,int) ; 
 int /*<<< orphan*/  skip (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wine_dbgstr_longlong (int) ; 

__attribute__((used)) static void one_RtlInt64ToUnicodeString_test(int test_num, const largeint2str_t *largeint2str)
{
    int pos;
    WCHAR expected_str_Buffer[LARGE_STRI_BUFFER_LENGTH + 1];
    UNICODE_STRING expected_unicode_string;
    STRING expected_ansi_str;
    WCHAR str_Buffer[LARGE_STRI_BUFFER_LENGTH + 1];
    UNICODE_STRING unicode_string;
    STRING ansi_str;
    NTSTATUS result;

#ifdef _WIN64
    if (largeint2str->value >> 32 == 0xffffffff)  /* this crashes on 64-bit Vista */
    {
        skip( "Value ffffffff%08x broken on 64-bit windows\n", (DWORD)largeint2str->value );
        return;
    }
#endif

    for (pos = 0; pos < LARGE_STRI_BUFFER_LENGTH; pos++) {
	expected_str_Buffer[pos] = largeint2str->Buffer[pos];
    } /* for */
    expected_unicode_string.Length = largeint2str->Length * sizeof(WCHAR);
    expected_unicode_string.MaximumLength = largeint2str->MaximumLength * sizeof(WCHAR);
    expected_unicode_string.Buffer = expected_str_Buffer;
    pRtlUnicodeStringToAnsiString(&expected_ansi_str, &expected_unicode_string, 1);

    for (pos = 0; pos < LARGE_STRI_BUFFER_LENGTH; pos++) {
	str_Buffer[pos] = '-';
    } /* for */
    unicode_string.Length = 0;
    unicode_string.MaximumLength = largeint2str->MaximumLength * sizeof(WCHAR);
    unicode_string.Buffer = str_Buffer;

    if (largeint2str->base == 0) {
	result = pRtlInt64ToUnicodeString(largeint2str->value, 10, &unicode_string);
    } else {
	result = pRtlInt64ToUnicodeString(largeint2str->value, largeint2str->base, &unicode_string);
    } /* if */
    pRtlUnicodeStringToAnsiString(&ansi_str, &unicode_string, 1);
    if (result == STATUS_BUFFER_OVERFLOW) {
	/* On BUFFER_OVERFLOW the string Buffer should be unchanged */
	for (pos = 0; pos < LARGE_STRI_BUFFER_LENGTH; pos++) {
	    expected_str_Buffer[pos] = '-';
	} /* for */
	/* w2k: The native function has two reasons for BUFFER_OVERFLOW: */
	/* If the value is too large to convert: The Length is unchanged */
	/* If str is too small to hold the string: Set str->Length to the length */
	/* the string would have (which can be larger than the MaximumLength). */
	/* To allow all this in the tests we do the following: */
	if (expected_unicode_string.Length >= 64) {
	    /* The value is too large to convert only triggered when testing native */
	    /* Length is not filled with the expected string length (garbage?) */
	    expected_unicode_string.Length = unicode_string.Length;
	} /* if */
    } else {
	ok(result == largeint2str->result,
           "(test %d): RtlInt64ToUnicodeString(0x%s, %d, [out]) has result %x, expected: %x\n",
	   test_num, wine_dbgstr_longlong(largeint2str->value), largeint2str->base, result, largeint2str->result);
	if (result == STATUS_SUCCESS) {
	    ok(unicode_string.Buffer[unicode_string.Length/sizeof(WCHAR)] == '\0',
               "(test %d): RtlInt64ToUnicodeString(0x%s, %d, [out]) string \"%s\" is not NULL terminated\n",
	       test_num, wine_dbgstr_longlong(largeint2str->value), largeint2str->base, ansi_str.Buffer);
	} /* if */
    } /* if */
    ok(memcmp(unicode_string.Buffer, expected_unicode_string.Buffer, LARGE_STRI_BUFFER_LENGTH * sizeof(WCHAR)) == 0,
       "(test %d): RtlInt64ToUnicodeString(0x%x%08x, %d, [out]) assigns string \"%s\", expected: \"%s\"\n",
       test_num, (DWORD)(largeint2str->value >>32), (DWORD)largeint2str->value, largeint2str->base, 
       ansi_str.Buffer, expected_ansi_str.Buffer);
    ok(unicode_string.Length == expected_unicode_string.Length,
       "(test %d): RtlInt64ToUnicodeString(0x%s, %d, [out]) string has Length %d, expected: %d\n",
       test_num, wine_dbgstr_longlong(largeint2str->value), largeint2str->base,
       unicode_string.Length, expected_unicode_string.Length);
    ok(unicode_string.MaximumLength == expected_unicode_string.MaximumLength,
       "(test %d): RtlInt64ToUnicodeString(0x%s, %d, [out]) string has MaximumLength %d, expected: %d\n",
       test_num, wine_dbgstr_longlong(largeint2str->value), largeint2str->base,
       unicode_string.MaximumLength, expected_unicode_string.MaximumLength);
    pRtlFreeAnsiString(&expected_ansi_str);
    pRtlFreeAnsiString(&ansi_str);
}