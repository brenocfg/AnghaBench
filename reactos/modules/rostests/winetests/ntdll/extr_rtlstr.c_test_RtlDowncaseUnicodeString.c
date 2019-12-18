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
 int /*<<< orphan*/  pRtlDowncaseUnicodeString (TYPE_1__*,TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_RtlDowncaseUnicodeString(void)
{
    int i;
    WCHAR ch;
    WCHAR lower_ch;
    WCHAR source_buf[1025];
    WCHAR result_buf[1025];
    WCHAR lower_buf[1025];
    UNICODE_STRING source_str;
    UNICODE_STRING result_str;
    UNICODE_STRING lower_str;

    for (i = 0; i < 1024; i++) {
	ch = (WCHAR) i;
	if (ch >= 'A' && ch <= 'Z') {
	    lower_ch = ch - 'A' + 'a';
	} else if (ch >= 0xc0 && ch <= 0xde && ch != 0xd7) {
	    lower_ch = ch + 0x20;
	} else if (ch >= 0x391 && ch <= 0x3ab && ch != 0x3a2) {
	    lower_ch = ch + 0x20;
	} else {
	    switch (ch) {
		case 0x178: lower_ch = 0xff; break;
		case 0x181: lower_ch = 0x253; break;
		case 0x186: lower_ch = 0x254; break;
		case 0x189: lower_ch = 0x256; break;
		case 0x18a: lower_ch = 0x257; break;
		case 0x18e: lower_ch = 0x1dd; break;
		case 0x18f: lower_ch = 0x259; break;
		case 0x190: lower_ch = 0x25b; break;
		case 0x193: lower_ch = 0x260; break;
		case 0x194: lower_ch = 0x263; break;
		case 0x196: lower_ch = 0x269; break;
		case 0x197: lower_ch = 0x268; break;
		case 0x19c: lower_ch = 0x26f; break;
		case 0x19d: lower_ch = 0x272; break;
		case 0x19f: lower_ch = 0x275; break;
		case 0x1a9: lower_ch = 0x283; break;
		case 0x1ae: lower_ch = 0x288; break;
		case 0x1b1: lower_ch = 0x28a; break;
		case 0x1b2: lower_ch = 0x28b; break;
		case 0x1b7: lower_ch = 0x292; break;
		case 0x1c4: lower_ch = 0x1c6; break;
		case 0x1c7: lower_ch = 0x1c9; break;
		case 0x1ca: lower_ch = 0x1cc; break;
		case 0x1f1: lower_ch = 0x1f3; break;
		case 0x386: lower_ch = 0x3ac; break;
		case 0x388: lower_ch = 0x3ad; break;
		case 0x389: lower_ch = 0x3ae; break;
		case 0x38a: lower_ch = 0x3af; break;
		case 0x38c: lower_ch = 0x3cc; break;
		case 0x38e: lower_ch = 0x3cd; break;
		case 0x38f: lower_ch = 0x3ce; break;
		default: lower_ch = ch; break;
	    } /* switch */
	}
	source_buf[i] = ch;
	result_buf[i] = '\0';
	lower_buf[i] = lower_ch;
    }
    source_buf[i] = '\0';
    result_buf[i] = '\0';
    lower_buf[i] = '\0';
    source_str.Length = 2048;
    source_str.MaximumLength = 2048;
    source_str.Buffer = source_buf;
    result_str.Length = 2048;
    result_str.MaximumLength = 2048;
    result_str.Buffer = result_buf;
    lower_str.Length = 2048;
    lower_str.MaximumLength = 2048;
    lower_str.Buffer = lower_buf;

    pRtlDowncaseUnicodeString(&result_str, &source_str, 0);
    for (i = 0; i <= 1024; i++) {
	ok(result_str.Buffer[i] == lower_str.Buffer[i] || result_str.Buffer[i] == source_str.Buffer[i] + 1,
	   "RtlDowncaseUnicodeString works wrong: '%c'[=0x%x] is converted to '%c'[=0x%x], expected: '%c'[=0x%x]\n",
	   source_str.Buffer[i], source_str.Buffer[i],
	   result_str.Buffer[i], result_str.Buffer[i],
	   lower_str.Buffer[i], lower_str.Buffer[i]);
    }
}