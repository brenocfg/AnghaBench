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
typedef  int /*<<< orphan*/  wchar_t ;

/* Variables and functions */
 int /*<<< orphan*/  CSIDL_FONTS ; 
 char* FromWide (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetWindowsDirectoryW (int /*<<< orphan*/ *,int) ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  SHGFP_TYPE_CURRENT ; 
 scalar_t__ SHGetFolderPathW (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  TEXT (char*) ; 
 int /*<<< orphan*/  wcscat (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static char* GetWindowsFontPath()
{
    wchar_t wdir[MAX_PATH];
    if( S_OK != SHGetFolderPathW( NULL, CSIDL_FONTS, NULL, SHGFP_TYPE_CURRENT, wdir ) )
    {
        GetWindowsDirectoryW( wdir, MAX_PATH );
        wcscat( wdir, TEXT("\\fonts") );
    }
    return FromWide( wdir );
}