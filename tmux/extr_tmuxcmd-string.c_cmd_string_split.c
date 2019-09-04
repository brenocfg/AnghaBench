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

/* Variables and functions */
#define  EOF 128 
 int SIZE_MAX ; 
 int /*<<< orphan*/  cmd_free_argv (int,char**) ; 
 int /*<<< orphan*/  cmd_string_copy (char**,char*,size_t*) ; 
 char* cmd_string_expand_tilde (char const*,size_t*) ; 
 int cmd_string_getc (char const*,size_t*) ; 
 char* cmd_string_string (char const*,size_t*,char,int) ; 
 char* cmd_string_variable (char const*,size_t*) ; 
 int /*<<< orphan*/  environ_put (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  global_environ ; 
 int /*<<< orphan*/  memmove (char**,char**,int) ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  strcspn (char*,char*) ; 
 char* xrealloc (char*,size_t) ; 
 char** xreallocarray (char**,int,int) ; 

int
cmd_string_split(const char *s, int *rargc, char ***rargv)
{
	size_t		p = 0;
	int		ch, argc = 0, append = 0;
	char	      **argv = NULL, *buf = NULL, *t;
	const char     *whitespace, *equals;
	size_t		len = 0;

	for (;;) {
		ch = cmd_string_getc(s, &p);
		switch (ch) {
		case '\'':
			if ((t = cmd_string_string(s, &p, '\'', 0)) == NULL)
				goto error;
			cmd_string_copy(&buf, t, &len);
			break;
		case '"':
			if ((t = cmd_string_string(s, &p, '"', 1)) == NULL)
				goto error;
			cmd_string_copy(&buf, t, &len);
			break;
		case '$':
			if ((t = cmd_string_variable(s, &p)) == NULL)
				goto error;
			cmd_string_copy(&buf, t, &len);
			break;
		case '#':
			/* Comment: discard rest of line. */
			while ((ch = cmd_string_getc(s, &p)) != EOF)
				;
			/* FALLTHROUGH */
		case EOF:
		case ' ':
		case '\t':
			if (buf != NULL) {
				buf = xrealloc(buf, len + 1);
				buf[len] = '\0';

				argv = xreallocarray(argv, argc + 1,
				    sizeof *argv);
				argv[argc++] = buf;

				buf = NULL;
				len = 0;
			}

			if (ch != EOF)
				break;

			while (argc != 0) {
				equals = strchr(argv[0], '=');
				whitespace = argv[0] + strcspn(argv[0], " \t");
				if (equals == NULL || equals > whitespace)
					break;
				environ_put(global_environ, argv[0]);
				argc--;
				memmove(argv, argv + 1, argc * (sizeof *argv));
			}
			goto done;
		case '~':
			if (buf != NULL) {
				append = 1;
				break;
			}
			t = cmd_string_expand_tilde(s, &p);
			if (t == NULL)
				goto error;
			cmd_string_copy(&buf, t, &len);
			break;
		default:
			append = 1;
			break;
		}
		if (append) {
			if (len >= SIZE_MAX - 2)
				goto error;
			buf = xrealloc(buf, len + 1);
			buf[len++] = ch;
		}
		append = 0;
	}

done:
	*rargc = argc;
	*rargv = argv;

	free(buf);
	return (0);

error:
	if (argv != NULL)
		cmd_free_argv(argc, argv);
	free(buf);
	return (-1);
}