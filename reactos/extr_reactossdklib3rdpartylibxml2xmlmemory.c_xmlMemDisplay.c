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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*) ; 

void
xmlMemDisplay(FILE *fp)
{
#ifdef MEM_LIST
    MEMHDR *p;
    unsigned idx;
    int     nb = 0;
#if defined(HAVE_LOCALTIME) && defined(HAVE_STRFTIME)
    time_t currentTime;
    char buf[500];
    struct tm * tstruct;
#endif
#endif
    FILE *old_fp = fp;

    if (fp == NULL) {
	fp = fopen(".memorylist", "w");
	if (fp == NULL)
	    return;
    }

#ifdef MEM_LIST
#if defined(HAVE_LOCALTIME) && defined(HAVE_STRFTIME)
    currentTime = time(NULL);
    tstruct = localtime(&currentTime);
    strftime(buf, sizeof(buf) - 1, "%I:%M:%S %p", tstruct);
    fprintf(fp,"      %s\n\n", buf);
#endif


    fprintf(fp,"      MEMORY ALLOCATED : %lu, MAX was %lu\n",
            debugMemSize, debugMaxMemSize);
    fprintf(fp,"BLOCK  NUMBER   SIZE  TYPE\n");
    idx = 0;
    xmlMutexLock(xmlMemMutex);
    p = memlist;
    while (p) {
	  fprintf(fp,"%-5u  %6lu %6lu ",idx++,p->mh_number,
		  (unsigned long)p->mh_size);
        switch (p->mh_type) {
           case STRDUP_TYPE:fprintf(fp,"strdup()  in ");break;
           case MALLOC_TYPE:fprintf(fp,"malloc()  in ");break;
           case REALLOC_TYPE:fprintf(fp,"realloc() in ");break;
           case MALLOC_ATOMIC_TYPE:fprintf(fp,"atomicmalloc()  in ");break;
           case REALLOC_ATOMIC_TYPE:fprintf(fp,"atomicrealloc() in ");break;
           default:
	        fprintf(fp,"Unknown memory block, may be corrupted");
		xmlMutexUnlock(xmlMemMutex);
		if (old_fp == NULL)
		    fclose(fp);
		return;
        }
	if (p->mh_file != NULL) fprintf(fp,"%s(%u)", p->mh_file, p->mh_line);
        if (p->mh_tag != MEMTAG)
	      fprintf(fp,"  INVALID");
        nb++;
	if (nb < 100)
	    xmlMemContentShow(fp, p);
	else
	    fprintf(fp," skip");

        fprintf(fp,"\n");
        p = p->mh_next;
    }
    xmlMutexUnlock(xmlMemMutex);
#else
    fprintf(fp,"Memory list not compiled (MEM_LIST not defined !)\n");
#endif
    if (old_fp == NULL)
	fclose(fp);
}