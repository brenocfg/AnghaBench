#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {size_t numParts; TYPE_1__* parts; } ;
struct TYPE_4__ {size_t x; } ;
typedef  TYPE_2__ STATUS_INFO ;
typedef  size_t INT ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE (char*,size_t) ; 

__attribute__((used)) static INT
STATUSBAR_GetParts (const STATUS_INFO *infoPtr, INT num_parts, INT parts[])
{
    INT   i;

    TRACE("(%d)\n", num_parts);
    if (parts) {
	for (i = 0; i < num_parts; i++) {
	    parts[i] = infoPtr->parts[i].x;
	}
    }
    return infoPtr->numParts;
}