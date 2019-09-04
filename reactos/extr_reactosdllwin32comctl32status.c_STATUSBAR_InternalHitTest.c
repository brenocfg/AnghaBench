#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ x; } ;
struct TYPE_9__ {unsigned int numParts; TYPE_2__* parts; scalar_t__ simple; } ;
struct TYPE_7__ {scalar_t__ left; scalar_t__ right; } ;
struct TYPE_8__ {TYPE_1__ bound; } ;
typedef  TYPE_3__ STATUS_INFO ;
typedef  TYPE_4__ POINT ;

/* Variables and functions */

__attribute__((used)) static int
STATUSBAR_InternalHitTest(const STATUS_INFO *infoPtr, const POINT *pt)
{
    unsigned int i;

    if (infoPtr->simple)
        return 255;

    for (i = 0; i < infoPtr->numParts; i++)
        if (pt->x >= infoPtr->parts[i].bound.left && pt->x <= infoPtr->parts[i].bound.right)
            return i;
    return -2;
}