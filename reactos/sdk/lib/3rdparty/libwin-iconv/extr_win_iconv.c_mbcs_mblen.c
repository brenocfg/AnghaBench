#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uchar ;
struct TYPE_3__ {int codepage; } ;
typedef  TYPE_1__ csconv_t ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int seterror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mbcs_mblen(csconv_t *cv, const uchar *buf, int bufsize)
{
    int len = 0;

    if (cv->codepage == 54936) {
	if (buf[0] <= 0x7F) len = 1;
	else if (buf[0] >= 0x81 && buf[0] <= 0xFE &&
		 bufsize >= 2 &&
		 ((buf[1] >= 0x40 && buf[1] <= 0x7E) ||
		  (buf[1] >= 0x80 && buf[1] <= 0xFE))) len = 2;
	else if (buf[0] >= 0x81 && buf[0] <= 0xFE &&
		 bufsize >= 4 &&
		 buf[1] >= 0x30 && buf[1] <= 0x39) len = 4;
	else
	    return seterror(EINVAL);
	return len;
    }
    else
	return seterror(EINVAL);
}