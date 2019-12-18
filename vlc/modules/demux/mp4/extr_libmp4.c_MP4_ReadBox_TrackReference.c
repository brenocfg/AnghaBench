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
typedef  unsigned int uint32_t ;
typedef  int /*<<< orphan*/  stream_t ;
struct TYPE_6__ {TYPE_1__* p_track_reference; } ;
struct TYPE_7__ {TYPE_2__ data; } ;
struct TYPE_5__ {unsigned int i_entry_count; int /*<<< orphan*/ * i_track_ID; } ;
typedef  TYPE_3__ MP4_Box_t ;

/* Variables and functions */
 int /*<<< orphan*/  MP4_Box_data_trak_reference_t ; 
 int /*<<< orphan*/  MP4_FreeBox_TrackReference ; 
 int /*<<< orphan*/  MP4_GET4BYTES (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MP4_READBOX_ENTER (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MP4_READBOX_EXIT (int) ; 
 int i_read ; 
 int /*<<< orphan*/  msg_Dbg (int /*<<< orphan*/ *,char*,unsigned int) ; 
 int /*<<< orphan*/ * vlc_alloc (unsigned int,int) ; 

__attribute__((used)) static int MP4_ReadBox_TrackReference( stream_t *p_stream, MP4_Box_t *p_box )
{
    uint32_t count;

    MP4_READBOX_ENTER( MP4_Box_data_trak_reference_t, MP4_FreeBox_TrackReference );

    p_box->data.p_track_reference->i_track_ID = NULL;
    count = i_read / sizeof(uint32_t);
    p_box->data.p_track_reference->i_entry_count = count;
    p_box->data.p_track_reference->i_track_ID = vlc_alloc( count,
                                                        sizeof(uint32_t) );
    if( p_box->data.p_track_reference->i_track_ID == NULL )
        MP4_READBOX_EXIT( 0 );

    for( unsigned i = 0; i < count; i++ )
    {
        MP4_GET4BYTES( p_box->data.p_track_reference->i_track_ID[i] );
    }
#ifdef MP4_VERBOSE
        msg_Dbg( p_stream, "read box: \"chap\" %d references",
                 p_box->data.p_track_reference->i_entry_count );
#endif

    MP4_READBOX_EXIT( 1 );
}