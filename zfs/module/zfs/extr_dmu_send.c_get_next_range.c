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
struct send_range {int dummy; } ;
typedef  int /*<<< orphan*/  bqueue_t ;

/* Variables and functions */
 struct send_range* get_next_range_nofree (int /*<<< orphan*/ *,struct send_range*) ; 
 int /*<<< orphan*/  range_free (struct send_range*) ; 

__attribute__((used)) static struct send_range *
get_next_range(bqueue_t *bq, struct send_range *prev)
{
	struct send_range *next = get_next_range_nofree(bq, prev);
	range_free(prev);
	return (next);
}