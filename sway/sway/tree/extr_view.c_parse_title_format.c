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
struct sway_view {char* title_format; } ;

/* Variables and functions */
 size_t append_prop (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lenient_strcat (char*,char*) ; 
 int /*<<< orphan*/  lenient_strncat (char*,char*,int) ; 
 char* strchr (char*,char) ; 
 scalar_t__ strcmp (char*,char*) ; 
 scalar_t__ strlen (char*) ; 
 scalar_t__ strncmp (char*,char*,int) ; 
 int /*<<< orphan*/  view_get_app_id (struct sway_view*) ; 
 int /*<<< orphan*/  view_get_class (struct sway_view*) ; 
 int /*<<< orphan*/  view_get_instance (struct sway_view*) ; 
 int /*<<< orphan*/  view_get_shell (struct sway_view*) ; 
 int /*<<< orphan*/  view_get_title (struct sway_view*) ; 

__attribute__((used)) static size_t parse_title_format(struct sway_view *view, char *buffer) {
	if (!view->title_format || strcmp(view->title_format, "%title") == 0) {
		return append_prop(buffer, view_get_title(view));
	}

	size_t len = 0;
	char *format = view->title_format;
	char *next = strchr(format, '%');
	while (next) {
		// Copy everything up to the %
		lenient_strncat(buffer, format, next - format);
		len += next - format;
		format = next;

		if (strncmp(next, "%title", 6) == 0) {
			len += append_prop(buffer, view_get_title(view));
			format += 6;
		} else if (strncmp(next, "%app_id", 7) == 0) {
			len += append_prop(buffer, view_get_app_id(view));
			format += 7;
		} else if (strncmp(next, "%class", 6) == 0) {
			len += append_prop(buffer, view_get_class(view));
			format += 6;
		} else if (strncmp(next, "%instance", 9) == 0) {
			len += append_prop(buffer, view_get_instance(view));
			format += 9;
		} else if (strncmp(next, "%shell", 6) == 0) {
			len += append_prop(buffer, view_get_shell(view));
			format += 6;
		} else {
			lenient_strcat(buffer, "%");
			++format;
			++len;
		}
		next = strchr(format, '%');
	}
	lenient_strcat(buffer, format);
	len += strlen(format);

	return len;
}