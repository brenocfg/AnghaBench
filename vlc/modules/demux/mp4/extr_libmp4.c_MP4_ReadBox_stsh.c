#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32_t ;
typedef  int /*<<< orphan*/  stream_t ;
struct TYPE_9__ {size_t* i_shadowed_sample_number; size_t* i_sync_sample_number; size_t i_entry_count; } ;
struct TYPE_7__ {TYPE_5__* p_stsh; TYPE_1__* p_stss; } ;
struct TYPE_8__ {TYPE_2__ data; } ;
struct TYPE_6__ {size_t i_entry_count; } ;
typedef  TYPE_3__ MP4_Box_t ;

/* Variables and functions */
 int /*<<< orphan*/  MP4_Box_data_stsh_t ; 
 int /*<<< orphan*/  MP4_FreeBox_stsh ; 
 int /*<<< orphan*/  MP4_GET4BYTES (size_t) ; 
 int /*<<< orphan*/  MP4_GETVERSIONFLAGS (TYPE_5__*) ; 
 int /*<<< orphan*/  MP4_READBOX_ENTER (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MP4_READBOX_EXIT (int) ; 
 size_t UINT64_C (int) ; 
 size_t i_read ; 
 int /*<<< orphan*/  msg_Dbg (int /*<<< orphan*/ *,char*,size_t) ; 
 void* vlc_alloc (size_t,int) ; 

__attribute__((used)) static int MP4_ReadBox_stsh( stream_t *p_stream, MP4_Box_t *p_box )
{
    uint32_t count;

    MP4_READBOX_ENTER( MP4_Box_data_stsh_t, MP4_FreeBox_stsh );

    MP4_GETVERSIONFLAGS( p_box->data.p_stsh );
    MP4_GET4BYTES( count );

    if( UINT64_C(8) * count > i_read )
        MP4_READBOX_EXIT( 0 );

    p_box->data.p_stsh->i_shadowed_sample_number = vlc_alloc( count,
                                                            sizeof(uint32_t) );
    p_box->data.p_stsh->i_sync_sample_number = vlc_alloc( count,
                                                          sizeof(uint32_t) );
    if( p_box->data.p_stsh->i_shadowed_sample_number == NULL
     || p_box->data.p_stsh->i_sync_sample_number == NULL )
        MP4_READBOX_EXIT( 0 );
    p_box->data.p_stsh->i_entry_count = count;

    for( uint32_t i = 0; i < p_box->data.p_stss->i_entry_count; i++ )
    {
        MP4_GET4BYTES( p_box->data.p_stsh->i_shadowed_sample_number[i] );
        MP4_GET4BYTES( p_box->data.p_stsh->i_sync_sample_number[i] );
    }

#ifdef MP4_VERBOSE
    msg_Dbg( p_stream, "read box: \"stsh\" entry-count %d",
                      p_box->data.p_stsh->i_entry_count );
#endif
    MP4_READBOX_EXIT( 1 );
}