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

/* Variables and functions */

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