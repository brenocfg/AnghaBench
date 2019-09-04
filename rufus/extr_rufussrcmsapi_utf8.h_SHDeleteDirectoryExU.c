#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * member_7; int /*<<< orphan*/ * member_6; int /*<<< orphan*/  member_5; int /*<<< orphan*/  member_4; int /*<<< orphan*/ * member_3; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ SHFILEOPSTRUCTW ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  FILEOP_FLAGS ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FO_DELETE ; 
 int SHFileOperationW (TYPE_1__*) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  utf8_to_wchar_no_alloc (char const*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  walloc (char const*,size_t) ; 
 int /*<<< orphan*/  wfree (char const*) ; 
 int /*<<< orphan*/  wpszPath ; 

__attribute__((used)) static __inline int SHDeleteDirectoryExU(HWND hwnd, const char* pszPath, FILEOP_FLAGS fFlags)
{
	int ret;
	// String needs to be double NULL terminated, so we just use the length of the UTF-8 string
	// which is always expected to be larger than our UTF-16 one, and add 2 chars for good measure.
	size_t wpszPath_len = strlen(pszPath) + 2;
	// coverity[returned_null]
	walloc(pszPath, wpszPath_len);
	SHFILEOPSTRUCTW shfo = { hwnd, FO_DELETE, wpszPath, NULL, fFlags, FALSE, NULL, NULL };
	utf8_to_wchar_no_alloc(pszPath, wpszPath, (int)wpszPath_len);
	// FOF_SILENT | FOF_NOERRORUI | FOF_NOCONFIRMATION,
	ret = SHFileOperationW(&shfo);
	wfree(pszPath);
	return ret;
}