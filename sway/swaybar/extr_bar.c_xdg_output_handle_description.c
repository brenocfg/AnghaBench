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
struct zxdg_output_v1 {int dummy; } ;
struct swaybar_output {char* identifier; } ;

/* Variables and functions */
 int /*<<< orphan*/  SWAY_ERROR ; 
 int /*<<< orphan*/  free (char*) ; 
 char* malloc (size_t) ; 
 int /*<<< orphan*/  strncpy (char*,char const*,size_t) ; 
 char* strrchr (char const*,char) ; 
 int /*<<< orphan*/  sway_log (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void xdg_output_handle_description(void *data,
		struct zxdg_output_v1 *xdg_output, const char *description) {
	// wlroots currently sets the description to `make model serial (name)`
	// If this changes in the future, this will need to be modified.
	struct swaybar_output *output = data;
	free(output->identifier);
	output->identifier = NULL;
	char *paren = strrchr(description, '(');
	if (paren) {
		size_t length = paren - description;
		output->identifier = malloc(length);
		if (!output->identifier) {
			sway_log(SWAY_ERROR, "Failed to allocate output identifier");
			return;
		}
		strncpy(output->identifier, description, length);
		output->identifier[length - 1] = '\0';
	}
}