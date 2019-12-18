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
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_6__ {size_t i_buffer; scalar_t__ p_buffer; } ;
typedef  TYPE_1__ block_t ;
struct TYPE_7__ {size_t i_write; size_t i_data; int /*<<< orphan*/  lock; int /*<<< orphan*/  p_dsbuffer; int /*<<< orphan*/  format; int /*<<< orphan*/  chan_table; int /*<<< orphan*/  chans_to_reorder; } ;
typedef  TYPE_2__ aout_stream_sys_t ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 scalar_t__ DSERR_BUFFERLOST ; 
 size_t DS_BUF_SIZE ; 
 scalar_t__ DS_OK ; 
 scalar_t__ IDirectSoundBuffer_Lock (int /*<<< orphan*/ ,size_t,size_t,void**,unsigned long*,void**,unsigned long*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDirectSoundBuffer_Restore (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDirectSoundBuffer_Unlock (int /*<<< orphan*/ ,void*,unsigned long,void*,unsigned long) ; 
 int /*<<< orphan*/  aout_ChannelReorder (scalar_t__,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  block_Release (TYPE_1__*) ; 
 int /*<<< orphan*/  memcpy (void*,scalar_t__,unsigned long) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  msg_Err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  msg_Warn (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static HRESULT FillBuffer( vlc_object_t *obj, aout_stream_sys_t *p_sys,
                           block_t *p_buffer )
{
    size_t towrite = (p_buffer != NULL) ? p_buffer->i_buffer : DS_BUF_SIZE;
    void *p_write_position, *p_wrap_around;
    unsigned long l_bytes1, l_bytes2;
    HRESULT dsresult;

    vlc_mutex_lock( &p_sys->lock );

    /* Before copying anything, we have to lock the buffer */
    dsresult = IDirectSoundBuffer_Lock(
           p_sys->p_dsbuffer,    /* DS buffer */
           p_sys->i_write,       /* Start offset */
           towrite,                /* Number of bytes */
           &p_write_position,    /* Address of lock start */
           &l_bytes1,            /* Count of bytes locked before wrap around */
           &p_wrap_around,       /* Buffer address (if wrap around) */
           &l_bytes2,            /* Count of bytes after wrap around */
           0 );                  /* Flags: DSBLOCK_FROMWRITECURSOR is buggy */
    if( dsresult == DSERR_BUFFERLOST )
    {
        IDirectSoundBuffer_Restore( p_sys->p_dsbuffer );
        dsresult = IDirectSoundBuffer_Lock(
                               p_sys->p_dsbuffer,
                               p_sys->i_write,
                               towrite,
                               &p_write_position,
                               &l_bytes1,
                               &p_wrap_around,
                               &l_bytes2,
                               0 );
    }
    if( dsresult != DS_OK )
    {
        msg_Warn( obj, "cannot lock buffer" );
        if( p_buffer != NULL )
            block_Release( p_buffer );
        vlc_mutex_unlock( &p_sys->lock );
        return dsresult;
    }

    if( p_buffer == NULL )
    {
        memset( p_write_position, 0, l_bytes1 );
        memset( p_wrap_around, 0, l_bytes2 );
    }
    else
    {
        if( p_sys->chans_to_reorder ) /* Do the channel reordering here */
            aout_ChannelReorder( p_buffer->p_buffer, p_buffer->i_buffer,
                                 p_sys->chans_to_reorder, p_sys->chan_table,
                                 p_sys->format );

        memcpy( p_write_position, p_buffer->p_buffer, l_bytes1 );
        if( p_wrap_around && l_bytes2 )
            memcpy( p_wrap_around, p_buffer->p_buffer + l_bytes1, l_bytes2 );

        if( unlikely( ( l_bytes1 + l_bytes2 ) < p_buffer->i_buffer ) )
            msg_Err( obj, "Buffer overrun");

        block_Release( p_buffer );
    }

    /* Now the data has been copied, unlock the buffer */
    IDirectSoundBuffer_Unlock( p_sys->p_dsbuffer, p_write_position, l_bytes1,
                               p_wrap_around, l_bytes2 );

    p_sys->i_write += towrite;
    p_sys->i_write %= DS_BUF_SIZE;
    p_sys->i_data += towrite;
    vlc_mutex_unlock( &p_sys->lock );

    return DS_OK;
}