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
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int LPWSTR ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  lstrcatW (int,int) ; 
 int /*<<< orphan*/  lstrcpynW (int,int,int) ; 
 int lstrlenW (int) ; 
 int msi_alloc (int) ; 
 int strrchrW (int,char) ; 

__attribute__((used)) static LPWSTR wildcard_to_file(LPWSTR wildcard, LPWSTR filename)
{
    LPWSTR path, ptr;
    DWORD dirlen, pathlen;

    ptr = strrchrW(wildcard, '\\');
    dirlen = ptr - wildcard + 1;

    pathlen = dirlen + lstrlenW(filename) + 1;
    path = msi_alloc(pathlen * sizeof(WCHAR));

    lstrcpynW(path, wildcard, dirlen + 1);
    lstrcatW(path, filename);

    return path;
}