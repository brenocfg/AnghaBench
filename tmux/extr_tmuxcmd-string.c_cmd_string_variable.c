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
struct environ_entry {char* value; } ;

/* Variables and functions */
#define  EOF 128 
 int /*<<< orphan*/  SIZE_MAX ; 
 int cmd_string_getc (char const*,size_t*) ; 
 int /*<<< orphan*/  cmd_string_ungetc (size_t*) ; 
 struct environ_entry* environ_find (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  global_environ ; 
 int /*<<< orphan*/  xasprintf (char**,char*,int) ; 
 char* xrealloc (char*,size_t) ; 
 char* xstrdup (char*) ; 

__attribute__((used)) static char *
cmd_string_variable(const char *s, size_t *p)
{
	int			ch, fch;
	char		       *buf, *t;
	size_t			len;
	struct environ_entry   *envent;

#define cmd_string_first(ch) ((ch) == '_' || \
	((ch) >= 'a' && (ch) <= 'z') || ((ch) >= 'A' && (ch) <= 'Z'))
#define cmd_string_other(ch) ((ch) == '_' || \
	((ch) >= 'a' && (ch) <= 'z') || ((ch) >= 'A' && (ch) <= 'Z') || \
	((ch) >= '0' && (ch) <= '9'))

	buf = NULL;
	len = 0;

	fch = EOF;
	switch (ch = cmd_string_getc(s, p)) {
	case EOF:
		goto error;
	case '{':
		fch = '{';

		ch = cmd_string_getc(s, p);
		if (!cmd_string_first(ch))
			goto error;
		/* FALLTHROUGH */
	default:
		if (!cmd_string_first(ch)) {
			xasprintf(&t, "$%c", ch);
			return (t);
		}

		buf = xrealloc(buf, len + 1);
		buf[len++] = ch;

		for (;;) {
			ch = cmd_string_getc(s, p);
			if (ch == EOF || !cmd_string_other(ch))
				break;
			else {
				if (len >= SIZE_MAX - 3)
					goto error;
				buf = xrealloc(buf, len + 1);
				buf[len++] = ch;
			}
		}
	}

	if (fch == '{' && ch != '}')
		goto error;
	if (ch != EOF && fch != '{')
		cmd_string_ungetc(p); /* ch */

	buf = xrealloc(buf, len + 1);
	buf[len] = '\0';

	envent = environ_find(global_environ, buf);
	free(buf);
	if (envent == NULL)
		return (xstrdup(""));
	return (xstrdup(envent->value));

error:
	free(buf);
	return (NULL);
}