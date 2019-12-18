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
struct TYPE_7__ {scalar_t__ i_balance; scalar_t__ i_reserved; } ;
struct TYPE_5__ {TYPE_4__* p_smhd; } ;
struct TYPE_6__ {TYPE_1__ data; } ;
typedef  TYPE_2__ MP4_Box_t ;

/* Variables and functions */
 int /*<<< orphan*/  MP4_Box_data_smhd_t ; 
 int /*<<< orphan*/  MP4_GET2BYTES (scalar_t__) ; 
 int /*<<< orphan*/  MP4_GETVERSIONFLAGS (TYPE_4__*) ; 
 int /*<<< orphan*/  MP4_READBOX_ENTER (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MP4_READBOX_EXIT (int) ; 
 int /*<<< orphan*/  msg_Dbg (int /*<<< orphan*/ *,char*,float) ; 

__attribute__((used)) static int MP4_ReadBox_smhd( stream_t *p_stream, MP4_Box_t *p_box )
{
    MP4_READBOX_ENTER( MP4_Box_data_smhd_t, NULL );

    MP4_GETVERSIONFLAGS( p_box->data.p_smhd );



    MP4_GET2BYTES( p_box->data.p_smhd->i_balance );

    MP4_GET2BYTES( p_box->data.p_smhd->i_reserved );

#ifdef MP4_VERBOSE
    msg_Dbg( p_stream, "read box: \"smhd\" balance %f",
                      (float)p_box->data.p_smhd->i_balance / 256 );
#endif
    MP4_READBOX_EXIT( 1 );
}