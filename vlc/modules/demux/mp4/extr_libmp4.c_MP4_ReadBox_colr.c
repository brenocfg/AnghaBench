#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  stream_t ;
struct TYPE_8__ {TYPE_2__* p_colr; } ;
struct TYPE_9__ {TYPE_3__ data; } ;
struct TYPE_6__ {int /*<<< orphan*/  i_full_range; int /*<<< orphan*/  i_matrix_idx; int /*<<< orphan*/  i_transfer_function_idx; int /*<<< orphan*/  i_primary_idx; } ;
struct TYPE_7__ {scalar_t__ i_type; TYPE_1__ nclc; } ;
typedef  TYPE_4__ MP4_Box_t ;

/* Variables and functions */
 int /*<<< orphan*/  MP4_Box_data_colr_t ; 
 int /*<<< orphan*/  MP4_GET1BYTE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MP4_GET2BYTES (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MP4_GETFOURCC (scalar_t__) ; 
 int /*<<< orphan*/  MP4_READBOX_ENTER (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MP4_READBOX_EXIT (int) ; 
 scalar_t__ VLC_FOURCC (char,char,char,char) ; 
 int /*<<< orphan*/  msg_Warn (int /*<<< orphan*/ *,char*,char*) ; 

__attribute__((used)) static int MP4_ReadBox_colr( stream_t *p_stream, MP4_Box_t *p_box )
{
    MP4_READBOX_ENTER( MP4_Box_data_colr_t, NULL );
    MP4_GETFOURCC( p_box->data.p_colr->i_type );
    if ( p_box->data.p_colr->i_type == VLC_FOURCC( 'n', 'c', 'l', 'c' ) ||
         p_box->data.p_colr->i_type == VLC_FOURCC( 'n', 'c', 'l', 'x' ) )
    {
        MP4_GET2BYTES( p_box->data.p_colr->nclc.i_primary_idx );
        MP4_GET2BYTES( p_box->data.p_colr->nclc.i_transfer_function_idx );
        MP4_GET2BYTES( p_box->data.p_colr->nclc.i_matrix_idx );
        if ( p_box->data.p_colr->i_type == VLC_FOURCC( 'n', 'c', 'l', 'x' ) )
            MP4_GET1BYTE( p_box->data.p_colr->nclc.i_full_range );
    }
    else
    {
#ifdef MP4_VERBOSE
        msg_Warn( p_stream, "Unhandled colr type: %4.4s", (char*)&p_box->data.p_colr->i_type );
#endif
    }
    MP4_READBOX_EXIT( 1 );
}