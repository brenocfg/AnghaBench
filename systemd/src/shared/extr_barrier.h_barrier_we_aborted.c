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
struct TYPE_3__ {scalar_t__ barriers; } ;
typedef  TYPE_1__ Barrier ;

/* Variables and functions */
 scalar_t__ BARRIER_WE_ABORTED ; 

__attribute__((used)) static inline bool barrier_we_aborted(Barrier *b) {
        return b->barriers == BARRIER_WE_ABORTED;
}