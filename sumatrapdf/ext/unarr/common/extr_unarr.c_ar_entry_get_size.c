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
struct TYPE_3__ {size_t entry_size_uncompressed; } ;
typedef  TYPE_1__ ar_archive ;

/* Variables and functions */

size_t ar_entry_get_size(ar_archive *ar)
{
    return ar->entry_size_uncompressed;
}