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
struct tty_key {int /*<<< orphan*/  key; } ;
struct tty {int /*<<< orphan*/  key_tree; } ;
typedef  int /*<<< orphan*/  key_code ;

/* Variables and functions */
 char* key_string_lookup_key (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_debug (char*,char const*,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 int /*<<< orphan*/  tty_keys_add1 (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 struct tty_key* tty_keys_find (struct tty*,char const*,int /*<<< orphan*/ ,size_t*) ; 

__attribute__((used)) static void
tty_keys_add(struct tty *tty, const char *s, key_code key)
{
	struct tty_key	*tk;
	size_t		 size;
	const char     	*keystr;

	keystr = key_string_lookup_key(key);
	if ((tk = tty_keys_find(tty, s, strlen(s), &size)) == NULL) {
		log_debug("new key %s: 0x%llx (%s)", s, key, keystr);
		tty_keys_add1(&tty->key_tree, s, key);
	} else {
		log_debug("replacing key %s: 0x%llx (%s)", s, key, keystr);
		tk->key = key;
	}
}