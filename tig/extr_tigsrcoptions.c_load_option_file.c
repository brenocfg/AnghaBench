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
struct io {int dummy; } ;
struct config_state {char const* member_0; int member_2; int errors; int /*<<< orphan*/  lineno; int /*<<< orphan*/  member_1; } ;
typedef  enum status_code { ____Placeholder_status_code } status_code ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 scalar_t__ ENOENT ; 
 int ERROR_FILE_DOES_NOT_EXIST ; 
 int SIZEOF_STR ; 
 int SUCCESS ; 
 int error (char*,char const*,...) ; 
 scalar_t__ io_error (struct io*) ; 
 int io_load_span (struct io*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct config_state*) ; 
 int /*<<< orphan*/  io_open (struct io*,char*,char*) ; 
 char* io_strerror (struct io*) ; 
 int /*<<< orphan*/  path_expand (char*,int,char const*) ; 
 int /*<<< orphan*/  read_option ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 int /*<<< orphan*/  warn (char*,char*) ; 

__attribute__((used)) static enum status_code
load_option_file(const char *path)
{
	struct config_state config = { path, 0, false };
	struct io io;
	char buf[SIZEOF_STR];

	/* Do not read configuration from stdin if set to "" */
	if (!path || !strlen(path))
		return SUCCESS;

	if (!path_expand(buf, sizeof(buf), path))
		return error("Failed to expand path: %s", path);

	/* It's OK that the file doesn't exist. */
	if (!io_open(&io, "%s", buf)) {
		/* XXX: Must return ERROR_FILE_DOES_NOT_EXIST so missing
		 * system tigrc is detected properly. */
		if (io_error(&io) == ENOENT)
			return ERROR_FILE_DOES_NOT_EXIST;
		return error("Error loading file %s: %s", buf, io_strerror(&io));
	}

	if (io_load_span(&io, " \t", &config.lineno, read_option, &config) != SUCCESS ||
	    config.errors == true)
		warn("Errors while loading %s.", buf);
	return SUCCESS;
}