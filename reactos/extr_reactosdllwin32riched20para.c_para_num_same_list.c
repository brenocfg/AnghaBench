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
struct TYPE_4__ {scalar_t__ wNumbering; scalar_t__ wNumberingStart; int wNumberingStyle; } ;
typedef  TYPE_1__ PARAFORMAT2 ;
typedef  int BOOL ;

/* Variables and functions */
 int PFNS_NEWNUMBER ; 

__attribute__((used)) static inline BOOL para_num_same_list( const PARAFORMAT2 *item, const PARAFORMAT2 *base )
{
    return item->wNumbering == base->wNumbering &&
        item->wNumberingStart == base->wNumberingStart &&
        item->wNumberingStyle == base->wNumberingStyle &&
        !(item->wNumberingStyle & PFNS_NEWNUMBER);
}