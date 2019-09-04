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
struct run_request {char const** argv; } ;
struct request_info {int /*<<< orphan*/  name; } ;
struct keymap {int /*<<< orphan*/  name; } ;
typedef  enum request { ____Placeholder_request } request ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 char const* enum_name (int /*<<< orphan*/ ) ; 
 char* format_run_request_flags (struct run_request const*) ; 
 int io_fprintf (int /*<<< orphan*/ *,char*,char const*,...) ; 

__attribute__((used)) static bool
save_option_keybinding(void *data, const char *group, struct keymap *keymap,
		       enum request request, const char *key,
		       const struct request_info *req_info,
		       const struct run_request *run_req)
{
	FILE *file = data;

	if (group && !io_fprintf(file, "\n# %s", group))
		return false;

	if (!io_fprintf(file, "\nbind %-10s %-15s ", enum_name(keymap->name), key))
		return false;

	if (req_info) {
		return io_fprintf(file, "%s", enum_name(req_info->name));

	} else {
		const char *sep = format_run_request_flags(run_req);
		int i;

		for (i = 0; run_req->argv[i]; i++) {
			if (!io_fprintf(file, "%s%s", sep, run_req->argv[i]))
				return false;
			sep = " ";
		}

		return true;
	}
}