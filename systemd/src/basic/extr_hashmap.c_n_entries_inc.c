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
struct TYPE_4__ {int /*<<< orphan*/  n_entries; } ;
struct TYPE_5__ {int /*<<< orphan*/  n_direct_entries; TYPE_1__ indirect; scalar_t__ has_indirect; } ;
typedef  TYPE_2__ HashmapBase ;

/* Variables and functions */

__attribute__((used)) static void n_entries_inc(HashmapBase *h) {
        if (h->has_indirect)
                h->indirect.n_entries++;
        else
                h->n_direct_entries++;
}