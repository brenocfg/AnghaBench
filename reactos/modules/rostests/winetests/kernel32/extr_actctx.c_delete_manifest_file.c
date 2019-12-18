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
typedef  int /*<<< orphan*/  path ;
typedef  int /*<<< orphan*/  CHAR ;

/* Variables and functions */
 int /*<<< orphan*/  DeleteFileA (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetTempPathA (int,int /*<<< orphan*/ *) ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  strcat (int /*<<< orphan*/ *,char const*) ; 

__attribute__((used)) static void delete_manifest_file(const char *filename)
{
    CHAR path[MAX_PATH];

    GetTempPathA(sizeof(path)/sizeof(CHAR), path);
    strcat(path, filename);
    DeleteFileA(path);
}