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
typedef  char const track_elem_t ;
typedef  int /*<<< orphan*/  stream_t ;
typedef  int /*<<< orphan*/  input_item_node_t ;

/* Variables and functions */
 int /*<<< orphan*/  VLC_UNUSED (char const*) ; 
 int /*<<< orphan*/  msg_Warn (int /*<<< orphan*/ *,char*,...) ; 
 int parse_dict (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 char* xml_ReaderNextAttr (int /*<<< orphan*/ *,char const**) ; 

__attribute__((used)) static bool parse_plist_node( stream_t *p_demux, input_item_node_t *p_input_node,
                              track_elem_t *p_track, xml_reader_t *p_xml_reader,
                              const char *psz_element,
                              xml_elem_hnd_t *p_handlers )
{
    VLC_UNUSED(p_track); VLC_UNUSED(psz_element);
    const char *attr, *value;
    bool b_version_found = false;

    /* read all playlist attributes */
    while( (attr = xml_ReaderNextAttr( p_xml_reader, &value )) != NULL )
    {
        /* attribute: version */
        if( !strcmp( attr, "version" ) )
        {
            b_version_found = true;
            if( strcmp( value, "1.0" ) )
                msg_Warn( p_demux, "unsupported iTunes Media Library version" );
        }
        /* unknown attribute */
        else
            msg_Warn( p_demux, "invalid <plist> attribute:\"%s\"", attr );
    }

    /* attribute version is mandatory !!! */
    if( !b_version_found )
        msg_Warn( p_demux, "<plist> requires \"version\" attribute" );

    return parse_dict( p_demux, p_input_node, NULL, p_xml_reader,
                       "plist", p_handlers );
}