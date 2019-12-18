#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_5__ {int /*<<< orphan*/  s; TYPE_2__* p_sys; } ;
typedef  TYPE_1__ stream_t ;
struct TYPE_6__ {int /*<<< orphan*/  cache; } ;
typedef  TYPE_2__ stream_sys_t ;

/* Variables and functions */
 scalar_t__ AStreamRefillBlock (TYPE_1__*) ; 
 int VLC_EGENERIC ; 
 scalar_t__ VLC_SUCCESS ; 
 int /*<<< orphan*/  block_BytestreamEmpty (int /*<<< orphan*/ *) ; 
 scalar_t__ block_SkipBytes (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ vlc_stream_Seek (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int AStreamSeekBlock(stream_t *s, uint64_t i_pos)
{
    stream_sys_t *sys = s->p_sys;

    if( block_SkipBytes( &sys->cache, i_pos) == VLC_SUCCESS )
        return VLC_SUCCESS;

    /* Not enought bytes, empty and seek */
    /* Do the access seek */
    if (vlc_stream_Seek(s->s, i_pos)) return VLC_EGENERIC;

    block_BytestreamEmpty( &sys->cache );

    /* Refill a block */
    if (AStreamRefillBlock(s))
        return VLC_EGENERIC;

    return VLC_SUCCESS;
}