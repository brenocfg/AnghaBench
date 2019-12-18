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
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_10__ {int /*<<< orphan*/  pf_control; int /*<<< orphan*/  pf_seek; int /*<<< orphan*/  pf_read; TYPE_3__* p_sys; TYPE_1__* s; } ;
typedef  TYPE_2__ stream_t ;
struct TYPE_11__ {int /*<<< orphan*/  cache; } ;
typedef  TYPE_3__ stream_sys_t ;
struct TYPE_9__ {int /*<<< orphan*/ * pf_block; } ;

/* Variables and functions */
 int /*<<< orphan*/  AStreamControl ; 
 int /*<<< orphan*/  AStreamPrebufferBlock (TYPE_2__*) ; 
 int /*<<< orphan*/  AStreamReadBlock ; 
 int /*<<< orphan*/  AStreamSeekBlock ; 
 int VLC_EGENERIC ; 
 int VLC_ENOMEM ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  block_BytestreamInit (int /*<<< orphan*/ *) ; 
 scalar_t__ block_BytestreamRemaining (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (TYPE_3__*) ; 
 TYPE_3__* malloc (int) ; 
 int /*<<< orphan*/  msg_Dbg (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  msg_Err (TYPE_2__*,char*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int Open(vlc_object_t *obj)
{
    stream_t *s = (stream_t *)obj;

    if (s->s->pf_block == NULL)
        return VLC_EGENERIC;

    stream_sys_t *sys = malloc(sizeof (*sys));
    if (unlikely(sys == NULL))
        return VLC_ENOMEM;

    msg_Dbg(s, "Using block method for AStream*");

    /* Init all fields of sys->block */
    block_BytestreamInit( &sys->cache );

    s->p_sys = sys;
    /* Do the prebuffering */
    AStreamPrebufferBlock(s);

    if (block_BytestreamRemaining( &sys->cache ) <= 0)
    {
        msg_Err(s, "cannot pre fill buffer");
        free(sys);
        return VLC_EGENERIC;
    }

    s->pf_read = AStreamReadBlock;
    s->pf_seek = AStreamSeekBlock;
    s->pf_control = AStreamControl;
    return VLC_SUCCESS;
}