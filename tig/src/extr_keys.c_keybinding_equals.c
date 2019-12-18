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
struct keybinding {size_t keys; } ;
struct key {int dummy; } ;

/* Variables and functions */
 int keybinding_matches (struct keybinding const*,struct key const*,size_t,int*) ; 

__attribute__((used)) static bool
keybinding_equals(const struct keybinding *keybinding, const struct key key[],
		  size_t keys, bool *conflict_ptr)
{
	if (keybinding->keys != keys)
		return false;
	return keybinding_matches(keybinding, key, keys, conflict_ptr);
}