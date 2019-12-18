#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xml_reader_t ;
struct TYPE_3__ {int /*<<< orphan*/ * p_sys; } ;
typedef  TYPE_1__ stream_t ;
typedef  int /*<<< orphan*/  input_item_t ;

/* Variables and functions */
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 scalar_t__ XML_READER_TEXT ; 
 int /*<<< orphan*/  consume_tag (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  input_item_SetTitle (int /*<<< orphan*/ *,char const*) ; 
 scalar_t__ xml_ReaderIsEmptyElement (int /*<<< orphan*/ *) ; 
 scalar_t__ xml_ReaderNextNode (int /*<<< orphan*/ *,char const**) ; 

__attribute__((used)) static int parse_title_element( stream_t* p_demux, input_item_t* p_input )
{
    xml_reader_t *p_reader = p_demux->p_sys;
    char const* psz_title;

    if( xml_ReaderIsEmptyElement( p_reader ) )
        return VLC_SUCCESS;

    if( xml_ReaderNextNode( p_reader, &psz_title ) != XML_READER_TEXT )
        return VLC_EGENERIC;

    input_item_SetTitle( p_input, psz_title );

    consume_tag( p_reader, "title" );
    return VLC_SUCCESS;
}