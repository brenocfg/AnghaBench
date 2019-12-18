#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  stream_t ;
struct TYPE_7__ {TYPE_1__* p_sample_vide; } ;
struct TYPE_8__ {scalar_t__ i_type; int i_pos; TYPE_2__ data; int /*<<< orphan*/  i_handler; } ;
struct TYPE_6__ {int i_qt_image_description; scalar_t__* sz_compressorname; int /*<<< orphan*/  i_depth; int /*<<< orphan*/  i_height; int /*<<< orphan*/  i_width; int /*<<< orphan*/  i_qt_color_table; int /*<<< orphan*/  i_qt_frame_count; int /*<<< orphan*/  i_qt_data_size; int /*<<< orphan*/  i_vertresolution; int /*<<< orphan*/  i_horizresolution; int /*<<< orphan*/  i_qt_spatial_quality; int /*<<< orphan*/  i_qt_temporal_quality; int /*<<< orphan*/  i_qt_vendor; int /*<<< orphan*/  i_qt_revision_level; int /*<<< orphan*/  i_qt_version; scalar_t__** p_qt_image_description; int /*<<< orphan*/  i_data_reference_index; int /*<<< orphan*/ * i_reserved1; } ;
typedef  TYPE_3__ MP4_Box_t ;

/* Variables and functions */
 scalar_t__ ATOM_drmi ; 
 int /*<<< orphan*/  ATOM_vide ; 
 int /*<<< orphan*/  MP4_Box_data_sample_vide_t ; 
 int /*<<< orphan*/  MP4_FreeBox_sample_vide ; 
 int /*<<< orphan*/  MP4_GET1BYTE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MP4_GET2BYTES (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MP4_GET4BYTES (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MP4_READBOX_ENTER (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MP4_READBOX_EXIT (int) ; 
 int /*<<< orphan*/  MP4_ReadBoxContainerRawInBox (int /*<<< orphan*/ *,TYPE_3__*,int*,int,int) ; 
 int header_size ; 
 int i_read ; 
 scalar_t__** malloc (int) ; 
 int /*<<< orphan*/  memcpy (scalar_t__**,int*,int) ; 
 int /*<<< orphan*/  msg_Dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  msg_Warn (int /*<<< orphan*/ *,char*) ; 
 int* p_buff ; 
 int* p_peek ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

int MP4_ReadBox_sample_vide( stream_t *p_stream, MP4_Box_t *p_box )
{
    p_box->i_handler = ATOM_vide;
    MP4_READBOX_ENTER( MP4_Box_data_sample_vide_t, MP4_FreeBox_sample_vide );

    size_t i_actually_read = i_read + header_size;

    for( unsigned i = 0; i < 6 ; i++ )
    {
        MP4_GET1BYTE( p_box->data.p_sample_vide->i_reserved1[i] );
    }

    MP4_GET2BYTES( p_box->data.p_sample_vide->i_data_reference_index );

    /*
     * XXX hack -> produce a copy of the nearly complete chunk
     */
    if( i_read > 0 )
    {
        p_box->data.p_sample_vide->p_qt_image_description = malloc( i_read );
        if( unlikely( p_box->data.p_sample_vide->p_qt_image_description == NULL ) )
            MP4_READBOX_EXIT( 0 );
        p_box->data.p_sample_vide->i_qt_image_description = i_read;
        memcpy( p_box->data.p_sample_vide->p_qt_image_description,
                p_peek, i_read );
    }
    else
    {
        p_box->data.p_sample_vide->i_qt_image_description = 0;
        p_box->data.p_sample_vide->p_qt_image_description = NULL;
    }

    MP4_GET2BYTES( p_box->data.p_sample_vide->i_qt_version );
    MP4_GET2BYTES( p_box->data.p_sample_vide->i_qt_revision_level );
    MP4_GET4BYTES( p_box->data.p_sample_vide->i_qt_vendor );

    MP4_GET4BYTES( p_box->data.p_sample_vide->i_qt_temporal_quality );
    MP4_GET4BYTES( p_box->data.p_sample_vide->i_qt_spatial_quality );

    MP4_GET2BYTES( p_box->data.p_sample_vide->i_width );
    MP4_GET2BYTES( p_box->data.p_sample_vide->i_height );

    MP4_GET4BYTES( p_box->data.p_sample_vide->i_horizresolution );
    MP4_GET4BYTES( p_box->data.p_sample_vide->i_vertresolution );

    MP4_GET4BYTES( p_box->data.p_sample_vide->i_qt_data_size );
    MP4_GET2BYTES( p_box->data.p_sample_vide->i_qt_frame_count );

    if ( i_read < 32 )
        MP4_READBOX_EXIT( 0 );
    if( p_peek[0] <= 31 ) // Must be Pascal String
    {
        memcpy( &p_box->data.p_sample_vide->sz_compressorname, &p_peek[1], p_peek[0] );
        p_box->data.p_sample_vide->sz_compressorname[p_peek[0]] = 0;
    }
    p_peek += 32; i_read -= 32;

    MP4_GET2BYTES( p_box->data.p_sample_vide->i_depth );
    MP4_GET2BYTES( p_box->data.p_sample_vide->i_qt_color_table );

    if( p_box->i_type == ATOM_drmi )
    {
        msg_Warn( p_stream, "DRM protected streams are not supported." );
        MP4_READBOX_EXIT( 0 );
    }

    if( i_actually_read > 78 && p_peek - p_buff > 78 )
    {
        MP4_ReadBoxContainerRawInBox( p_stream, p_box, p_peek, i_read,
                                      p_box->i_pos + p_peek - p_buff );
    }

#ifdef MP4_VERBOSE
    msg_Dbg( p_stream, "read box: \"vide\" in stsd %dx%d depth %d (%s)",
                      p_box->data.p_sample_vide->i_width,
                      p_box->data.p_sample_vide->i_height,
                      p_box->data.p_sample_vide->i_depth,
                      p_box->data.p_sample_vide->sz_compressorname );

#endif
    MP4_READBOX_EXIT( 1 );
}