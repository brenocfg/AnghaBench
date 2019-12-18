#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xml_reader_t ;
typedef  int /*<<< orphan*/  stream_t ;
struct TYPE_7__ {int /*<<< orphan*/  i_extra; int /*<<< orphan*/  p_extra; } ;
struct TYPE_8__ {TYPE_1__ fmt_in; } ;
typedef  TYPE_2__ decoder_t ;

/* Variables and functions */
 int /*<<< orphan*/  ParseUSFHeaderTags (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VLC_OBJECT (TYPE_2__*) ; 
 scalar_t__ XML_READER_STARTELEM ; 
 scalar_t__ likely (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcasecmp (char*,char const*) ; 
 int /*<<< orphan*/  vlc_stream_Delete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * vlc_stream_MemoryNew (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * xml_ReaderCreate (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xml_ReaderDelete (int /*<<< orphan*/ *) ; 
 scalar_t__ xml_ReaderNextNode (int /*<<< orphan*/ *,char const**) ; 

__attribute__((used)) static void ParseUSFHeader( decoder_t *p_dec )
{
    stream_t      *p_sub = NULL;
    xml_reader_t  *p_xml_reader = NULL;

    p_sub = vlc_stream_MemoryNew( VLC_OBJECT(p_dec),
                              p_dec->fmt_in.p_extra,
                              p_dec->fmt_in.i_extra,
                              true );
    if( !p_sub )
        return;

    p_xml_reader = xml_ReaderCreate( p_dec, p_sub );
    if( likely(p_xml_reader) )
    {
        const char *node;

        /* Look for Root Node */
        if( xml_ReaderNextNode( p_xml_reader, &node ) == XML_READER_STARTELEM
         && !strcasecmp( "usfsubtitles", node ) )
            ParseUSFHeaderTags( p_dec, p_xml_reader );

        xml_ReaderDelete( p_xml_reader );
    }
    vlc_stream_Delete( p_sub );
}