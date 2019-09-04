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
typedef  int /*<<< orphan*/  LPFILETIME ;
typedef  scalar_t__ HANDLE ;

/* Variables and functions */
 scalar_t__ CreateFileU (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FILE_FLAG_BACKUP_SEMANTICS ; 
 int /*<<< orphan*/  FILE_SHARE_READ ; 
 int GENERIC_READ ; 
 int GENERIC_WRITE ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int /*<<< orphan*/  OPEN_EXISTING ; 
 int /*<<< orphan*/  SetFileTime (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WindowsErrorString () ; 
 int /*<<< orphan*/  safe_closehandle (scalar_t__) ; 
 int /*<<< orphan*/  uprintf (char*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __inline set_directory_timestamp(char* path, LPFILETIME creation, LPFILETIME last_access, LPFILETIME modify)
{
	HANDLE dir_handle = CreateFileU(path, GENERIC_READ | GENERIC_WRITE,
		FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_FLAG_BACKUP_SEMANTICS, NULL);
	if ((dir_handle == INVALID_HANDLE_VALUE) || (!SetFileTime(dir_handle, creation, last_access, modify)))
		uprintf("  Could not set timestamp for directory '%s': %s", path, WindowsErrorString());
	safe_closehandle(dir_handle);
}