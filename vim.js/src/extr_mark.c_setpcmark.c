#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  fnum; int /*<<< orphan*/  mark; } ;
struct TYPE_7__ {int /*<<< orphan*/ * fname; TYPE_1__ fmark; } ;
typedef  TYPE_2__ xfmark_T ;
struct TYPE_10__ {scalar_t__ keepjumps; } ;
struct TYPE_9__ {int /*<<< orphan*/  b_fnum; } ;
struct TYPE_8__ {int w_jumplistidx; int w_jumplistlen; int /*<<< orphan*/  w_pcmark; TYPE_2__* w_jumplist; int /*<<< orphan*/  w_cursor; int /*<<< orphan*/  w_prev_pcmark; } ;

/* Variables and functions */
 int JUMPLISTSIZE ; 
 TYPE_5__ cmdmod ; 
 TYPE_4__* curbuf ; 
 TYPE_3__* curwin ; 
 scalar_t__ global_busy ; 
 scalar_t__ listcmd_busy ; 
 int /*<<< orphan*/  vim_free (int /*<<< orphan*/ *) ; 

void
setpcmark()
{
#ifdef FEAT_JUMPLIST
    int		i;
    xfmark_T	*fm;
#endif
#ifdef JUMPLIST_ROTATE
    xfmark_T	tempmark;
#endif

    /* for :global the mark is set only once */
    if (global_busy || listcmd_busy || cmdmod.keepjumps)
	return;

    curwin->w_prev_pcmark = curwin->w_pcmark;
    curwin->w_pcmark = curwin->w_cursor;

#ifdef FEAT_JUMPLIST
# ifdef JUMPLIST_ROTATE
    /*
     * If last used entry is not at the top, put it at the top by rotating
     * the stack until it is (the newer entries will be at the bottom).
     * Keep one entry (the last used one) at the top.
     */
    if (curwin->w_jumplistidx < curwin->w_jumplistlen)
	++curwin->w_jumplistidx;
    while (curwin->w_jumplistidx < curwin->w_jumplistlen)
    {
	tempmark = curwin->w_jumplist[curwin->w_jumplistlen - 1];
	for (i = curwin->w_jumplistlen - 1; i > 0; --i)
	    curwin->w_jumplist[i] = curwin->w_jumplist[i - 1];
	curwin->w_jumplist[0] = tempmark;
	++curwin->w_jumplistidx;
    }
# endif

    /* If jumplist is full: remove oldest entry */
    if (++curwin->w_jumplistlen > JUMPLISTSIZE)
    {
	curwin->w_jumplistlen = JUMPLISTSIZE;
	vim_free(curwin->w_jumplist[0].fname);
	for (i = 1; i < JUMPLISTSIZE; ++i)
	    curwin->w_jumplist[i - 1] = curwin->w_jumplist[i];
    }
    curwin->w_jumplistidx = curwin->w_jumplistlen;
    fm = &curwin->w_jumplist[curwin->w_jumplistlen - 1];

    fm->fmark.mark = curwin->w_pcmark;
    fm->fmark.fnum = curbuf->b_fnum;
    fm->fname = NULL;
#endif
}