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
struct TYPE_4__ {int Length; int MaximumLength; char* Buffer; } ;
typedef  TYPE_1__ STRING ;
typedef  char CHAR ;

/* Variables and functions */
 scalar_t__ memcmp (char*,char*,int) ; 
 int /*<<< orphan*/  ok (int,char*) ; 
 int /*<<< orphan*/  pRtlUpperString (TYPE_1__*,TYPE_1__*) ; 

__attribute__((used)) static void test_RtlUpperString(void)
{
    int i;
    CHAR ch;
    CHAR upper_ch;
    char ascii_buf[257];
    char result_buf[257];
    char upper_buf[257];
    STRING ascii_str;
    STRING result_str;
    STRING upper_str;

    for (i = 0; i <= 255; i++) {
	ch = (CHAR) i;
	if (ch >= 'a' && ch <= 'z') {
	    upper_ch = ch - 'a' + 'A';
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
    ascii_str.Length = 256;
    ascii_str.MaximumLength = 256;
    ascii_str.Buffer = ascii_buf;
    result_str.Length = 256;
    result_str.MaximumLength = 256;
    result_str.Buffer = result_buf;
    upper_str.Length = 256;
    upper_str.MaximumLength = 256;
    upper_str.Buffer = upper_buf;

    pRtlUpperString(&result_str, &ascii_str);
    ok(memcmp(result_str.Buffer, upper_str.Buffer, 256) == 0,
       "RtlUpperString does not work as expected\n");
}