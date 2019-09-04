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
typedef  char WCHAR ;
struct TYPE_4__ {int Length; int MaximumLength; char* Buffer; } ;
typedef  TYPE_1__ UNICODE_STRING ;

/* Variables and functions */
 int /*<<< orphan*/  ok (int,char*,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  pRtlUpcaseUnicodeString (TYPE_1__*,TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_RtlUpcaseUnicodeString(void)
{
    int i;
    WCHAR ch;
    WCHAR upper_ch;
    WCHAR ascii_buf[257];
    WCHAR result_buf[257];
    WCHAR upper_buf[257];
    UNICODE_STRING ascii_str;
    UNICODE_STRING result_str;
    UNICODE_STRING upper_str;

    for (i = 0; i <= 255; i++) {
	ch = (WCHAR) i;
	if (ch >= 'a' && ch <= 'z') {
	    upper_ch = ch - 'a' + 'A';
	} else if (ch >= 0xe0 && ch <= 0xfe && ch != 0xf7) {
	    upper_ch = ch - 0x20;
	} else if (ch == 0xff) {
	    upper_ch = 0x178;
	} else {
	    upper_ch = ch;
	}
	ascii_buf[i] = ch;
	result_buf[i] = '\0';
	upper_buf[i] = upper_ch;
    }
    ascii_buf[i] = '\0';
    result_buf[i] = '\0';
    upper_buf[i] = '\0';
    ascii_str.Length = 512;
    ascii_str.MaximumLength = 512;
    ascii_str.Buffer = ascii_buf;
    result_str.Length = 512;
    result_str.MaximumLength = 512;
    result_str.Buffer = result_buf;
    upper_str.Length = 512;
    upper_str.MaximumLength = 512;
    upper_str.Buffer = upper_buf;

    pRtlUpcaseUnicodeString(&result_str, &ascii_str, 0);
    for (i = 0; i <= 255; i++) {
	ok(result_str.Buffer[i] == upper_str.Buffer[i],
	   "RtlUpcaseUnicodeString works wrong: '%c'[=0x%x] is converted to '%c'[=0x%x], expected: '%c'[=0x%x]\n",
	   ascii_str.Buffer[i], ascii_str.Buffer[i],
	   result_str.Buffer[i], result_str.Buffer[i],
	   upper_str.Buffer[i], upper_str.Buffer[i]);
    }
}