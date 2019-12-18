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
struct TYPE_7__ {int /*<<< orphan*/  identifier; int /*<<< orphan*/  source; TYPE_2__* p_sys; } ;
typedef  TYPE_1__ stream_extractor_t ;
struct TYPE_8__ {int b_dead; int b_eof; scalar_t__ i_offset; } ;
typedef  TYPE_2__ private_sys_t ;

/* Variables and functions */
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 scalar_t__ archive_clean (TYPE_2__*) ; 
 scalar_t__ archive_init (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ archive_seek_subentry (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ vlc_stream_Seek (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int archive_extractor_reset( stream_extractor_t* p_extractor )
{
    private_sys_t* p_sys = p_extractor->p_sys;

    if( vlc_stream_Seek( p_extractor->source, 0 )
        || archive_clean( p_sys )
        || archive_init( p_sys, p_extractor->source )
        || archive_seek_subentry( p_sys, p_extractor->identifier ) )
    {
        p_sys->b_dead = true;
        return VLC_EGENERIC;
    }

    p_sys->i_offset = 0;
    p_sys->b_eof = false;
    p_sys->b_dead = false;
    return VLC_SUCCESS;
}