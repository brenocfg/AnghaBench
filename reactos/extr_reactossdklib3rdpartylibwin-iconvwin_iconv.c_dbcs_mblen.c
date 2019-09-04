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
typedef  int /*<<< orphan*/  uchar ;
struct TYPE_3__ {int /*<<< orphan*/  codepage; } ;
typedef  TYPE_1__ csconv_t ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 scalar_t__ IsDBCSLeadByteEx (int /*<<< orphan*/ ,int /*<<< orphan*/  const) ; 
 int seterror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
dbcs_mblen(csconv_t *cv, const uchar *buf, int bufsize)
{
    int len = IsDBCSLeadByteEx(cv->codepage, buf[0]) ? 2 : 1;
    if (bufsize < len)
        return seterror(EINVAL);
    return len;
}