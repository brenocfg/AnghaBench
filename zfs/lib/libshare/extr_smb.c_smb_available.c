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
struct stat {int /*<<< orphan*/  st_mode; } ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  B_TRUE ; 
 int /*<<< orphan*/  F_OK ; 
 int /*<<< orphan*/  NET_CMD_PATH ; 
 int /*<<< orphan*/  SHARE_DIR ; 
 int /*<<< orphan*/  S_ISDIR (int /*<<< orphan*/ ) ; 
 scalar_t__ access (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ lstat (int /*<<< orphan*/ ,struct stat*) ; 

__attribute__((used)) static boolean_t
smb_available(void)
{
	struct stat statbuf;

	if (lstat(SHARE_DIR, &statbuf) != 0 ||
	    !S_ISDIR(statbuf.st_mode))
		return (B_FALSE);

	if (access(NET_CMD_PATH, F_OK) != 0)
		return (B_FALSE);

	return (B_TRUE);
}