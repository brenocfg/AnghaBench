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
struct TYPE_4__ {void* ndisc_dnssl; void* ndisc_rdnss; } ;
typedef  TYPE_1__ Link ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 void* set_free_free (void*) ; 

void ndisc_flush(Link *link) {
        assert(link);

        /* Removes all RDNSS and DNSSL entries, without exception */

        link->ndisc_rdnss = set_free_free(link->ndisc_rdnss);
        link->ndisc_dnssl = set_free_free(link->ndisc_dnssl);
}