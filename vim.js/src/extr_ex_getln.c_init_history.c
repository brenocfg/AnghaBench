#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  long_u ;
struct TYPE_5__ {struct TYPE_5__* hisstr; } ;
typedef  TYPE_1__ histentry_T ;

/* Variables and functions */
 int HIST_COUNT ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  clear_hist_entry (TYPE_1__*) ; 
 int* hisidx ; 
 int hislen ; 
 TYPE_1__** history ; 
 scalar_t__ lalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ p_hi ; 
 int /*<<< orphan*/  vim_free (TYPE_1__*) ; 

void
init_history()
{
    int		newlen;	    /* new length of history table */
    histentry_T	*temp;
    int		i;
    int		j;
    int		type;

    /*
     * If size of history table changed, reallocate it
     */
    newlen = (int)p_hi;
    if (newlen != hislen)			/* history length changed */
    {
	for (type = 0; type < HIST_COUNT; ++type)   /* adjust the tables */
	{
	    if (newlen)
	    {
		temp = (histentry_T *)lalloc(
				(long_u)(newlen * sizeof(histentry_T)), TRUE);
		if (temp == NULL)   /* out of memory! */
		{
		    if (type == 0)  /* first one: just keep the old length */
		    {
			newlen = hislen;
			break;
		    }
		    /* Already changed one table, now we can only have zero
		     * length for all tables. */
		    newlen = 0;
		    type = -1;
		    continue;
		}
	    }
	    else
		temp = NULL;
	    if (newlen == 0 || temp != NULL)
	    {
		if (hisidx[type] < 0)		/* there are no entries yet */
		{
		    for (i = 0; i < newlen; ++i)
			clear_hist_entry(&temp[i]);
		}
		else if (newlen > hislen)	/* array becomes bigger */
		{
		    for (i = 0; i <= hisidx[type]; ++i)
			temp[i] = history[type][i];
		    j = i;
		    for ( ; i <= newlen - (hislen - hisidx[type]); ++i)
			clear_hist_entry(&temp[i]);
		    for ( ; j < hislen; ++i, ++j)
			temp[i] = history[type][j];
		}
		else				/* array becomes smaller or 0 */
		{
		    j = hisidx[type];
		    for (i = newlen - 1; ; --i)
		    {
			if (i >= 0)		/* copy newest entries */
			    temp[i] = history[type][j];
			else			/* remove older entries */
			    vim_free(history[type][j].hisstr);
			if (--j < 0)
			    j = hislen - 1;
			if (j == hisidx[type])
			    break;
		    }
		    hisidx[type] = newlen - 1;
		}
		vim_free(history[type]);
		history[type] = temp;
	    }
	}
	hislen = newlen;
    }
}