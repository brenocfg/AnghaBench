#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  stream_t ;
struct TYPE_4__ {scalar_t__ i_size; scalar_t__ i_pos; int /*<<< orphan*/  i_handler; } ;
typedef  TYPE_1__ MP4_Box_t ;

/* Variables and functions */
 int /*<<< orphan*/  ATOM_text ; 
 int /*<<< orphan*/  MP4_Box_data_sample_text_t ; 
 int /*<<< orphan*/  MP4_READBOX_ENTER_PARTIAL (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MP4_READBOX_EXIT (int) ; 
 int /*<<< orphan*/  MP4_ReadBoxContainerChildren (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *) ; 
 scalar_t__ MP4_Seek (int /*<<< orphan*/ *,scalar_t__) ; 
 int i_read ; 
 int /*<<< orphan*/  p_peek ; 

__attribute__((used)) static int MP4_ReadBox_sample_mp4s( stream_t *p_stream, MP4_Box_t *p_box )
{
    p_box->i_handler = ATOM_text;
    MP4_READBOX_ENTER_PARTIAL( MP4_Box_data_sample_text_t, 16, NULL );
    (void) p_peek;
    if( i_read < 8 )
        MP4_READBOX_EXIT( 0 );

    MP4_ReadBoxContainerChildren( p_stream, p_box, NULL );

    if ( MP4_Seek( p_stream, p_box->i_pos + p_box->i_size ) )
        MP4_READBOX_EXIT( 0 );

    MP4_READBOX_EXIT( 1 );
}