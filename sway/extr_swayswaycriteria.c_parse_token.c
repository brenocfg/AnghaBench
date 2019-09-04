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
struct criteria {int autofail; int floating; int tiling; char urgent; int /*<<< orphan*/  workspace; int /*<<< orphan*/  con_mark; int /*<<< orphan*/  con_id; int /*<<< orphan*/  app_id; int /*<<< orphan*/  shell; int /*<<< orphan*/  title; } ;
typedef  enum criteria_token { ____Placeholder_criteria_token } criteria_token ;

/* Variables and functions */
#define  T_APP_ID 137 
#define  T_CON_ID 136 
#define  T_CON_MARK 135 
#define  T_FLOATING 134 
#define  T_INVALID 133 
#define  T_SHELL 132 
#define  T_TILING 131 
#define  T_TITLE 130 
#define  T_URGENT 129 
#define  T_WORKSPACE 128 
 void* error ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  generate_regex (int /*<<< orphan*/ *,char*) ; 
 char* get_focused_prop (int,int*) ; 
 void* malloc (int) ; 
 int /*<<< orphan*/  snprintf (void*,int,char const*,char*) ; 
 scalar_t__ strcmp (char*,char*) ; 
 void* strdup (char*) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  strtoul (char*,char**,int) ; 
 int token_from_name (char*) ; 

__attribute__((used)) static bool parse_token(struct criteria *criteria, char *name, char *value) {
	enum criteria_token token = token_from_name(name);
	if (token == T_INVALID) {
		const char *fmt = "Token '%s' is not recognized";
		int len = strlen(fmt) + strlen(name) - 1;
		error = malloc(len);
		snprintf(error, len, fmt, name);
		return false;
	}

	char *effective_value = NULL;
	if (value && strcmp(value, "__focused__") == 0) {
		bool autofail = false;
		effective_value = get_focused_prop(token, &autofail);
		if (!effective_value && autofail) {
			criteria->autofail = true;
			return true;
		}
	} else if (value) {
		effective_value = strdup(value);
	}

	// Require value, unless token is floating or tiled
	if (!effective_value && token != T_FLOATING && token != T_TILING) {
		const char *fmt = "Token '%s' requires a value";
		int len = strlen(fmt) + strlen(name) - 1;
		error = malloc(len);
		snprintf(error, len, fmt, name);
		return false;
	}

	char *endptr = NULL;
	switch (token) {
	case T_TITLE:
		generate_regex(&criteria->title, effective_value);
		break;
	case T_SHELL:
		generate_regex(&criteria->shell, effective_value);
		break;
	case T_APP_ID:
		generate_regex(&criteria->app_id, effective_value);
		break;
	case T_CON_ID:
		criteria->con_id = strtoul(effective_value, &endptr, 10);
		if (*endptr != 0) {
			error = strdup("The value for 'con_id' should be '__focused__' or numeric");
		}
		break;
	case T_CON_MARK:
		generate_regex(&criteria->con_mark, effective_value);
		break;
#if HAVE_XWAYLAND
	case T_CLASS:
		generate_regex(&criteria->class, effective_value);
		break;
	case T_ID:
		criteria->id = strtoul(effective_value, &endptr, 10);
		if (*endptr != 0) {
			error = strdup("The value for 'id' should be numeric");
		}
		break;
	case T_INSTANCE:
		generate_regex(&criteria->instance, effective_value);
		break;
	case T_WINDOW_ROLE:
		generate_regex(&criteria->window_role, effective_value);
		break;
	case T_WINDOW_TYPE:
		criteria->window_type = parse_window_type(effective_value);
		break;
#endif
	case T_FLOATING:
		criteria->floating = true;
		break;
	case T_TILING:
		criteria->tiling = true;
		break;
	case T_URGENT:
		if (strcmp(effective_value, "latest") == 0 ||
				strcmp(effective_value, "newest") == 0 ||
				strcmp(effective_value, "last") == 0 ||
				strcmp(effective_value, "recent") == 0) {
			criteria->urgent = 'l';
		} else if (strcmp(effective_value, "oldest") == 0 ||
				strcmp(effective_value, "first") == 0) {
			criteria->urgent = 'o';
		} else {
			error =
				strdup("The value for 'urgent' must be 'first', 'last', "
						"'latest', 'newest', 'oldest' or 'recent'");
		}
		break;
	case T_WORKSPACE:
		generate_regex(&criteria->workspace, effective_value);
		break;
	case T_INVALID:
		break;
	}
	free(effective_value);

	if (error) {
		return false;
	}

	return true;
}