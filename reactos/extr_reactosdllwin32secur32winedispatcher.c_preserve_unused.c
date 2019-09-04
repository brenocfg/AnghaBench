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
struct TYPE_3__ {int com_buf_offset; scalar_t__ com_buf; } ;
typedef  int /*<<< orphan*/  SECURITY_STATUS ;
typedef  TYPE_1__* PNegoHelper ;

/* Variables and functions */
 int /*<<< orphan*/  SEC_E_OK ; 
 int /*<<< orphan*/  TRACE (char*,int) ; 
 int /*<<< orphan*/  memmove (scalar_t__,scalar_t__,int) ; 

__attribute__((used)) static SECURITY_STATUS preserve_unused(PNegoHelper helper, int offset_len)
{
    TRACE("offset_len = %d\n", offset_len);

    if(offset_len > 0)
    {
        memmove(helper->com_buf, helper->com_buf + helper->com_buf_offset, 
                offset_len);
        helper->com_buf_offset = offset_len;
    }
    else
    {
        helper->com_buf_offset = 0;
    }

    TRACE("helper->com_buf_offset was set to: %d\n", helper->com_buf_offset);
    return SEC_E_OK;
}