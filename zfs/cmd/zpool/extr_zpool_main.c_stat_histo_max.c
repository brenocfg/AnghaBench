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
typedef  int /*<<< orphan*/  uint64_t ;
struct stat_array {int /*<<< orphan*/  count; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAX (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  array64_max (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint64_t
stat_histo_max(struct stat_array *nva, unsigned int len)
{
	uint64_t max = 0;
	int i;
	for (i = 0; i < len; i++)
		max = MAX(max, array64_max(nva[i].data, nva[i].count));

	return (max);
}