#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_7__ {int position; scalar_t__ time; scalar_t__ length; } ;
struct TYPE_8__ {int /*<<< orphan*/  lock; int /*<<< orphan*/ * writer; int /*<<< orphan*/  reader; int /*<<< orphan*/  thread; int /*<<< orphan*/  name; int /*<<< orphan*/ * out; TYPE_1__ stats; } ;
typedef  TYPE_2__ vlc_demux_chained_t ;
typedef  int /*<<< orphan*/  es_out_t ;

/* Variables and functions */
 int /*<<< orphan*/  VLC_THREAD_PRIORITY_INPUT ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 TYPE_2__* malloc (scalar_t__) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ strlen (char const*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 scalar_t__ vlc_clone (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_demux_chained_Thread ; 
 int /*<<< orphan*/  vlc_mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_stream_Delete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_stream_fifo_Close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * vlc_stream_fifo_New (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

vlc_demux_chained_t *vlc_demux_chained_New(vlc_object_t *parent,
                                           const char *name, es_out_t *out)
{
    vlc_demux_chained_t *dc = malloc(sizeof (*dc) + strlen(name) + 1);
    if (unlikely(dc == NULL))
        return NULL;

    dc->writer = vlc_stream_fifo_New(parent, &dc->reader);
    if (dc->writer == NULL)
    {
        free(dc);
        return NULL;
    }

    dc->stats.position = 0.;
    dc->stats.length = 0;
    dc->stats.time = 0;
    dc->out = out;
    strcpy(dc->name, name);

    vlc_mutex_init(&dc->lock);

    if (vlc_clone(&dc->thread, vlc_demux_chained_Thread, dc,
                  VLC_THREAD_PRIORITY_INPUT))
    {
        vlc_stream_Delete(dc->reader);
        vlc_stream_fifo_Close(dc->writer);
        vlc_mutex_destroy(&dc->lock);
        free(dc);
        dc = NULL;
    }
    return dc;
}