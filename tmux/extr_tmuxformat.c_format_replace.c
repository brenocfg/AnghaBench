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
struct window_pane {int /*<<< orphan*/  id; } ;
struct format_tree {struct window_pane* wp; } ;
struct format_modifier {int* modifier; int argc; int size; int /*<<< orphan*/ * argv; } ;

/* Variables and functions */
 int FORMAT_BASENAME ; 
 int FORMAT_DIRNAME ; 
 int FORMAT_EXPAND ; 
 int FORMAT_EXPANDTIME ; 
 int FORMAT_LITERAL ; 
 int FORMAT_PANES ; 
 int FORMAT_QUOTE ; 
 int FORMAT_SESSIONS ; 
 int FORMAT_TIMESTRING ; 
 int FORMAT_WINDOWS ; 
 int /*<<< orphan*/  INT_MAX ; 
 int /*<<< orphan*/  INT_MIN ; 
 scalar_t__ fnmatch (char*,char*,int /*<<< orphan*/ ) ; 
 struct format_modifier* format_build_modifiers (struct format_tree*,char const**,size_t*) ; 
 scalar_t__ format_choose (struct format_tree*,char const*,char**,char**,int) ; 
 char* format_expand (struct format_tree*,char*) ; 
 char* format_expand_time (struct format_tree*,char*) ; 
 char* format_find (struct format_tree*,char const*,int) ; 
 int /*<<< orphan*/  format_free_modifiers (struct format_modifier*,size_t) ; 
 int /*<<< orphan*/  format_log (struct format_tree*,char*,...) ; 
 scalar_t__ format_logging (struct format_tree*) ; 
 char* format_loop_panes (struct format_tree*,char const*) ; 
 char* format_loop_sessions (struct format_tree*,char const*) ; 
 char* format_loop_windows (struct format_tree*,char const*) ; 
 char* format_skip (char const*,char*) ; 
 char* format_substitute (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* format_trim_left (char*,int) ; 
 char* format_trim_right (char*,int) ; 
 scalar_t__ format_true (char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  memcpy (char*,char*,size_t) ; 
 scalar_t__ strcmp (char*,char*) ; 
 size_t strlen (char*) ; 
 int strtonum (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const**) ; 
 int /*<<< orphan*/  window_pane_search (struct window_pane*,char const*) ; 
 int /*<<< orphan*/  xasprintf (char**,char*,int /*<<< orphan*/ ) ; 
 char* xreallocarray (char*,int,size_t) ; 
 char* xstrdup (char const*) ; 
 char* xstrndup (char const*,int) ; 

__attribute__((used)) static int
format_replace(struct format_tree *ft, const char *key, size_t keylen,
    char **buf, size_t *len, size_t *off)
{
	struct window_pane	*wp = ft->wp;
	const char		*errptr, *copy, *cp;
	char			*copy0, *condition, *found, *new;
	char			*value, *left, *right;
	size_t			 valuelen;
	int			 modifiers = 0, limit = 0;
	struct format_modifier  *list, *fm, *cmp = NULL, *search = NULL;
	struct format_modifier  *sub = NULL;
	u_int			 i, count;
	int			 j;

	/* Make a copy of the key. */
	copy = copy0 = xstrndup(key, keylen);

	/* Process modifier list. */
	list = format_build_modifiers(ft, &copy, &count);
	for (i = 0; i < count; i++) {
		fm = &list[i];
		if (format_logging(ft)) {
			format_log(ft, "modifier %u is %s", i, fm->modifier);
			for (j = 0; j < fm->argc; j++) {
				format_log(ft, "modifier %u argument %d: %s", i,
				    j, fm->argv[j]);
			}
		}
		if (fm->size == 1) {
			switch (fm->modifier[0]) {
			case 'm':
				cmp = fm;
				break;
			case 'C':
				search = fm;
				break;
			case 's':
				if (fm->argc != 2)
					break;
				sub = fm;
				break;
			case '=':
				if (fm->argc != 1)
					break;
				limit = strtonum(fm->argv[0], INT_MIN, INT_MAX,
				    &errptr);
				if (errptr != NULL)
					limit = 0;
				break;
			case 'l':
				modifiers |= FORMAT_LITERAL;
				break;
			case 'b':
				modifiers |= FORMAT_BASENAME;
				break;
			case 'd':
				modifiers |= FORMAT_DIRNAME;
				break;
			case 't':
				modifiers |= FORMAT_TIMESTRING;
				break;
			case 'q':
				modifiers |= FORMAT_QUOTE;
				break;
			case 'E':
				modifiers |= FORMAT_EXPAND;
				break;
			case 'T':
				modifiers |= FORMAT_EXPANDTIME;
				break;
			case 'S':
				modifiers |= FORMAT_SESSIONS;
				break;
			case 'W':
				modifiers |= FORMAT_WINDOWS;
				break;
			case 'P':
				modifiers |= FORMAT_PANES;
				break;
			}
		} else if (fm->size == 2) {
			if (strcmp(fm->modifier, "||") == 0 ||
			    strcmp(fm->modifier, "&&") == 0 ||
			    strcmp(fm->modifier, "==") == 0 ||
			    strcmp(fm->modifier, "!=") == 0)
				cmp = fm;
		}
	}

	/* Is this a literal string? */
	if (modifiers & FORMAT_LITERAL) {
		value = xstrdup(copy);
		goto done;
	}

	/* Is this a loop, comparison or condition? */
	if (modifiers & FORMAT_SESSIONS) {
		value = format_loop_sessions(ft, copy);
		if (value == NULL)
			goto fail;
	} else if (modifiers & FORMAT_WINDOWS) {
		value = format_loop_windows(ft, copy);
		if (value == NULL)
			goto fail;
	} else if (modifiers & FORMAT_PANES) {
		value = format_loop_panes(ft, copy);
		if (value == NULL)
			goto fail;
	} else if (search != NULL) {
		/* Search in pane. */
		if (wp == NULL) {
			format_log(ft, "search '%s' but no pane", copy);
			value = xstrdup("0");
		} else {
			format_log(ft, "search '%s' pane %%%u", copy,  wp->id);
			xasprintf(&value, "%u", window_pane_search(wp, copy));
		}
	} else if (cmp != NULL) {
		/* Comparison of left and right. */
		if (format_choose(ft, copy, &left, &right, 1) != 0) {
			format_log(ft, "compare %s syntax error: %s",
			    cmp->modifier, copy);
			goto fail;
		}
		format_log(ft, "compare %s left is: %s", cmp->modifier, left);
		format_log(ft, "compare %s right is: %s", cmp->modifier, right);

		if (strcmp(cmp->modifier, "||") == 0) {
			if (format_true(left) || format_true(right))
				value = xstrdup("1");
			else
				value = xstrdup("0");
		} else if (strcmp(cmp->modifier, "&&") == 0) {
			if (format_true(left) && format_true(right))
				value = xstrdup("1");
			else
				value = xstrdup("0");
		} else if (strcmp(cmp->modifier, "==") == 0) {
			if (strcmp(left, right) == 0)
				value = xstrdup("1");
			else
				value = xstrdup("0");
		} else if (strcmp(cmp->modifier, "!=") == 0) {
			if (strcmp(left, right) != 0)
				value = xstrdup("1");
			else
				value = xstrdup("0");
		}
		else if (strcmp(cmp->modifier, "m") == 0) {
			if (fnmatch(left, right, 0) == 0)
				value = xstrdup("1");
			else
				value = xstrdup("0");
		}

		free(right);
		free(left);
	} else if (*copy == '?') {
		/* Conditional: check first and choose second or third. */
		cp = format_skip(copy + 1, ",");
		if (cp == NULL) {
			format_log(ft, "condition syntax error: %s", copy + 1);
			goto fail;
		}
		condition = xstrndup(copy + 1, cp - (copy + 1));
		format_log(ft, "condition is: %s", condition);

		found = format_find(ft, condition, modifiers);
		if (found == NULL) {
			/*
			 * If the condition not found, try to expand it. If
			 * the expansion doesn't have any effect, then assume
			 * false.
			 */
			found = format_expand(ft, condition);
			if (strcmp(found, condition) == 0) {
				free(found);
				found = xstrdup("");
				format_log(ft, "condition '%s' found: %s",
				    condition, found);
			} else {
				format_log(ft,
				    "condition '%s' not found; assuming false",
				    condition);
			}
		} else
			format_log(ft, "condition '%s' found", condition);

		if (format_choose(ft, cp + 1, &left, &right, 0) != 0) {
			format_log(ft, "condition '%s' syntax error: %s",
			    condition, cp + 1);
			free(found);
			goto fail;
		}
		if (format_true(found)) {
			format_log(ft, "condition '%s' is true", condition);
			value = format_expand(ft, left);
		} else {
			format_log(ft, "condition '%s' is false", condition);
			value = format_expand(ft, right);
		}
		free(right);
		free(left);

		free(condition);
		free(found);
	} else {
		/* Neither: look up directly. */
		value = format_find(ft, copy, modifiers);
		if (value == NULL) {
			format_log(ft, "format '%s' not found", copy);
			value = xstrdup("");
		} else
			format_log(ft, "format '%s' found: %s", copy, value);
	}

done:
	/* Expand again if required. */
	if (modifiers & FORMAT_EXPAND) {
		new = format_expand(ft, value);
		free(value);
		value = new;
	}
	else if (modifiers & FORMAT_EXPANDTIME) {
		new = format_expand_time(ft, value);
		free(value);
		value = new;
	}

	/* Perform substitution if any. */
	if (sub != NULL) {
		new = format_substitute(value, sub->argv[0], sub->argv[1]);
		format_log(ft, "substituted '%s' to '%s: %s", sub->argv[0],
		    sub->argv[1], new);
		free(value);
		value = new;
	}

	/* Truncate the value if needed. */
	if (limit > 0) {
		new = format_trim_left(value, limit);
		format_log(ft, "applied length limit %d: %s", limit, new);
		free(value);
		value = new;
	} else if (limit < 0) {
		new = format_trim_right(value, -limit);
		format_log(ft, "applied length limit %d: %s", limit, new);
		free(value);
		value = new;
	}

	/* Expand the buffer and copy in the value. */
	valuelen = strlen(value);
	while (*len - *off < valuelen + 1) {
		*buf = xreallocarray(*buf, 2, *len);
		*len *= 2;
	}
	memcpy(*buf + *off, value, valuelen);
	*off += valuelen;

	format_log(ft, "replaced '%s' with '%s'", copy0, value);
	free(value);

	format_free_modifiers(list, count);
	free(copy0);
	return (0);

fail:
	format_log(ft, "failed %s", copy0);
	format_free_modifiers(list, count);
	free(copy0);
	return (-1);
}