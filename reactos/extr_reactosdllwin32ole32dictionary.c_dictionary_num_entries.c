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
struct dictionary {int /*<<< orphan*/  num_entries; } ;
typedef  int /*<<< orphan*/  UINT ;

/* Variables and functions */

UINT dictionary_num_entries(struct dictionary *d)
{
    return d ? d->num_entries : 0;
}