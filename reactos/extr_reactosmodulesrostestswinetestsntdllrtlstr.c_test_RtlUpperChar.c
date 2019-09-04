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
typedef  int CHAR ;

/* Variables and functions */
 int /*<<< orphan*/  ok (int,char*,int,int,int,int,int,int) ; 
 int pRtlUpperChar (int) ; 

__attribute__((used)) static void test_RtlUpperChar(void)
{
    int ch;
    int upper_ch;
    int expected_upper_ch;
    int byte_ch;

    for (ch = -1; ch <= 1024; ch++) {
	upper_ch = pRtlUpperChar(ch);
	byte_ch = ch & 0xff;
	if (byte_ch >= 'a' && byte_ch <= 'z') {
	    expected_upper_ch = (CHAR) (byte_ch - 'a' + 'A');
	} else {
	    expected_upper_ch = (CHAR) byte_ch;
	}
	ok(upper_ch == expected_upper_ch,
	   "RtlUpperChar('%c'[=0x%x]) has result '%c'[=0x%x], expected '%c'[=0x%x]\n",
	   ch, ch, upper_ch, upper_ch, expected_upper_ch, expected_upper_ch);
    }
}