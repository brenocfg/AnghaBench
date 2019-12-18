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
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  int DWORD ;
typedef  int BOOL ;

/* Variables and functions */
 int FALSE ; 
 int FILE_ATTRIBUTE_DIRECTORY ; 
 int GetFileAttributesW (int /*<<< orphan*/ ) ; 
 int INVALID_FILE_ATTRIBUTES ; 

__attribute__((used)) static BOOL is_directory(LPCWSTR target)
{
	/*TODO correctly handle UNIX paths */
	DWORD target_attr = GetFileAttributesW(target);

	if (target_attr == INVALID_FILE_ATTRIBUTES)
		return FALSE;

	return (target_attr & FILE_ATTRIBUTE_DIRECTORY) != 0;
}