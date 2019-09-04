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
struct keymap {size_t size; struct keybinding** data; } ;
struct keybinding {int request; size_t keys; int /*<<< orphan*/  key; } ;
struct key {int dummy; } ;
typedef  enum status_code { ____Placeholder_status_code } status_code ;
typedef  enum request { ____Placeholder_request } request ;

/* Variables and functions */
 int SIZEOF_STR ; 
 int SUCCESS ; 
 struct keybinding* calloc (int,int) ; 
 int /*<<< orphan*/  die (char*) ; 
 int error (char*,char*,char*) ; 
 char* get_request_name (int) ; 
 scalar_t__ keybinding_equals (struct keybinding*,struct key const*,size_t,int*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,struct key const*,int) ; 
 struct keybinding** realloc (struct keybinding**,int) ; 
 int /*<<< orphan*/  string_ncopy (char*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

enum status_code
add_keybinding(struct keymap *table, enum request request,
	       const struct key key[], size_t keys)
{
	struct keybinding *keybinding;
	char buf[SIZEOF_STR];
	bool conflict = false;
	size_t i;

	for (i = 0; i < table->size; i++) {
		if (keybinding_equals(table->data[i], key, keys, &conflict)) {
			enum request old_request = table->data[i]->request;
			const char *old_name;

			table->data[i]->request = request;
			if (!conflict)
				return SUCCESS;

			old_name = get_request_name(old_request);
			string_ncopy(buf, old_name, strlen(old_name));
			return error("Key binding for %s and %s conflict; "
				     "keys using Ctrl are case insensitive",
				     buf, get_request_name(request));
		}
	}

	table->data = realloc(table->data, (table->size + 1) * sizeof(*table->data));
	keybinding = calloc(1, sizeof(*keybinding) + (sizeof(*key) * (keys - 1)));
	if (!table->data || !keybinding)
		die("Failed to allocate keybinding");

	memcpy(keybinding->key, key, sizeof(*key) * keys);
	keybinding->keys = keys;
	keybinding->request = request;
	table->data[table->size++] = keybinding;
	return SUCCESS;
}