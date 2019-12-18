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
struct TYPE_3__ {int zh_hdr_size; int zh_stats_size; int zh_stats_count; int zh_ds_size; int zh_ds_count; scalar_t__ zh_size; scalar_t__ zh_opts_size; } ;
typedef  TYPE_1__ ztest_shared_hdr_t ;

/* Variables and functions */

__attribute__((used)) static int
shared_data_size(ztest_shared_hdr_t *hdr)
{
	int size;

	size = hdr->zh_hdr_size;
	size += hdr->zh_opts_size;
	size += hdr->zh_size;
	size += hdr->zh_stats_size * hdr->zh_stats_count;
	size += hdr->zh_ds_size * hdr->zh_ds_count;

	return (size);
}