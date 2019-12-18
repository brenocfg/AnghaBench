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
typedef  int /*<<< orphan*/  iostat_cbdata_t ;

/* Variables and functions */
 int /*<<< orphan*/  print_iostat_dashes (int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
print_iostat_separator_impl(iostat_cbdata_t *cb,
    unsigned int force_column_width)
{
	print_iostat_dashes(cb, force_column_width, NULL);
}