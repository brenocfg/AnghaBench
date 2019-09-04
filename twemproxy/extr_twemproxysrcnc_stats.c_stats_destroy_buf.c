#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ size; int /*<<< orphan*/ * data; } ;
struct stats {TYPE_1__ buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nc_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
stats_destroy_buf(struct stats *st)
{
    if (st->buf.size != 0) {
        ASSERT(st->buf.data != NULL);
        nc_free(st->buf.data);
        st->buf.size = 0;
    }
}