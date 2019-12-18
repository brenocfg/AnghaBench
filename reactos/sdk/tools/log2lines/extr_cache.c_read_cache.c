#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * ptail; int /*<<< orphan*/  phead; } ;
typedef  int /*<<< orphan*/  LIST_MEMBER ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int LINESIZE ; 
 TYPE_1__ cache ; 
 int /*<<< orphan*/ * cache_entry_create (char*) ; 
 char* cache_name ; 
 int /*<<< orphan*/  entry_insert (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  l2l_dbg (int,char*,char*) ; 

int
read_cache(void)
{
    FILE *fr;
    LIST_MEMBER *pentry;
    char Line[LINESIZE + 1];
    int result = 0;

    Line[LINESIZE] = '\0';

    fr = fopen(cache_name, "r");
    if (!fr)
    {
        l2l_dbg(1, "Open %s failed\n", cache_name);
        return 2;
    }
    cache.phead = cache.ptail = NULL;

    while (fgets(Line, LINESIZE, fr) != NULL)
    {
        pentry = cache_entry_create(Line);
        if (!pentry)
        {
            l2l_dbg(2, "** Create entry failed of: %s\n", Line);
        }
        else
            entry_insert(&cache, pentry);
    }

    fclose(fr);
    return result;
}