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
struct TYPE_3__ {int /*<<< orphan*/  barriers; } ;
typedef  TYPE_1__ Barrier ;

/* Variables and functions */
 int /*<<< orphan*/  BARRIER_THEY_ABORTED ; 
 int /*<<< orphan*/  BARRIER_WE_ABORTED ; 
 int IN_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool barrier_they_aborted(Barrier *b) {
        return IN_SET(b->barriers, BARRIER_THEY_ABORTED, BARRIER_WE_ABORTED);
}