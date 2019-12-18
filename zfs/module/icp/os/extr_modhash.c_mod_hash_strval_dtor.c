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
typedef  scalar_t__ mod_hash_val_t ;

/* Variables and functions */
 int /*<<< orphan*/  kmem_free (char*,scalar_t__) ; 
 scalar_t__ strlen (char*) ; 

void
mod_hash_strval_dtor(mod_hash_val_t val)
{
	char *c = (char *)val;
	kmem_free(c, strlen(c) + 1);
}