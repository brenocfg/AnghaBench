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
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ CreateDirectoryA (char*,int /*<<< orphan*/ *) ; 
 scalar_t__ ERROR_ALREADY_EXISTS ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  GetCurrentDirectoryA (int,char*) ; 
 scalar_t__ GetLastError () ; 
 int /*<<< orphan*/  GetTempPathA (int,char*) ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  RemoveDirectoryA (char*) ; 
 int /*<<< orphan*/  SetCurrentDirectoryA (char*) ; 
 scalar_t__ TRUE ; 
 char* _fullpath (char*,char*,int) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 

__attribute__((used)) static void test_fullpath(void)
{
    char full[MAX_PATH];
    char tmppath[MAX_PATH];
    char prevpath[MAX_PATH];
    char level1[MAX_PATH];
    char level2[MAX_PATH];
    char teststring[MAX_PATH];
    char *freeme;
    BOOL rc,free1,free2;

    free1=free2=TRUE;
    GetCurrentDirectoryA(MAX_PATH, prevpath);
    GetTempPathA(MAX_PATH,tmppath);
    strcpy(level1,tmppath);
    strcat(level1,"msvcrt-test\\");

    rc = CreateDirectoryA(level1,NULL);
    if (!rc && GetLastError()==ERROR_ALREADY_EXISTS)
        free1=FALSE;

    strcpy(level2,level1);
    strcat(level2,"nextlevel\\");
    rc = CreateDirectoryA(level2,NULL);
    if (!rc && GetLastError()==ERROR_ALREADY_EXISTS)
        free2=FALSE;
    SetCurrentDirectoryA(level2);

    ok(_fullpath(full,"test", MAX_PATH)!=NULL,"_fullpath failed\n");
    strcpy(teststring,level2);
    strcat(teststring,"test");
    ok(strcmp(full,teststring)==0,"Invalid Path returned %s\n",full);
    ok(_fullpath(full,"\\test", MAX_PATH)!=NULL,"_fullpath failed\n");
    memcpy(teststring,level2,3);
    teststring[3]=0;
    strcat(teststring,"test");
    ok(strcmp(full,teststring)==0,"Invalid Path returned %s\n",full);
    ok(_fullpath(full,"..\\test", MAX_PATH)!=NULL,"_fullpath failed\n");
    strcpy(teststring,level1);
    strcat(teststring,"test");
    ok(strcmp(full,teststring)==0,"Invalid Path returned %s\n",full);
    ok(_fullpath(full,"..\\test", 10)==NULL,"_fullpath failed to generate error\n");

    freeme = _fullpath(NULL,"test", 0);
    ok(freeme!=NULL,"No path returned\n");
    strcpy(teststring,level2);
    strcat(teststring,"test");
    ok(strcmp(freeme,teststring)==0,"Invalid Path returned %s\n",freeme);
    free(freeme);

    SetCurrentDirectoryA(prevpath);
    if (free2)
        RemoveDirectoryA(level2);
    if (free1)
        RemoveDirectoryA(level1);
}