#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int rec_type; int /*<<< orphan*/ * ex; } ;
typedef  TYPE_1__ ty_rec_hdr_t ;
struct TYPE_9__ {TYPE_3__* p_sys; } ;
typedef  TYPE_2__ demux_t ;
struct TYPE_11__ {scalar_t__ i_data; } ;
struct TYPE_10__ {TYPE_4__ cc; } ;
typedef  TYPE_3__ demux_sys_t ;
typedef  int /*<<< orphan*/  block_t ;

/* Variables and functions */
 scalar_t__ CC_MAX_DATA_SIZE ; 
 int /*<<< orphan*/  CC_PKT_BYTE0 (int) ; 
 int /*<<< orphan*/  DemuxDecodeXds (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  block_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cc_AppendData (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int DemuxRecCc( demux_t *p_demux, ty_rec_hdr_t *rec_hdr, block_t *p_block_in )
{
    demux_sys_t *p_sys = p_demux->p_sys;
    int i_field;

    if( p_block_in )
        block_Release(p_block_in);

    if( rec_hdr->rec_type == 0x01 )
        i_field = 0;
    else if( rec_hdr->rec_type == 0x02 )
        i_field = 1;
    else
        return 0;

    /* XDS data (extract programs infos) transmitted on field 2 only */
    if( i_field == 1 )
        DemuxDecodeXds( p_demux, rec_hdr->ex[0], rec_hdr->ex[1] );

    if( p_sys->cc.i_data + 3 > CC_MAX_DATA_SIZE )
        return 0;

    cc_AppendData( &p_sys->cc, CC_PKT_BYTE0(i_field), rec_hdr->ex );
    return 0;
}