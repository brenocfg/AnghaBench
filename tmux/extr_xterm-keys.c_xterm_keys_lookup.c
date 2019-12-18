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
typedef  size_t u_int ;
struct xterm_keys_entry {int key; int /*<<< orphan*/  template; } ;
typedef  int key_code ;

/* Variables and functions */
 int KEYC_CTRL ; 
 int KEYC_ESCAPE ; 
 int KEYC_MASK_KEY ; 
 int KEYC_SHIFT ; 
 int KEYC_XTERM ; 
 size_t nitems (struct xterm_keys_entry*) ; 
 size_t strcspn (char*,char*) ; 
 char* xstrdup (int /*<<< orphan*/ ) ; 
 struct xterm_keys_entry* xterm_keys_table ; 

char *
xterm_keys_lookup(key_code key)
{
	const struct xterm_keys_entry	*entry;
	u_int				 i;
	key_code			 modifiers;
	char				*out;

	modifiers = 1;
	if (key & KEYC_SHIFT)
		modifiers += 1;
	if (key & KEYC_ESCAPE)
		modifiers += 2;
	if (key & KEYC_CTRL)
		modifiers += 4;

	/*
	 * If the key has no modifiers, return NULL and let it fall through to
	 * the normal lookup.
	 */
	if (modifiers == 1)
		return (NULL);

	/*
	 * If this has the escape modifier, but was not originally an xterm
	 * key, it may be a genuine escape + key. So don't pass it through as
	 * an xterm key or programs like vi may be confused.
	 */
	if ((key & (KEYC_ESCAPE|KEYC_XTERM)) == KEYC_ESCAPE)
		return (NULL);

	/* Otherwise, find the key in the table. */
	key &= KEYC_MASK_KEY;
	for (i = 0; i < nitems(xterm_keys_table); i++) {
		entry = &xterm_keys_table[i];
		if (key == entry->key)
			break;
	}
	if (i == nitems(xterm_keys_table))
		return (NULL);

	/* Copy the template and replace the modifier. */
	out = xstrdup(entry->template);
	out[strcspn(out, "_")] = '0' + modifiers;
	return (out);
}