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
struct vlc_stream_fifo {int eof; int /*<<< orphan*/ * fifo; } ;
typedef  struct vlc_stream_fifo vlc_stream_fifo_t ;
typedef  int /*<<< orphan*/  vlc_object_t ;
struct vlc_stream_fifo_private {struct vlc_stream_fifo* writer; } ;
struct TYPE_5__ {int /*<<< orphan*/  pf_control; int /*<<< orphan*/ * pf_seek; int /*<<< orphan*/  pf_block; } ;
typedef  TYPE_1__ stream_t ;

/* Variables and functions */
 int /*<<< orphan*/ * block_FifoNew () ; 
 int /*<<< orphan*/  block_FifoRelease (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (struct vlc_stream_fifo*) ; 
 struct vlc_stream_fifo* malloc (int) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 TYPE_1__* vlc_stream_CustomNew (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,char*) ; 
 struct vlc_stream_fifo_private* vlc_stream_Private (TYPE_1__*) ; 
 int /*<<< orphan*/  vlc_stream_fifo_Block ; 
 int /*<<< orphan*/  vlc_stream_fifo_Control ; 
 int /*<<< orphan*/  vlc_stream_fifo_Destroy ; 

vlc_stream_fifo_t *vlc_stream_fifo_New(vlc_object_t *parent, stream_t **reader)
{
    struct vlc_stream_fifo *writer = malloc(sizeof (*writer));
    if (unlikely(writer == NULL))
        return NULL;

    writer->fifo = block_FifoNew();
    if (unlikely(writer->fifo == NULL)) {
        free(writer);
        return NULL;
    }
    writer->eof = false;

    struct vlc_stream_fifo_private *sys;
    stream_t *s = vlc_stream_CustomNew(parent, vlc_stream_fifo_Destroy,
                                       sizeof (*sys), "stream");
    if (unlikely(s == NULL)) {
        block_FifoRelease(writer->fifo);
        free(writer);
        return NULL;
    }

    sys = vlc_stream_Private(s);
    sys->writer = writer;
    s->pf_block = vlc_stream_fifo_Block;
    s->pf_seek = NULL;
    s->pf_control = vlc_stream_fifo_Control;
    *reader = s;
    return writer;
}