#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  stream_t ;
typedef  int /*<<< orphan*/  rom1394_directory ;
typedef  int /*<<< orphan*/ * raw1394handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  AVC1394_SUBUNIT_TYPE_VCR ; 
 scalar_t__ ROM1394_NODE_TYPE_AVC ; 
 int /*<<< orphan*/  Raw1394Close (int /*<<< orphan*/ *) ; 
 int Raw1394GetNumPorts (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * Raw1394Open (int /*<<< orphan*/ *,int) ; 
 scalar_t__ avc1394_check_subunit_type (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_Err (int /*<<< orphan*/ *,char*,int) ; 
 int raw1394_get_nodecount (int /*<<< orphan*/ *) ; 
 scalar_t__ rom1394_get_directory (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 scalar_t__ rom1394_get_guid (int /*<<< orphan*/ *,int) ; 
 scalar_t__ rom1394_get_node_type (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int DiscoverAVC( stream_t *p_access, int* port, uint64_t guid )
{
    rom1394_directory rom_dir;
    raw1394handle_t handle = NULL;
    int device = -1;
    int i, j = 0;
    int m = Raw1394GetNumPorts( p_access );

    if( *port >= 0 )
    {
        /* search on explicit port */
        j = *port;
        m = *port + 1;
    }

    for( ; j < m && device == -1; j++ )
    {
        handle = Raw1394Open( p_access, j );
        if( !handle )
            return -1;

        for( i = 0; i < raw1394_get_nodecount( handle ); ++i )
        {
            if( guid != 0 )
            {
                /* select explicitly by GUID */
                if( guid == rom1394_get_guid( handle, i ) )
                {
                    device = i;
                    *port = j;
                    break;
                }
            }
            else
            {
                /* select first AV/C Tape Reccorder Player node */
                if( rom1394_get_directory( handle, i, &rom_dir ) < 0 )
                {
                    msg_Err( p_access, "error reading config rom directory for node %d", i );
                    continue;
                }
                if( ( rom1394_get_node_type( &rom_dir ) == ROM1394_NODE_TYPE_AVC ) &&
                        avc1394_check_subunit_type( handle, i, AVC1394_SUBUNIT_TYPE_VCR ) )
                {
                    device = i;
                    *port = j;
                    break;
                }
            }
        }
        Raw1394Close( handle );
    }

    return device;
}