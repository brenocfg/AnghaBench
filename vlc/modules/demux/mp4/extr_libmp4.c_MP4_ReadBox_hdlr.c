#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint8_t ;
typedef  int /*<<< orphan*/  stream_t ;
typedef  int /*<<< orphan*/  int32_t ;
struct TYPE_7__ {scalar_t__ i_predefined; scalar_t__ i_handler_type; size_t* psz_name; } ;
struct TYPE_5__ {TYPE_4__* p_hdlr; } ;
struct TYPE_6__ {TYPE_1__ data; } ;
typedef  TYPE_2__ MP4_Box_t ;

/* Variables and functions */
 int /*<<< orphan*/  MP4_Box_data_hdlr_t ; 
 int /*<<< orphan*/  MP4_FreeBox_hdlr ; 
 int /*<<< orphan*/  MP4_GET1BYTE (size_t) ; 
 int /*<<< orphan*/  MP4_GET4BYTES (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MP4_GETFOURCC (scalar_t__) ; 
 int /*<<< orphan*/  MP4_GETVERSIONFLAGS (TYPE_4__*) ; 
 int /*<<< orphan*/  MP4_READBOX_ENTER (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MP4_READBOX_EXIT (int) ; 
 size_t SSIZE_MAX ; 
 scalar_t__ VLC_FOURCC (char,char,char,char) ; 
 int /*<<< orphan*/  VLC_UNUSED (int /*<<< orphan*/ ) ; 
 size_t i_read ; 
 size_t* malloc (size_t) ; 
 int /*<<< orphan*/  memcpy (size_t*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  msg_Dbg (int /*<<< orphan*/ *,char*,char*,char*) ; 
 int /*<<< orphan*/  p_peek ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int MP4_ReadBox_hdlr( stream_t *p_stream, MP4_Box_t *p_box )
{
    int32_t i_reserved;
    VLC_UNUSED(i_reserved);

    MP4_READBOX_ENTER( MP4_Box_data_hdlr_t, MP4_FreeBox_hdlr );

    MP4_GETVERSIONFLAGS( p_box->data.p_hdlr );

    MP4_GETFOURCC( p_box->data.p_hdlr->i_predefined );
    MP4_GETFOURCC( p_box->data.p_hdlr->i_handler_type );

    MP4_GET4BYTES( i_reserved );
    MP4_GET4BYTES( i_reserved );
    MP4_GET4BYTES( i_reserved );
    p_box->data.p_hdlr->psz_name = NULL;

    if( i_read >= SSIZE_MAX )
        MP4_READBOX_EXIT( 0 );

    if( i_read > 0 )
    {
        size_t i_copy;

        /* Yes, I love .mp4 :( */
        if( p_box->data.p_hdlr->i_predefined == VLC_FOURCC( 'm', 'h', 'l', 'r' ) )
        {
            uint8_t i_len;

            MP4_GET1BYTE( i_len );
            i_copy = (i_len <= i_read) ? i_len : i_read;
        }
        else
            i_copy = i_read;

        uint8_t *psz = p_box->data.p_hdlr->psz_name = malloc( i_copy + 1 );
        if( unlikely( psz == NULL ) )
            MP4_READBOX_EXIT( 0 );

        memcpy( psz, p_peek, i_copy );
        p_box->data.p_hdlr->psz_name[i_copy] = '\0';
    }

#ifdef MP4_VERBOSE
        msg_Dbg( p_stream, "read box: \"hdlr\" handler type: \"%4.4s\" name: \"%s\"",
                   (char*)&p_box->data.p_hdlr->i_handler_type,
                   p_box->data.p_hdlr->psz_name );

#endif
    MP4_READBOX_EXIT( 1 );
}