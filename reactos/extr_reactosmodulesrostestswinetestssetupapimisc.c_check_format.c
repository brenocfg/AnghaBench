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
typedef  char* LPSTR ;
typedef  char CHAR ;
typedef  int BOOL ;

/* Variables and functions */
 scalar_t__ CSTR_EQUAL ; 
 scalar_t__ CompareStringA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,char*,int) ; 
 int /*<<< orphan*/  GetWindowsDirectoryA (char*,int) ; 
 int /*<<< orphan*/  LOCALE_SYSTEM_DEFAULT ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  NORM_IGNORECASE ; 
 int /*<<< orphan*/  strcat (char*,char const*) ; 
 int strlen (char*) ; 

__attribute__((used)) static BOOL check_format(LPSTR path, LPSTR inf)
{
    CHAR check[MAX_PATH];
    BOOL res;

    static const CHAR format[] = "\\INF\\oem";

    GetWindowsDirectoryA(check, MAX_PATH);
    strcat(check, format);
    res = CompareStringA(LOCALE_SYSTEM_DEFAULT, NORM_IGNORECASE, check, -1, path, strlen(check)) == CSTR_EQUAL &&
          path[strlen(check)] != '\\';

    return (!inf) ? res : res && (inf == path + strlen(check) - 3);
}