#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_tick_t ;
typedef  int ssize_t ;
struct TYPE_11__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ sout_access_out_t ;
struct TYPE_12__ {size_t stuffing_size; int /*<<< orphan*/  i_handle; int /*<<< orphan*/  aes_ctx; int /*<<< orphan*/ * stuffing_bytes; scalar_t__ key_uri; int /*<<< orphan*/  current_segment_length; TYPE_3__* full_segments; TYPE_3__** full_segments_end; } ;
typedef  TYPE_2__ sout_access_out_sys_t ;
typedef  scalar_t__ gcry_error_t ;
struct TYPE_13__ {size_t i_buffer; int /*<<< orphan*/ * p_buffer; struct TYPE_13__* p_next; } ;
typedef  TYPE_3__ block_t ;

/* Variables and functions */
 scalar_t__ EINTR ; 
 int VLC_ENOMEM ; 
 int /*<<< orphan*/  block_ChainProperties (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_3__* block_Realloc (TYPE_3__*,size_t,size_t) ; 
 int /*<<< orphan*/  block_Release (TYPE_3__*) ; 
 scalar_t__ errno ; 
 scalar_t__ gcry_cipher_encrypt (int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpg_strerror (scalar_t__) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  msg_Dbg (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  msg_Err (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 
 int vlc_write (int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static ssize_t writeSegment( sout_access_out_t *p_access )
{
    sout_access_out_sys_t *p_sys = p_access->p_sys;
    msg_Dbg( p_access, "Writing all full segments" );

    block_t *output = p_sys->full_segments;
    p_sys->full_segments = NULL;
    p_sys->full_segments_end = &p_sys->full_segments;

    vlc_tick_t current_length = 0;
    block_ChainProperties( output, NULL, NULL, &current_length );

    ssize_t i_write=0;
    bool crypted = false;
    p_sys->current_segment_length = current_length;
    while( output )
    {
        if( p_sys->key_uri && !crypted )
        {
            if( p_sys->stuffing_size )
            {
                output = block_Realloc( output, p_sys->stuffing_size, output->i_buffer );
                if( unlikely(!output ) )
                    return VLC_ENOMEM;
                memcpy( output->p_buffer, p_sys->stuffing_bytes, p_sys->stuffing_size );
                p_sys->stuffing_size = 0;
            }
            size_t original = output->i_buffer;
            size_t padded = (output->i_buffer + 15 ) & ~15;
            size_t pad = padded - original;
            if( pad )
            {
                p_sys->stuffing_size = 16-pad;
                output->i_buffer -= p_sys->stuffing_size;
                memcpy(p_sys->stuffing_bytes, &output->p_buffer[output->i_buffer], p_sys->stuffing_size);
            }

            gcry_error_t err = gcry_cipher_encrypt( p_sys->aes_ctx,
                                output->p_buffer, output->i_buffer, NULL, 0 );
            if( err )
            {
                msg_Err( p_access, "Encryption failure: %s ", gpg_strerror(err) );
                return -1;
            }
            crypted=true;

        }

        ssize_t val = vlc_write( p_sys->i_handle, output->p_buffer, output->i_buffer );
        if ( val == -1 )
        {
           if ( errno == EINTR )
              continue;
           return -1;
        }


        if ( (size_t)val >= output->i_buffer )
        {
           block_t *p_next = output->p_next;
           block_Release (output);
           output = p_next;
           crypted=false;
        }
        else
        {
           output->p_buffer += val;
           output->i_buffer -= val;
        }
        i_write += val;
    }
    return i_write;
}