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
struct TYPE_6__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ demux_t ;
struct TYPE_7__ {TYPE_3__* p_rootnode; int /*<<< orphan*/  p_reader; } ;
typedef  TYPE_2__ demux_sys_t ;
struct TYPE_8__ {char* psz_node_name; } ;

/* Variables and functions */
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
#define  XML_READER_ENDELEM 129 
 int XML_READER_NONE ; 
#define  XML_READER_STARTELEM 128 
 int /*<<< orphan*/  tt_node_NameCompare (char const*,char*) ; 
 TYPE_3__* tt_node_New (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char const*) ; 
 int tt_nodes_Read (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int xml_ReaderIsEmptyElement (int /*<<< orphan*/ ) ; 
 int xml_ReaderNextNode (int /*<<< orphan*/ ,char const**) ; 

__attribute__((used)) static int ReadTTML( demux_t* p_demux )
{
    demux_sys_t* p_sys = p_demux->p_sys;
    const char* psz_node_name;

    do
    {
        int i_type = xml_ReaderNextNode( p_sys->p_reader, &psz_node_name );
        bool b_empty = xml_ReaderIsEmptyElement( p_sys->p_reader );

        if( i_type <= XML_READER_NONE )
            break;

        switch(i_type)
        {
            default:
                break;

            case XML_READER_STARTELEM:
                if( tt_node_NameCompare( psz_node_name, "tt" ) ||
                    p_sys->p_rootnode != NULL )
                    return VLC_EGENERIC;

                p_sys->p_rootnode = tt_node_New( p_sys->p_reader, NULL, psz_node_name );
                if( b_empty )
                    break;
                if( !p_sys->p_rootnode ||
                    tt_nodes_Read( p_sys->p_reader, p_sys->p_rootnode ) != VLC_SUCCESS )
                    return VLC_EGENERIC;
                break;

            case XML_READER_ENDELEM:
                if( !p_sys->p_rootnode ||
                    tt_node_NameCompare( psz_node_name, p_sys->p_rootnode->psz_node_name ) )
                    return VLC_EGENERIC;
                break;
        }

    } while( 1 );

    if( p_sys->p_rootnode == NULL )
        return VLC_EGENERIC;

    return VLC_SUCCESS;
}