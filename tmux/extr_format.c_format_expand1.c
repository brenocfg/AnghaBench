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
typedef  int u_char ;
struct tm {int dummy; } ;
struct format_tree {scalar_t__ loop; int flags; int /*<<< orphan*/  time; } ;

/* Variables and functions */
 scalar_t__ FORMAT_LOOP_LIMIT ; 
 int FORMAT_NOJOBS ; 
 char* format_job_get (struct format_tree*,char*) ; 
 int /*<<< orphan*/  format_log (struct format_tree*,char*,...) ; 
 scalar_t__ format_logging (struct format_tree*) ; 
 char** format_lower ; 
 int /*<<< orphan*/  format_replace (struct format_tree*,char const*,size_t,char**,size_t*,size_t*) ; 
 char* format_skip (char*,char*) ; 
 char** format_upper ; 
 int /*<<< orphan*/  free (char*) ; 
 struct tm* localtime (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (char*,char*,size_t) ; 
 scalar_t__ strcmp (char*,char const*) ; 
 scalar_t__ strftime (char*,int,char const*,struct tm*) ; 
 size_t strlen (char const*) ; 
 char* xmalloc (size_t) ; 
 char* xreallocarray (char*,int,size_t) ; 
 char* xstrdup (char*) ; 
 char* xstrndup (char const*,size_t) ; 

__attribute__((used)) static char *
format_expand1(struct format_tree *ft, const char *fmt, int time)
{
	char		*buf, *out, *name;
	const char	*ptr, *s;
	size_t		 off, len, n, outlen;
	int     	 ch, brackets;
	struct tm	*tm;
	char		 expanded[8192];

	if (fmt == NULL || *fmt == '\0')
		return (xstrdup(""));

	if (ft->loop == FORMAT_LOOP_LIMIT)
		return (xstrdup(""));
	ft->loop++;

	format_log(ft, "expanding format: %s", fmt);

	if (time) {
		tm = localtime(&ft->time);
		if (strftime(expanded, sizeof expanded, fmt, tm) == 0) {
			format_log(ft, "format is too long");
			return (xstrdup(""));
		}
		if (format_logging(ft) && strcmp(expanded, fmt) != 0)
			format_log(ft, "after time expanded: %s", expanded);
		fmt = expanded;
	}

	len = 64;
	buf = xmalloc(len);
	off = 0;

	while (*fmt != '\0') {
		if (*fmt != '#') {
			while (len - off < 2) {
				buf = xreallocarray(buf, 2, len);
				len *= 2;
			}
			buf[off++] = *fmt++;
			continue;
		}
		fmt++;

		ch = (u_char)*fmt++;
		switch (ch) {
		case '(':
			brackets = 1;
			for (ptr = fmt; *ptr != '\0'; ptr++) {
				if (*ptr == '(')
					brackets++;
				if (*ptr == ')' && --brackets == 0)
					break;
			}
			if (*ptr != ')' || brackets != 0)
				break;
			n = ptr - fmt;

			name = xstrndup(fmt, n);
			format_log(ft, "found #(): %s", name);

			if (ft->flags & FORMAT_NOJOBS) {
				out = xstrdup("");
				format_log(ft, "#() is disabled");
			} else {
				out = format_job_get(ft, name);
				format_log(ft, "#() result: %s", out);
			}
			free(name);

			outlen = strlen(out);
			while (len - off < outlen + 1) {
				buf = xreallocarray(buf, 2, len);
				len *= 2;
			}
			memcpy(buf + off, out, outlen);
			off += outlen;

			free(out);

			fmt += n + 1;
			continue;
		case '{':
			ptr = format_skip((char *)fmt - 2, "}");
			if (ptr == NULL)
				break;
			n = ptr - fmt;

			format_log(ft, "found #{}: %.*s", (int)n, fmt);
			if (format_replace(ft, fmt, n, &buf, &len, &off) != 0)
				break;
			fmt += n + 1;
			continue;
		case '}':
		case '#':
		case ',':
			format_log(ft, "found #%c", ch);
			while (len - off < 2) {
				buf = xreallocarray(buf, 2, len);
				len *= 2;
			}
			buf[off++] = ch;
			continue;
		default:
			s = NULL;
			if (ch >= 'A' && ch <= 'Z')
				s = format_upper[ch - 'A'];
			else if (ch >= 'a' && ch <= 'z')
				s = format_lower[ch - 'a'];
			if (s == NULL) {
				while (len - off < 3) {
					buf = xreallocarray(buf, 2, len);
					len *= 2;
				}
				buf[off++] = '#';
				buf[off++] = ch;
				continue;
			}
			n = strlen(s);
			format_log(ft, "found #%c: %s", ch, s);
			if (format_replace(ft, s, n, &buf, &len, &off) != 0)
				break;
			continue;
		}

		break;
	}
	buf[off] = '\0';

	format_log(ft, "result is: %s", buf);
	ft->loop--;

	return (buf);
}