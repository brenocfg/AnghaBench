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
typedef  char CHAR ;

/* Variables and functions */
 int /*<<< orphan*/  DeleteFileA (char*) ; 
 char* LONGDIR ; 
 char* LONGFILE ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  RemoveDirectoryA (char*) ; 
 char* SHORTDIR ; 
 char* SHORTFILE ; 
 int /*<<< orphan*/  SetCurrentDirectoryA (char*) ; 
 int /*<<< orphan*/  ok (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,char*,...) ; 

__attribute__((used)) static void test_CleanupPathA(CHAR *origdir, CHAR *curdir)
{
  CHAR tmpstr[MAX_PATH];
  sprintf(tmpstr,"%s\\%s\\%s",curdir,SHORTDIR,SHORTFILE);
  ok(DeleteFileA(tmpstr),"DeleteFileA failed\n");
  sprintf(tmpstr,"%s\\%s\\%s",curdir,SHORTDIR,LONGFILE);
  ok(DeleteFileA(tmpstr),"DeleteFileA failed\n");
  sprintf(tmpstr,"%s\\%s\\%s",curdir,LONGDIR,SHORTFILE);
  ok(DeleteFileA(tmpstr),"DeleteFileA failed\n");
  sprintf(tmpstr,"%s\\%s\\%s",curdir,LONGDIR,LONGFILE);
  ok(DeleteFileA(tmpstr),"DeleteFileA failed\n");
  sprintf(tmpstr,"%s\\%s",curdir,SHORTDIR);
  ok(RemoveDirectoryA(tmpstr),"RemoveDirectoryA failed\n");
  sprintf(tmpstr,"%s\\%s",curdir,LONGDIR);
  ok(RemoveDirectoryA(tmpstr),"RemoveDirectoryA failed\n");
  ok(SetCurrentDirectoryA(origdir),"SetCurrentDirectoryA failed\n");
  ok(RemoveDirectoryA(curdir),"RemoveDirectoryA failed\n");
}