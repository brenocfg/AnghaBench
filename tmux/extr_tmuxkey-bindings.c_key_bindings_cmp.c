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
struct key_binding {scalar_t__ key; } ;

/* Variables and functions */

__attribute__((used)) static int
key_bindings_cmp(struct key_binding *bd1, struct key_binding *bd2)
{
	if (bd1->key < bd2->key)
		return (-1);
	if (bd1->key > bd2->key)
		return (1);
	return (0);
}