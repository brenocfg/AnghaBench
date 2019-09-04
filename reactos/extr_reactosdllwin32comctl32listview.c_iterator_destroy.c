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
struct TYPE_3__ {int /*<<< orphan*/  ranges; } ;
typedef  TYPE_1__ ITERATOR ;

/* Variables and functions */
 int /*<<< orphan*/  ranges_destroy (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void iterator_destroy(const ITERATOR *i)
{
    ranges_destroy(i->ranges);
}