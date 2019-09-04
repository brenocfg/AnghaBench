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
struct keybinding {int /*<<< orphan*/  keys; int /*<<< orphan*/  key; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUFSIZ ; 
 char* get_key_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int string_nformat (char*,int /*<<< orphan*/ ,size_t*,char*,char const*,char const*) ; 

__attribute__((used)) static bool
append_key(char *buf, size_t *pos, const struct keybinding *keybinding, bool all)
{
	const char *sep = *pos > 0 ? ", " : "";
	const char *keyname = get_key_name(keybinding->key, keybinding->keys, all);

	return string_nformat(buf, BUFSIZ, pos, "%s%s", sep, keyname);
}