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
struct TYPE_2__ {scalar_t__ pango_markup; } ;

/* Variables and functions */
 TYPE_1__* config ; 
 char* escape_pango_markup (char const*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  lenient_strcat (char*,char const*) ; 
 size_t strlen (char const*) ; 

__attribute__((used)) static size_t append_prop(char *buffer, const char *value) {
	if (!value) {
		return 0;
	}
	// If using pango_markup in font, we need to escape all markup chars
	// from values to make sure tags are not inserted by clients
	if (config->pango_markup) {
		char *escaped_value = escape_pango_markup(value);
		lenient_strcat(buffer, escaped_value);
		size_t len = strlen(escaped_value);
		free(escaped_value);
		return len;
	} else {
		lenient_strcat(buffer, value);
		return strlen(value);
	}
}