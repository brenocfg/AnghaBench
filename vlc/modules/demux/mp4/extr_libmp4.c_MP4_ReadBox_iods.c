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
typedef  int /*<<< orphan*/  stream_t ;
struct TYPE_7__ {int i_object_descriptor; char i_OD_profile_level; char i_scene_profile_level; char i_audio_profile_level; char i_visual_profile_level; char i_graphics_profile_level; } ;
struct TYPE_5__ {TYPE_4__* p_iods; } ;
struct TYPE_6__ {TYPE_1__ data; } ;
typedef  TYPE_2__ MP4_Box_t ;

/* Variables and functions */
 int /*<<< orphan*/  MP4_Box_data_iods_t ; 
 int /*<<< orphan*/  MP4_GET1BYTE (char) ; 
 int /*<<< orphan*/  MP4_GET2BYTES (int) ; 
 int /*<<< orphan*/  MP4_GETVERSIONFLAGS (TYPE_4__*) ; 
 int /*<<< orphan*/  MP4_READBOX_ENTER (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MP4_READBOX_EXIT (int) ; 
 int /*<<< orphan*/  VLC_UNUSED (char) ; 
 int /*<<< orphan*/  msg_Dbg (int /*<<< orphan*/ *,char*,int,char,char,char,char,char) ; 

__attribute__((used)) static int MP4_ReadBox_iods( stream_t *p_stream, MP4_Box_t *p_box )
{
    char i_unused;
    VLC_UNUSED(i_unused);

    MP4_READBOX_ENTER( MP4_Box_data_iods_t, NULL );
    MP4_GETVERSIONFLAGS( p_box->data.p_iods );

    MP4_GET1BYTE( i_unused ); /* tag */
    MP4_GET1BYTE( i_unused ); /* length */

    MP4_GET2BYTES( p_box->data.p_iods->i_object_descriptor ); /* 10bits, 6 other bits
                                                              are used for other flags */
    MP4_GET1BYTE( p_box->data.p_iods->i_OD_profile_level );
    MP4_GET1BYTE( p_box->data.p_iods->i_scene_profile_level );
    MP4_GET1BYTE( p_box->data.p_iods->i_audio_profile_level );
    MP4_GET1BYTE( p_box->data.p_iods->i_visual_profile_level );
    MP4_GET1BYTE( p_box->data.p_iods->i_graphics_profile_level );

#ifdef MP4_VERBOSE
    msg_Dbg( p_stream,
             "read box: \"iods\" objectDescriptorId: %i, OD: %i, scene: %i, audio: %i, "
             "visual: %i, graphics: %i",
             p_box->data.p_iods->i_object_descriptor >> 6,
             p_box->data.p_iods->i_OD_profile_level,
             p_box->data.p_iods->i_scene_profile_level,
             p_box->data.p_iods->i_audio_profile_level,
             p_box->data.p_iods->i_visual_profile_level,
             p_box->data.p_iods->i_graphics_profile_level );
#endif

    MP4_READBOX_EXIT( 1 );
}