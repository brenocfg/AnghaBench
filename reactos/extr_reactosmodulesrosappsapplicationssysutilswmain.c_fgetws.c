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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 char* GlobalAlloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GlobalFree (char*) ; 
 int /*<<< orphan*/  a2w (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fgets (char*,int,int /*<<< orphan*/ *) ; 

wchar_t *
fgetws(wchar_t *buf, int bufsize, FILE *file)
{
	char * abuf = GlobalAlloc(bufsize,0);
	if (!buf)return NULL;
	fgets(abuf,bufsize,file);
	a2w(abuf,buf);
	GlobalFree(abuf);
	return buf;
}