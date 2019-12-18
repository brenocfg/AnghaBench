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
typedef  int /*<<< orphan*/  u_int ;
struct format_tree {int dummy; } ;
struct format_modifier {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  format_add_modifier (struct format_modifier**,int /*<<< orphan*/ *,char const*,int,char**,int) ; 
 char* format_expand (struct format_tree*,char*) ; 
 int /*<<< orphan*/  format_free_modifiers (struct format_modifier*,int /*<<< orphan*/ ) ; 
 scalar_t__ format_is_end (char const) ; 
 char* format_skip (char const*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  ispunct (char const) ; 
 scalar_t__ memcmp (char*,char const*,int) ; 
 int /*<<< orphan*/ * strchr (char*,char const) ; 
 char** xcalloc (int,int) ; 
 char** xreallocarray (char**,int,int) ; 
 char* xstrndup (char const*,int) ; 

__attribute__((used)) static struct format_modifier *
format_build_modifiers(struct format_tree *ft, const char **s, u_int *count)
{
	const char		*cp = *s, *end;
	struct format_modifier	*list = NULL;
	char			 c, last[] = "X;:", **argv, *value;
	int			 argc;

	/*
	 * Modifiers are a ; separated list of the forms:
	 *      l,m,C,b,d,t,q,E,T,S,W,P,<,>
	 *	=a
	 *	=/a
	 *      =/a/
	 *	s/a/b/
	 *	s/a/b
	 *	||,&&,!=,==,<=,>=
	 */

	*count = 0;

	while (*cp != '\0' && *cp != ':') {
		/* Skip and separator character. */
		if (*cp == ';')
			cp++;

		/* Check single character modifiers with no arguments. */
		if (strchr("lbdtqETSWP<>", cp[0]) != NULL &&
		    format_is_end(cp[1])) {
			format_add_modifier(&list, count, cp, 1, NULL, 0);
			cp++;
			continue;
		}

		/* Then try double character with no arguments. */
		if ((memcmp("||", cp, 2) == 0 ||
		    memcmp("&&", cp, 2) == 0 ||
		    memcmp("!=", cp, 2) == 0 ||
		    memcmp("==", cp, 2) == 0 ||
		    memcmp("<=", cp, 2) == 0 ||
		    memcmp(">=", cp, 2) == 0) &&
		    format_is_end(cp[2])) {
			format_add_modifier(&list, count, cp, 2, NULL, 0);
			cp += 2;
			continue;
		}

		/* Now try single character with arguments. */
		if (strchr("mCs=", cp[0]) == NULL)
			break;
		c = cp[0];

		/* No arguments provided. */
		if (format_is_end(cp[1])) {
			format_add_modifier(&list, count, cp, 1, NULL, 0);
			cp++;
			continue;
		}
		argv = NULL;
		argc = 0;

		/* Single argument with no wrapper character. */
		if (!ispunct(cp[1]) || cp[1] == '-') {
			end = format_skip(cp + 1, ":;");
			if (end == NULL)
				break;

			argv = xcalloc(1, sizeof *argv);
			value = xstrndup(cp + 1, end - (cp + 1));
			argv[0] = format_expand(ft, value);
			free(value);
			argc = 1;

			format_add_modifier(&list, count, &c, 1, argv, argc);
			cp = end;
			continue;
		}

		/* Multiple arguments with a wrapper character. */
		last[0] = cp[1];
		cp++;
		do {
			if (cp[0] == last[0] && format_is_end(cp[1])) {
				cp++;
				break;
			}
			end = format_skip(cp + 1, last);
			if (end == NULL)
				break;
			cp++;

			argv = xreallocarray (argv, argc + 1, sizeof *argv);
			value = xstrndup(cp, end - cp);
			argv[argc++] = format_expand(ft, value);
			free(value);

			cp = end;
		} while (!format_is_end(cp[0]));
		format_add_modifier(&list, count, &c, 1, argv, argc);
	}
	if (*cp != ':') {
		format_free_modifiers(list, *count);
		*count = 0;
		return (NULL);
	}
	*s = cp + 1;
	return list;
}