#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xml_reader_t ;
struct TYPE_7__ {int /*<<< orphan*/ * p_sys; } ;
typedef  TYPE_1__ stream_t ;
typedef  int /*<<< orphan*/  input_item_t ;

/* Variables and functions */
 int XML_READER_ENDELEM ; 
 int XML_READER_STARTELEM ; 
 int /*<<< orphan*/  consume_volatile_tag (TYPE_1__*,char const*) ; 
 int /*<<< orphan*/  msg_Warn (TYPE_1__*,char*,char const*) ; 
 int /*<<< orphan*/  parse_meta (TYPE_1__*,int /*<<< orphan*/ *) ; 
 scalar_t__ parse_title_element (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcasecmp (char const*,char*) ; 
 int xml_ReaderNextNode (int /*<<< orphan*/ *,char const**) ; 

__attribute__((used)) static void read_head( stream_t* p_demux, input_item_t* p_input )
{
    xml_reader_t *p_reader = p_demux->p_sys;
    char const* psz_name;
    int i_type;

    while( ( i_type = xml_ReaderNextNode( p_reader, &psz_name ) ) > 0 )
    {
        if( i_type == XML_READER_ENDELEM && !strcasecmp( psz_name, "head" ) )
            break;

        if( i_type == XML_READER_STARTELEM )
        {
            if( !strcasecmp( psz_name, "meta" ) )
            {
                parse_meta( p_demux, p_input );
                continue;
            }

            if( !strcasecmp( psz_name, "title" ) )
            {
                if( parse_title_element( p_demux, p_input ) )
                    break;
                continue;
            }

            msg_Warn( p_demux, "skipping unknown tag <%s> in <head>", psz_name );
            consume_volatile_tag( p_demux, psz_name );
        }
    }
}