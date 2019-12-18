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
union options_value {char const* string; } ;
typedef  size_t u_int ;
struct tty_default_key_raw {char* string; scalar_t__ key; int /*<<< orphan*/  code; } ;
struct tty_default_key_code {char* string; scalar_t__ key; int /*<<< orphan*/  code; } ;
struct tty {int /*<<< orphan*/  term; int /*<<< orphan*/ * key_tree; } ;
struct options_entry {int dummy; } ;
struct options_array_item {int dummy; } ;

/* Variables and functions */
 scalar_t__ KEYC_USER ; 
 int /*<<< orphan*/  global_options ; 
 size_t nitems (struct tty_default_key_raw*) ; 
 struct options_array_item* options_array_first (struct options_entry*) ; 
 size_t options_array_item_index (struct options_array_item*) ; 
 union options_value* options_array_item_value (struct options_array_item*) ; 
 struct options_array_item* options_array_next (struct options_array_item*) ; 
 struct options_entry* options_get (int /*<<< orphan*/ ,char*) ; 
 struct tty_default_key_raw* tty_default_code_keys ; 
 struct tty_default_key_raw* tty_default_raw_keys ; 
 int /*<<< orphan*/  tty_keys_add (struct tty*,char const*,scalar_t__) ; 
 int /*<<< orphan*/  tty_keys_free (struct tty*) ; 
 char* tty_term_string (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
tty_keys_build(struct tty *tty)
{
	const struct tty_default_key_raw	*tdkr;
	const struct tty_default_key_code	*tdkc;
	u_int		 			 i;
	const char				*s;
	struct options_entry			*o;
	struct options_array_item		*a;
	union options_value			*ov;

	if (tty->key_tree != NULL)
		tty_keys_free(tty);
	tty->key_tree = NULL;

	for (i = 0; i < nitems(tty_default_raw_keys); i++) {
		tdkr = &tty_default_raw_keys[i];

		s = tdkr->string;
		if (*s != '\0')
			tty_keys_add(tty, s, tdkr->key);
	}
	for (i = 0; i < nitems(tty_default_code_keys); i++) {
		tdkc = &tty_default_code_keys[i];

		s = tty_term_string(tty->term, tdkc->code);
		if (*s != '\0')
			tty_keys_add(tty, s, tdkc->key);

	}

	o = options_get(global_options, "user-keys");
	if (o != NULL) {
		a = options_array_first(o);
		while (a != NULL) {
			i = options_array_item_index(a);
			ov = options_array_item_value(a);
			tty_keys_add(tty, ov->string, KEYC_USER + i);
			a = options_array_next(a);
		}
	}
}