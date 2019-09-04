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
struct target_dir_hash {int /*<<< orphan*/  root; } ;

/* Variables and functions */
 int /*<<< orphan*/  dir_hash_destroy_dir (struct target_dir_hash*,int /*<<< orphan*/ *) ; 

void dir_hash_destroy(struct target_dir_hash *dh)
{
    dir_hash_destroy_dir(dh, &dh->root);
}