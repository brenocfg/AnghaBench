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
typedef  unsigned long long uint64_t ;
typedef  int /*<<< orphan*/  sa_attr_type_t ;

/* Variables and functions */
 unsigned long long SA_ATTR_HASH (int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint64_t
sa_layout_info_hash(sa_attr_type_t *attrs, int attr_count)
{
	int i;
	uint64_t crc = -1ULL;

	for (i = 0; i != attr_count; i++)
		crc ^= SA_ATTR_HASH(attrs[i]);

	return (crc);
}