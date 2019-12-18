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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  tt_node_t ;
typedef  int /*<<< orphan*/  stream_t ;
typedef  int /*<<< orphan*/  decoder_t ;

/* Variables and functions */
 scalar_t__ ParseTTMLChunk (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 scalar_t__ VLC_SUCCESS ; 
 int /*<<< orphan*/  tt_node_RecursiveDelete (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_stream_Delete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * vlc_stream_MemoryNew (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t,int) ; 
 int /*<<< orphan*/ * xml_ReaderCreate (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xml_ReaderDelete (int /*<<< orphan*/ *) ; 

__attribute__((used)) static tt_node_t *ParseTTML( decoder_t *p_dec, const uint8_t *p_buffer, size_t i_buffer )
{
    stream_t*       p_sub;
    xml_reader_t*   p_xml_reader;

    p_sub = vlc_stream_MemoryNew( p_dec, (uint8_t*) p_buffer, i_buffer, true );
    if( unlikely( p_sub == NULL ) )
        return NULL;

    p_xml_reader = xml_ReaderCreate( p_dec, p_sub );
    if( unlikely( p_xml_reader == NULL ) )
    {
        vlc_stream_Delete( p_sub );
        return NULL;
    }

    tt_node_t *p_rootnode = NULL;
    if( ParseTTMLChunk( p_xml_reader, &p_rootnode ) != VLC_SUCCESS )
    {
        if( p_rootnode )
            tt_node_RecursiveDelete( p_rootnode );
        p_rootnode = NULL;
    }

    xml_ReaderDelete( p_xml_reader );
    vlc_stream_Delete( p_sub );

    return p_rootnode;
}