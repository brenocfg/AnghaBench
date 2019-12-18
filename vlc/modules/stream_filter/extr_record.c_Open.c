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
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_6__ {int /*<<< orphan*/  pf_control; int /*<<< orphan*/  pf_seek; int /*<<< orphan*/  pf_read; TYPE_3__* p_sys; TYPE_1__* s; } ;
typedef  TYPE_2__ stream_t ;
struct TYPE_7__ {int /*<<< orphan*/ * f; } ;
typedef  TYPE_3__ stream_sys_t ;
struct TYPE_5__ {int /*<<< orphan*/ * pf_readdir; } ;

/* Variables and functions */
 int /*<<< orphan*/  Control ; 
 int /*<<< orphan*/  Read ; 
 int /*<<< orphan*/  Seek ; 
 int VLC_EGENERIC ; 
 int VLC_ENOMEM ; 
 int VLC_SUCCESS ; 
 TYPE_3__* malloc (int) ; 

__attribute__((used)) static int Open ( vlc_object_t *p_this )
{
    stream_t *s = (stream_t*)p_this;
    stream_sys_t *p_sys;

    if( s->s->pf_readdir != NULL )
        return VLC_EGENERIC;

    /* */
    s->p_sys = p_sys = malloc( sizeof( *p_sys ) );
    if( !p_sys )
        return VLC_ENOMEM;

    p_sys->f = NULL;

    /* */
    s->pf_read = Read;
    s->pf_seek = Seek;
    s->pf_control = Control;

    return VLC_SUCCESS;
}