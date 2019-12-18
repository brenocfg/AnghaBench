#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {void* storage; } ;
struct TYPE_5__ {void* storage; } ;
struct TYPE_7__ {TYPE_2__ direct; TYPE_1__ indirect; scalar_t__ has_indirect; } ;
typedef  TYPE_3__ HashmapBase ;

/* Variables and functions */

__attribute__((used)) static void *storage_ptr(HashmapBase *h) {
        return h->has_indirect ? h->indirect.storage
                               : h->direct.storage;
}