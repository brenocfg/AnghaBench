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
 scalar_t__ debugMaxMemSize ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/ * stderr ; 
 int /*<<< orphan*/  xmlMemDisplay (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * xmlMemoryDumpFile ; 

void
xmlMemoryDump(void)
{
#ifdef MEM_LIST
    FILE *dump;

    if (debugMaxMemSize == 0)
	return;
    dump = fopen(".memdump", "w");
    if (dump == NULL)
	xmlMemoryDumpFile = stderr;
    else xmlMemoryDumpFile = dump;

    xmlMemDisplay(xmlMemoryDumpFile);

    if (dump != NULL) fclose(dump);
#endif /* MEM_LIST */
}