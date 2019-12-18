#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  i_nb_samples; } ;
struct TYPE_9__ {TYPE_3__* frame; TYPE_2__ self; } ;
typedef  TYPE_1__ vlc_av_frame_t ;
typedef  TYPE_2__ block_t ;
struct TYPE_11__ {scalar_t__* linesize; int /*<<< orphan*/  nb_samples; int /*<<< orphan*/ * extended_data; } ;
typedef  TYPE_3__ AVFrame ;

/* Variables and functions */
 unsigned int AV_NUM_DATA_POINTERS ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ av_frame_make_writable (TYPE_3__*) ; 
 int /*<<< orphan*/  block_Init (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 TYPE_1__* malloc (int) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_av_frame_cbs ; 

__attribute__((used)) static block_t *vlc_av_frame_Wrap(AVFrame *frame)
{
    for (unsigned i = 1; i < AV_NUM_DATA_POINTERS; i++)
        assert(frame->linesize[i] == 0); /* only packed frame supported */

    if (av_frame_make_writable(frame)) /* TODO: read-only block_t */
        return NULL;

    vlc_av_frame_t *b = malloc(sizeof (*b));
    if (unlikely(b == NULL))
        return NULL;

    block_t *block = &b->self;

    block_Init(block, &vlc_av_frame_cbs,
               frame->extended_data[0], frame->linesize[0]);
    block->i_nb_samples = frame->nb_samples;
    b->frame = frame;
    return block;
}