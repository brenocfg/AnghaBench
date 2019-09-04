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
typedef  int /*<<< orphan*/  wchar_t ;
struct utf8_data {size_t size; int /*<<< orphan*/  data; } ;

/* Variables and functions */
#define  EOF 128 
 int SIZE_MAX ; 
 int /*<<< orphan*/  UTF8_DONE ; 
 int /*<<< orphan*/  cmd_string_copy (char**,char*,size_t*) ; 
 int cmd_string_getc (char const*,size_t*) ; 
 int /*<<< orphan*/  cmd_string_unicode (int /*<<< orphan*/ *,char const*,size_t*,int) ; 
 char* cmd_string_variable (char const*,size_t*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  utf8_split (int /*<<< orphan*/ ,struct utf8_data*) ; 
 char* xrealloc (char*,size_t) ; 

__attribute__((used)) static char *
cmd_string_string(const char *s, size_t *p, char endch, int esc)
{
	int			ch;
	wchar_t			wc;
	struct utf8_data	ud;
	char		       *buf = NULL, *t;
	size_t			len = 0;

	while ((ch = cmd_string_getc(s, p)) != endch) {
		switch (ch) {
		case EOF:
			goto error;
		case '\\':
			if (!esc)
				break;
			switch (ch = cmd_string_getc(s, p)) {
			case EOF:
				goto error;
			case 'e':
				ch = '\033';
				break;
			case 'r':
				ch = '\r';
				break;
			case 'n':
				ch = '\n';
				break;
			case 't':
				ch = '\t';
				break;
			case 'u':
			case 'U':
				if (cmd_string_unicode(&wc, s, p, ch) != 0)
					goto error;
				if (utf8_split(wc, &ud) != UTF8_DONE)
					goto error;
				if (len >= SIZE_MAX - ud.size - 1)
					goto error;
				buf = xrealloc(buf, len + ud.size);
				memcpy(buf + len, ud.data, ud.size);
				len += ud.size;
				continue;
			}
			break;
		case '$':
			if (!esc)
				break;
			if ((t = cmd_string_variable(s, p)) == NULL)
				goto error;
			cmd_string_copy(&buf, t, &len);
			continue;
		}

		if (len >= SIZE_MAX - 2)
			goto error;
		buf = xrealloc(buf, len + 1);
		buf[len++] = ch;
	}

	buf = xrealloc(buf, len + 1);
	buf[len] = '\0';
	return (buf);

error:
	free(buf);
	return (NULL);
}