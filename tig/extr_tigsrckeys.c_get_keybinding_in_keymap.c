#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct keymap {size_t size; TYPE_1__** data; } ;
struct key {int dummy; } ;
typedef  enum request { ____Placeholder_request } request ;
struct TYPE_2__ {scalar_t__ request; size_t keys; } ;

/* Variables and functions */
 scalar_t__ REQ_NONE ; 
 int REQ_UNKNOWN ; 
 scalar_t__ keybinding_matches (TYPE_1__*,struct key const*,size_t,int /*<<< orphan*/ *) ; 

__attribute__((used)) static enum request
get_keybinding_in_keymap(const struct keymap *keymap, const struct key key[], size_t keys, int *matches)
{
	enum request request = REQ_UNKNOWN;
	size_t i;

	for (i = 0; i < keymap->size; i++)
		if (keybinding_matches(keymap->data[i], key, keys, NULL)) {
			if (matches && keymap->data[i]->request != REQ_NONE)
				(*matches)++;
			/* Overriding keybindings, might have been added
			 * at the end of the keymap so we need to
			 * iterate all keybindings. */
			if (keymap->data[i]->keys == keys)
				request = keymap->data[i]->request;
		}

	return request;
}