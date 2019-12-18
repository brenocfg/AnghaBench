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
typedef  int /*<<< orphan*/  xml_reader_t ;
typedef  int /*<<< orphan*/  xml_elem_hnd_t ;
typedef  int /*<<< orphan*/  track_elem_t ;
typedef  int /*<<< orphan*/  stream_t ;
typedef  int /*<<< orphan*/  input_item_node_t ;

/* Variables and functions */
 int /*<<< orphan*/  VLC_UNUSED (int /*<<< orphan*/ *) ; 
 int XML_READER_ENDELEM ; 
 int /*<<< orphan*/  strcmp (char const*,char const*) ; 
 int xml_ReaderNextNode (int /*<<< orphan*/ *,char const**) ; 

__attribute__((used)) static bool skip_element( stream_t *p_demux, input_item_node_t *p_input_node,
                          track_elem_t *p_track, xml_reader_t *p_xml_reader,
                          const char *psz_element, xml_elem_hnd_t *p_handlers )
{
    VLC_UNUSED(p_demux); VLC_UNUSED(p_input_node);
    VLC_UNUSED(p_track); VLC_UNUSED(p_handlers);
    const char *node;
    int type;

    while( (type = xml_ReaderNextNode( p_xml_reader, &node )) > 0 )
        if( type == XML_READER_ENDELEM && !strcmp( psz_element, node ) )
            return true;
    return false;
}