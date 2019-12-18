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
typedef  int /*<<< orphan*/  stream_t ;
struct TYPE_6__ {TYPE_1__* p_sample_text; } ;
struct TYPE_7__ {TYPE_2__ data; int /*<<< orphan*/  i_handler; } ;
struct TYPE_5__ {scalar_t__ i_data; int /*<<< orphan*/  p_data; int /*<<< orphan*/  i_data_reference_index; int /*<<< orphan*/  i_reserved2; int /*<<< orphan*/  i_reserved1; } ;
typedef  TYPE_3__ MP4_Box_t ;

/* Variables and functions */
 int /*<<< orphan*/  ATOM_text ; 
 int /*<<< orphan*/  MP4_Box_data_sample_text_t ; 
 int /*<<< orphan*/  MP4_FreeBox_sample_text ; 
 int /*<<< orphan*/  MP4_GET2BYTES (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MP4_GET4BYTES (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MP4_READBOX_ENTER (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MP4_READBOX_EXIT (int) ; 
 scalar_t__ i_read ; 
 int /*<<< orphan*/  malloc (scalar_t__) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  msg_Dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  p_peek ; 

__attribute__((used)) static int MP4_ReadBox_sample_text( stream_t *p_stream, MP4_Box_t *p_box )
{
    p_box->i_handler = ATOM_text;
    MP4_READBOX_ENTER( MP4_Box_data_sample_text_t, MP4_FreeBox_sample_text );

    MP4_GET4BYTES( p_box->data.p_sample_text->i_reserved1 );
    MP4_GET2BYTES( p_box->data.p_sample_text->i_reserved2 );

    MP4_GET2BYTES( p_box->data.p_sample_text->i_data_reference_index );

    if( i_read )
    {
        p_box->data.p_sample_text->p_data = malloc( i_read );
        if( !p_box->data.p_sample_text->p_data )
            MP4_READBOX_EXIT( 0 );
        memcpy( p_box->data.p_sample_text->p_data, p_peek, i_read );
    }
    p_box->data.p_sample_text->i_data = i_read;

#ifdef MP4_VERBOSE
    msg_Dbg( p_stream, "read box: \"text\" in stsd text" );
#endif
    MP4_READBOX_EXIT( 1 );
}