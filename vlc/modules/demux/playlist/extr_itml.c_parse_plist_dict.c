#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xml_reader_t ;
typedef  char const xml_elem_hnd_t ;
typedef  char const track_elem_t ;
typedef  int /*<<< orphan*/  stream_t ;
typedef  int /*<<< orphan*/  input_item_node_t ;
struct TYPE_2__ {int /*<<< orphan*/ * member_0; int /*<<< orphan*/  cmplx; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMPLEX_CONTENT ; 
 int /*<<< orphan*/  SIMPLE_CONTENT ; 
 int /*<<< orphan*/  UNKNOWN_CONTENT ; 
 int /*<<< orphan*/  VLC_UNUSED (char const*) ; 
 int parse_dict (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,char const*) ; 
 int /*<<< orphan*/  parse_tracks_dict ; 

__attribute__((used)) static bool parse_plist_dict( stream_t *p_demux, input_item_node_t *p_input_node,
                              track_elem_t *p_track, xml_reader_t *p_xml_reader,
                              const char *psz_element,
                              xml_elem_hnd_t *p_handlers )
{
    VLC_UNUSED(p_track); VLC_UNUSED(psz_element); VLC_UNUSED(p_handlers);
    xml_elem_hnd_t pl_elements[] =
        { {"dict",    COMPLEX_CONTENT, {.cmplx = parse_tracks_dict} },
          {"array",   SIMPLE_CONTENT,  {NULL} },
          {"key",     SIMPLE_CONTENT,  {NULL} },
          {"integer", SIMPLE_CONTENT,  {NULL} },
          {"string",  SIMPLE_CONTENT,  {NULL} },
          {"date",    SIMPLE_CONTENT,  {NULL} },
          {"true",    SIMPLE_CONTENT,  {NULL} },
          {"false",   SIMPLE_CONTENT,  {NULL} },
          {NULL,      UNKNOWN_CONTENT, {NULL} }
        };

    return parse_dict( p_demux, p_input_node, NULL, p_xml_reader,
                       "dict", pl_elements );
}