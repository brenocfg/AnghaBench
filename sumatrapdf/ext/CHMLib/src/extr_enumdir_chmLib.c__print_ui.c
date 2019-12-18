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
struct chmUnitInfo {int flags; char* path; scalar_t__ length; scalar_t__ start; scalar_t__ space; } ;
struct chmFile {int dummy; } ;

/* Variables and functions */
 int CHM_ENUMERATE_DIRS ; 
 int CHM_ENUMERATE_FILES ; 
 int CHM_ENUMERATE_META ; 
 int CHM_ENUMERATE_NORMAL ; 
 int CHM_ENUMERATE_SPECIAL ; 
 int CHM_ENUMERATOR_CONTINUE ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*,int,int,int,char*,char*) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 

int _print_ui(struct chmFile *h,
              struct chmUnitInfo *ui,
              void *context)
{
    static char szBuf[128];
	memset(szBuf, 0, 128);
	if(ui->flags & CHM_ENUMERATE_NORMAL)
		strcpy(szBuf, "normal ");
	else if(ui->flags & CHM_ENUMERATE_SPECIAL)
		strcpy(szBuf, "special ");
	else if(ui->flags & CHM_ENUMERATE_META)
		strcpy(szBuf, "meta ");
	
	if(ui->flags & CHM_ENUMERATE_DIRS)
		strcat(szBuf, "dir");
	else if(ui->flags & CHM_ENUMERATE_FILES)
		strcat(szBuf, "file");

    printf("   %1d %8d %8d   %s\t\t%s\n",
           (int)ui->space,
           (int)ui->start,
           (int)ui->length,
		   szBuf,
           ui->path);
    return CHM_ENUMERATOR_CONTINUE;}