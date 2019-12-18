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
typedef  long wchar_t ;
struct utf8_data {scalar_t__ size; } ;
struct cmdq_item {int dummy; } ;
struct cmd_find_state {int dummy; } ;
struct client {int dummy; } ;
struct args {char** argv; } ;
typedef  long key_code ;

/* Variables and functions */
 long KEYC_LITERAL ; 
 long KEYC_NONE ; 
 long KEYC_UNKNOWN ; 
 scalar_t__ UTF8_DONE ; 
 int args_has (struct args*,char) ; 
 struct cmdq_item* cmd_send_keys_inject_key (struct client*,struct cmd_find_state*,struct cmdq_item*,long) ; 
 int /*<<< orphan*/  free (struct utf8_data*) ; 
 long key_string_lookup_string (char const*) ; 
 long strtol (char const*,char**,int) ; 
 scalar_t__ utf8_combine (struct utf8_data*,long*) ; 
 struct utf8_data* utf8_fromcstr (char const*) ; 

__attribute__((used)) static struct cmdq_item *
cmd_send_keys_inject_string(struct client *c, struct cmd_find_state *fs,
    struct cmdq_item *item, struct args *args, int i)
{
	const char		*s = args->argv[i];
	struct utf8_data	*ud, *uc;
	wchar_t			 wc;
	key_code		 key;
	char			*endptr;
	long			 n;
	int			 literal;

	if (args_has(args, 'H')) {
		n = strtol(s, &endptr, 16);
		if (*s =='\0' || n < 0 || n > 0xff || *endptr != '\0')
			return (item);
		return (cmd_send_keys_inject_key(c, fs, item, KEYC_LITERAL|n));
	}

	literal = args_has(args, 'l');
	if (!literal) {
		key = key_string_lookup_string(s);
		if (key != KEYC_NONE && key != KEYC_UNKNOWN)
			return (cmd_send_keys_inject_key(c, fs, item, key));
		literal = 1;
	}
	if (literal) {
		ud = utf8_fromcstr(s);
		for (uc = ud; uc->size != 0; uc++) {
			if (utf8_combine(uc, &wc) != UTF8_DONE)
				continue;
			item = cmd_send_keys_inject_key(c, fs, item, wc);
		}
		free(ud);
	}
	return (item);
}