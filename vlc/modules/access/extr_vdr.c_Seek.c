#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct TYPE_6__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ stream_t ;
struct TYPE_7__ {int /*<<< orphan*/  fd; scalar_t__ offset; int /*<<< orphan*/  size; } ;
typedef  TYPE_2__ access_sys_t ;

/* Variables and functions */
 int FILE_COUNT ; 
 scalar_t__ FILE_SIZE (unsigned int) ; 
 int /*<<< orphan*/  FindSeekpoint (TYPE_1__*) ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  SwitchFile (TYPE_1__*,unsigned int) ; 
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 scalar_t__ __MIN (scalar_t__,int /*<<< orphan*/ ) ; 
 int lseek (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int Seek( stream_t *p_access, uint64_t i_pos )
{
    access_sys_t *p_sys = p_access->p_sys;

    /* might happen if called by STREAM_SET_SEEKPOINT */
    i_pos = __MIN( i_pos, p_sys->size );

    p_sys->offset = i_pos;

    /* find correct chapter */
    FindSeekpoint( p_access );

    /* find correct file */
    unsigned i_file = 0;
    while( i_file < FILE_COUNT - 1 &&
           i_pos >= FILE_SIZE( i_file ) )
    {
        i_pos -= FILE_SIZE( i_file );
        i_file++;
    }
    if( !SwitchFile( p_access, i_file ) )
        return VLC_EGENERIC;

    /* adjust position within that file */
    return lseek( p_sys->fd, i_pos, SEEK_SET ) != -1 ?
        VLC_SUCCESS : VLC_EGENERIC;
}