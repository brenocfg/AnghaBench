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
typedef  enum status_code { ____Placeholder_status_code } status_code ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int SIZEOF_STR ; 
 int SUCCESS ; 
 int error (char*,...) ; 
 scalar_t__ io_open (int /*<<< orphan*/ *,char*,char*) ; 
 scalar_t__ is_script_executing () ; 
 int /*<<< orphan*/  path_expand (char*,int,char const*) ; 
 int /*<<< orphan*/  script_io ; 

enum status_code
open_script(const char *path)
{
	if (is_script_executing())
		return error("Scripts cannot be run from scripts");

	char buf[SIZEOF_STR];

	if (!path_expand(buf, sizeof(buf), path))
		return error("Failed to expand path: %s", path);

	return io_open(&script_io, "%s", buf)
		? SUCCESS : error("Failed to open %s", buf);
}