#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xml_reader_t ;
struct TYPE_5__ {char* psz_node_name; } ;
typedef  TYPE_1__ tt_node_t ;

/* Variables and functions */
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
#define  XML_READER_ENDELEM 129 
 int XML_READER_NONE ; 
#define  XML_READER_STARTELEM 128 
 int /*<<< orphan*/  tt_node_NameCompare (char const*,char*) ; 
 TYPE_1__* tt_node_New (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*) ; 
 int tt_nodes_Read (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int xml_ReaderNextNode (int /*<<< orphan*/ *,char const**) ; 

__attribute__((used)) static int ParseTTMLChunk( xml_reader_t *p_reader, tt_node_t **pp_rootnode )
{
    const char* psz_node_name;

    do
    {
        int i_type = xml_ReaderNextNode( p_reader, &psz_node_name );

        if( i_type <= XML_READER_NONE )
            break;

        switch(i_type)
        {
            default:
                break;

            case XML_READER_STARTELEM:
                if( tt_node_NameCompare( psz_node_name, "tt" ) ||
                    *pp_rootnode != NULL )
                    return VLC_EGENERIC;

                *pp_rootnode = tt_node_New( p_reader, NULL, psz_node_name );
                if( !*pp_rootnode ||
                    tt_nodes_Read( p_reader, *pp_rootnode ) != VLC_SUCCESS )
                    return VLC_EGENERIC;
                break;

            case XML_READER_ENDELEM:
                if( !*pp_rootnode ||
                    tt_node_NameCompare( psz_node_name, (*pp_rootnode)->psz_node_name ) )
                    return VLC_EGENERIC;
                break;
        }

    } while( 1 );

    if( *pp_rootnode == NULL )
        return VLC_EGENERIC;

    return VLC_SUCCESS;
}