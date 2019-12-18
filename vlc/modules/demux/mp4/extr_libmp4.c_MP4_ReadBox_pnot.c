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
typedef  scalar_t__ uint16_t ;
typedef  int /*<<< orphan*/  stream_t ;
struct TYPE_6__ {TYPE_1__* p_pnot; } ;
struct TYPE_7__ {int i_size; TYPE_2__ data; } ;
struct TYPE_5__ {scalar_t__ i_index; int /*<<< orphan*/  i_type; int /*<<< orphan*/  i_date; } ;
typedef  TYPE_3__ MP4_Box_t ;

/* Variables and functions */
 int /*<<< orphan*/  MP4_Box_data_pnot_t ; 
 int /*<<< orphan*/  MP4_GET2BYTES (scalar_t__) ; 
 int /*<<< orphan*/  MP4_GET4BYTES (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MP4_GETFOURCC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MP4_READBOX_ENTER (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MP4_READBOX_EXIT (int) ; 

__attribute__((used)) static int MP4_ReadBox_pnot( stream_t *p_stream, MP4_Box_t *p_box )
{
    if ( p_box->i_size != 20 )
        return 0;
    MP4_READBOX_ENTER( MP4_Box_data_pnot_t, NULL );
    MP4_GET4BYTES( p_box->data.p_pnot->i_date );
    uint16_t i_version;
    MP4_GET2BYTES( i_version );
    if ( i_version != 0 )
        MP4_READBOX_EXIT( 0 );
    MP4_GETFOURCC( p_box->data.p_pnot->i_type );
    MP4_GET2BYTES( p_box->data.p_pnot->i_index );
    MP4_READBOX_EXIT( 1 );
}