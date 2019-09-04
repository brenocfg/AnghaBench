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
typedef  TYPE_1__* xmlBufPtr ;
struct TYPE_4__ {scalar_t__ error; } ;

/* Variables and functions */
 size_t xmlBufGrowInternal (TYPE_1__*,int) ; 

int
xmlBufGrow(xmlBufPtr buf, int len) {
    size_t ret;

    if ((buf == NULL) || (len < 0)) return(-1);
    if (len == 0)
        return(0);
    ret = xmlBufGrowInternal(buf, len);
    if (buf->error != 0)
        return(-1);
    return((int) ret);
}