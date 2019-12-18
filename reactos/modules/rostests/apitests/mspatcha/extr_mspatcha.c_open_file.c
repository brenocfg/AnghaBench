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
typedef  int /*<<< orphan*/  HANDLE ;
typedef  int DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CreateFileA (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int FILE_ATTRIBUTE_NORMAL ; 
 int FILE_ATTRIBUTE_READONLY ; 
 int /*<<< orphan*/  FILE_SHARE_READ ; 
 int GENERIC_READ ; 
 int GENERIC_WRITE ; 
 int /*<<< orphan*/  OPEN_EXISTING ; 

HANDLE open_file(char* filename, BOOL bWrite)
{
    DWORD dwAccess = GENERIC_READ | (bWrite ? GENERIC_WRITE : 0);
    DWORD dwAttr = (bWrite ? FILE_ATTRIBUTE_NORMAL : FILE_ATTRIBUTE_READONLY);
    return CreateFileA(filename, dwAccess, FILE_SHARE_READ, NULL, OPEN_EXISTING,
                       dwAttr, NULL);
}