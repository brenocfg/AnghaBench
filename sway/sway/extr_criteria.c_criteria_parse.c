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
struct criteria {char* raw; int /*<<< orphan*/  window_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATOM_LAST ; 
 int /*<<< orphan*/  SWAY_DEBUG ; 
 void* calloc (int,int) ; 
 int /*<<< orphan*/  criteria_destroy (struct criteria*) ; 
 scalar_t__ criteria_is_empty (struct criteria*) ; 
 char* error ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  parse_token (struct criteria*,char*,char*) ; 
 int /*<<< orphan*/  skip_spaces (char**) ; 
 char* strdup (char*) ; 
 int /*<<< orphan*/  strncpy (char*,char*,int) ; 
 int /*<<< orphan*/  sway_log (int /*<<< orphan*/ ,char*,char*,char*) ; 
 int /*<<< orphan*/  unescape (char*) ; 

struct criteria *criteria_parse(char *raw, char **error_arg) {
	*error_arg = NULL;
	error = NULL;

	char *head = raw;
	skip_spaces(&head);
	if (*head != '[') {
		*error_arg = strdup("No criteria");
		return NULL;
	}
	++head;

	struct criteria *criteria = calloc(1, sizeof(struct criteria));
#if HAVE_XWAYLAND
	criteria->window_type = ATOM_LAST; // default value
#endif
	char *name = NULL, *value = NULL;
	bool in_quotes = false;

	while (*head && *head != ']') {
		skip_spaces(&head);
		// Parse token name
		char *namestart = head;
		while ((*head >= 'a' && *head <= 'z') || *head == '_') {
			++head;
		}
		name = calloc(head - namestart + 1, 1);
		if (head != namestart) {
			strncpy(name, namestart, head - namestart);
		}
		// Parse token value
		skip_spaces(&head);
		value = NULL;
		if (*head == '=') {
			++head;
			skip_spaces(&head);
			if (*head == '"') {
				in_quotes = true;
				++head;
			}
			char *valuestart = head;
			if (in_quotes) {
				while (*head && (*head != '"' || *(head - 1) == '\\')) {
					++head;
				}
				if (!*head) {
					*error_arg = strdup("Quote mismatch in criteria");
					goto cleanup;
				}
			} else {
				while (*head && *head != ' ' && *head != ']') {
					++head;
				}
			}
			value = calloc(head - valuestart + 1, 1);
			strncpy(value, valuestart, head - valuestart);
			if (in_quotes) {
				++head;
				in_quotes = false;
			}
			unescape(value);
			sway_log(SWAY_DEBUG, "Found pair: %s=%s", name, value);
		}
		if (!parse_token(criteria, name, value)) {
			*error_arg = error;
			goto cleanup;
		}
		skip_spaces(&head);
		free(name);
		free(value);
		name = NULL;
		value = NULL;
	}
	if (*head != ']') {
		*error_arg = strdup("No closing brace found in criteria");
		goto cleanup;
	}

	if (criteria_is_empty(criteria)) {
		*error_arg = strdup("Criteria is empty");
		goto cleanup;
	}

	++head;
	int len = head - raw;
	criteria->raw = calloc(len + 1, 1);
	strncpy(criteria->raw, raw, len);
	return criteria;

cleanup:
	free(name);
	free(value);
	criteria_destroy(criteria);
	return NULL;
}