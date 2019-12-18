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

/* Variables and functions */
 int /*<<< orphan*/  EXIT_SUCCESS ; 
 char* ZFS_META_NAME ; 
 char* ZFS_META_RELEASE ; 
 char* ZFS_META_VERSION ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,char*,char*,char*) ; 

__attribute__((used)) static void
_zed_conf_display_version(void)
{
	printf("%s-%s-%s\n",
	    ZFS_META_NAME, ZFS_META_VERSION, ZFS_META_RELEASE);

	exit(EXIT_SUCCESS);
}