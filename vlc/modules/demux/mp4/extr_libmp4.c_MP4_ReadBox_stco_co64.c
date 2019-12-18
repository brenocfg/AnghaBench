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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  size_t uint32_t ;
typedef  int /*<<< orphan*/  stream_t ;
struct TYPE_7__ {size_t* i_chunk_offset; size_t i_entry_count; } ;
struct TYPE_5__ {TYPE_4__* p_co64; } ;
struct TYPE_6__ {scalar_t__ i_type; TYPE_1__ data; } ;
typedef  TYPE_2__ MP4_Box_t ;

/* Variables and functions */
 scalar_t__ ATOM_stco ; 
 int /*<<< orphan*/  MP4_Box_data_co64_t ; 
 int /*<<< orphan*/  MP4_FreeBox_stco_co64 ; 
 int /*<<< orphan*/  MP4_GET4BYTES (size_t) ; 
 int /*<<< orphan*/  MP4_GET8BYTES (size_t) ; 
 int /*<<< orphan*/  MP4_GETVERSIONFLAGS (TYPE_4__*) ; 
 int /*<<< orphan*/  MP4_READBOX_ENTER (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MP4_READBOX_EXIT (int) ; 
 size_t UINT64_C (int) ; 
 size_t i_read ; 
 int /*<<< orphan*/  msg_Dbg (int /*<<< orphan*/ *,char*,size_t) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 size_t* vlc_alloc (size_t,int) ; 

__attribute__((used)) static int MP4_ReadBox_stco_co64( stream_t *p_stream, MP4_Box_t *p_box )
{
    const bool sixtyfour = p_box->i_type != ATOM_stco;
    uint32_t count;

    MP4_READBOX_ENTER( MP4_Box_data_co64_t, MP4_FreeBox_stco_co64 );

    MP4_GETVERSIONFLAGS( p_box->data.p_co64 );
    MP4_GET4BYTES( count );

    if( (sixtyfour ? UINT64_C(8) : UINT64_C(4)) * count > i_read )
        MP4_READBOX_EXIT( 0 );

    p_box->data.p_co64->i_chunk_offset = vlc_alloc( count, sizeof(uint64_t) );
    if( unlikely(p_box->data.p_co64->i_chunk_offset == NULL) )
        MP4_READBOX_EXIT( 0 );
    p_box->data.p_co64->i_entry_count = count;

    for( uint32_t i = 0; i < count; i++ )
    {
        if( sixtyfour )
            MP4_GET8BYTES( p_box->data.p_co64->i_chunk_offset[i] );
        else
            MP4_GET4BYTES( p_box->data.p_co64->i_chunk_offset[i] );
    }

#ifdef MP4_VERBOSE
    msg_Dbg( p_stream, "read box: \"co64\" entry-count %d",
                      p_box->data.p_co64->i_entry_count );

#endif
    MP4_READBOX_EXIT( 1 );
}