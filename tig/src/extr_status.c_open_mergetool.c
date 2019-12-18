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
struct TYPE_2__ {int /*<<< orphan*/  exec_dir; } ;

/* Variables and functions */
 int /*<<< orphan*/  open_external_viewer (char const**,int /*<<< orphan*/ ,int,int,int,int,int,char*) ; 
 TYPE_1__ repo ; 

__attribute__((used)) static void
open_mergetool(const char *file)
{
	const char *mergetool_argv[] = { "git", "mergetool", file, NULL };

	open_external_viewer(mergetool_argv, repo.exec_dir, false, true, false, true, true, "");
}