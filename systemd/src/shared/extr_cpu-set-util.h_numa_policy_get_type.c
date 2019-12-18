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
struct TYPE_4__ {scalar_t__ set; } ;
struct TYPE_5__ {int type; TYPE_1__ nodes; } ;
typedef  TYPE_2__ NUMAPolicy ;

/* Variables and functions */
 int MPOL_PREFERRED ; 

__attribute__((used)) static inline int numa_policy_get_type(const NUMAPolicy *p) {
        return p->type < 0 ? (p->nodes.set ? MPOL_PREFERRED : -1) : p->type;
}