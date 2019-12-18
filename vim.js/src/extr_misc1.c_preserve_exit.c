#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* ml_mfp; } ;
struct TYPE_7__ {TYPE_2__ b_ml; struct TYPE_7__* b_next; } ;
typedef  TYPE_3__ buf_T ;
struct TYPE_5__ {int /*<<< orphan*/ * mf_fname; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  IObuff ; 
 int /*<<< orphan*/  OUT_STR (char*) ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_3__* firstbuf ; 
 int /*<<< orphan*/  getout (int) ; 
 int /*<<< orphan*/  ml_close_all (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ml_close_notmod () ; 
 int /*<<< orphan*/  ml_sync_all (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  out_flush () ; 
 int /*<<< orphan*/  out_str (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  prepare_to_exit () ; 
 int /*<<< orphan*/  really_exiting ; 
 int /*<<< orphan*/  screen_start () ; 

void
preserve_exit()
{
    buf_T	*buf;

    prepare_to_exit();

    /* Setting this will prevent free() calls.  That avoids calling free()
     * recursively when free() was invoked with a bad pointer. */
    really_exiting = TRUE;

    out_str(IObuff);
    screen_start();		    /* don't know where cursor is now */
    out_flush();

    ml_close_notmod();		    /* close all not-modified buffers */

    for (buf = firstbuf; buf != NULL; buf = buf->b_next)
    {
	if (buf->b_ml.ml_mfp != NULL && buf->b_ml.ml_mfp->mf_fname != NULL)
	{
	    OUT_STR("Vim: preserving files...\n");
	    screen_start();	    /* don't know where cursor is now */
	    out_flush();
	    ml_sync_all(FALSE, FALSE);	/* preserve all swap files */
	    break;
	}
    }

    ml_close_all(FALSE);	    /* close all memfiles, without deleting */

    OUT_STR("Vim: Finished.\n");

    getout(1);
}