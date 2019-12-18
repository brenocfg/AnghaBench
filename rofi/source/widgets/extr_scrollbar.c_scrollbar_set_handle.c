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
struct TYPE_3__ {int /*<<< orphan*/  length; int /*<<< orphan*/  pos; } ;
typedef  TYPE_1__ scrollbar ;

/* Variables and functions */
 int /*<<< orphan*/  MIN (int /*<<< orphan*/ ,unsigned int) ; 

void scrollbar_set_handle ( scrollbar *sb, unsigned int pos )
{
    if ( sb != NULL ) {
        sb->pos = MIN ( sb->length, pos );
    }
}