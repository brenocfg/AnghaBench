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
typedef  size_t u_int ;
struct tty_term_code_entry {int type; int /*<<< orphan*/  name; } ;
struct tty_term {struct tty_code* codes; int /*<<< orphan*/  name; } ;
struct TYPE_2__ {char* string; int number; int flag; } ;
struct tty_code {int type; TYPE_1__ value; } ;

/* Variables and functions */
 int /*<<< orphan*/  INT_MAX ; 
#define  TTYCODE_FLAG 131 
#define  TTYCODE_NONE 130 
#define  TTYCODE_NUMBER 129 
#define  TTYCODE_STRING 128 
 scalar_t__ fnmatch (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  log_debug (char*,int /*<<< orphan*/ ,char*,...) ; 
 char* strchr (char*,char) ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ ) ; 
 int strlen (char*) ; 
 int strtonum (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const**) ; 
 int strunvis (char*,char*) ; 
 struct tty_term_code_entry* tty_term_codes ; 
 size_t tty_term_ncodes () ; 
 char* tty_term_override_next (char const*,size_t*) ; 
 void* xstrdup (char*) ; 

__attribute__((used)) static void
tty_term_override(struct tty_term *term, const char *override)
{
	const struct tty_term_code_entry	*ent;
	struct tty_code				*code;
	size_t                                   offset = 0;
	char					*cp, *value, *s;
	const char				*errstr;
	u_int					 i;
	int					 n, remove;

	s = tty_term_override_next(override, &offset);
	if (s == NULL || fnmatch(s, term->name, 0) != 0)
		return;

	while ((s = tty_term_override_next(override, &offset)) != NULL) {
		if (*s == '\0')
			continue;
		value = NULL;

		remove = 0;
		if ((cp = strchr(s, '=')) != NULL) {
			*cp++ = '\0';
			value = xstrdup(cp);
			if (strunvis(value, cp) == -1) {
				free(value);
				value = xstrdup(cp);
			}
		} else if (s[strlen(s) - 1] == '@') {
			s[strlen(s) - 1] = '\0';
			remove = 1;
		} else
			value = xstrdup("");

		if (remove)
			log_debug("%s override: %s@", term->name, s);
		else if (*value == '\0')
			log_debug("%s override: %s", term->name, s);
		else
			log_debug("%s override: %s=%s", term->name, s, value);

		for (i = 0; i < tty_term_ncodes(); i++) {
			ent = &tty_term_codes[i];
			if (strcmp(s, ent->name) != 0)
				continue;
			code = &term->codes[i];

			if (remove) {
				code->type = TTYCODE_NONE;
				continue;
			}
			switch (ent->type) {
			case TTYCODE_NONE:
				break;
			case TTYCODE_STRING:
				if (code->type == TTYCODE_STRING)
					free(code->value.string);
				code->value.string = xstrdup(value);
				code->type = ent->type;
				break;
			case TTYCODE_NUMBER:
				n = strtonum(value, 0, INT_MAX, &errstr);
				if (errstr != NULL)
					break;
				code->value.number = n;
				code->type = ent->type;
				break;
			case TTYCODE_FLAG:
				code->value.flag = 1;
				code->type = ent->type;
				break;
			}
		}

		free(value);
	}
}