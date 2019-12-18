#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct filter_level {int /*<<< orphan*/  Range; int /*<<< orphan*/  level; } ;

/* Variables and functions */
 int /*<<< orphan*/  StoreLevel (struct filter_level*,int /*<<< orphan*/ *,float) ; 
 int /*<<< orphan*/  atomic_store (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void SetLevel(struct filter_level *range, float val)
{
    atomic_store( &range->level, StoreLevel( range, &range->Range, val ) );
}