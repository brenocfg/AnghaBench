#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct icon_theme {char const* name; } ;
struct TYPE_3__ {scalar_t__ length; struct icon_theme** items; } ;
typedef  TYPE_1__ list_t ;

/* Variables and functions */
 int /*<<< orphan*/  SWAY_DEBUG ; 
 int /*<<< orphan*/  SWAY_INFO ; 
 int /*<<< orphan*/  free (char*) ; 
 char* malloc (size_t) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,size_t) ; 
 size_t strlen (char const*) ; 
 int /*<<< orphan*/  sway_log (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static void log_loaded_themes(list_t *themes) {
	if (themes->length == 0) {
		sway_log(SWAY_INFO, "Warning: no icon themes loaded");
		return;
	}

	const char sep[] = ", ";
	size_t sep_len = strlen(sep);

	size_t len = 0;
	for (int i = 0; i < themes->length; ++i) {
		struct icon_theme *theme = themes->items[i];
		len += strlen(theme->name) + sep_len;
	}

	char *str = malloc(len + 1);
	if (!str) {
		return;
	}
	char *p = str;
	for (int i = 0; i < themes->length; ++i) {
		if (i > 0) {
			memcpy(p, sep, sep_len);
			p += sep_len;
		}

		struct icon_theme *theme = themes->items[i];
		size_t name_len = strlen(theme->name);
		memcpy(p, theme->name, name_len);
		p += name_len;
	}
	*p = '\0';

	sway_log(SWAY_DEBUG, "Loaded icon themes: %s", str);
	free(str);
}