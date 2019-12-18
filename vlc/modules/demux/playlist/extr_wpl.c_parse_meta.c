#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xml_reader_t ;
struct TYPE_4__ {int /*<<< orphan*/ * p_sys; } ;
typedef  TYPE_1__ stream_t ;
typedef  int /*<<< orphan*/  input_item_t ;

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  atoll (char*) ; 
 int /*<<< orphan*/  consume_tag (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  input_item_AddInfo (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_item_SetGenre (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  input_item_SetPublisher (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  input_item_SetRating (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  msg_Warn (TYPE_1__*,char*,char*) ; 
 int /*<<< orphan*/  strcasecmp (char const*,char*) ; 
 char* strdup (char const*) ; 
 int xml_ReaderIsEmptyElement (int /*<<< orphan*/ *) ; 
 char* xml_ReaderNextAttr (int /*<<< orphan*/ *,char const**) ; 

__attribute__((used)) static void parse_meta( stream_t* p_demux, input_item_t* p_input )
{
    xml_reader_t *p_reader = p_demux->p_sys;
    bool const b_empty = xml_ReaderIsEmptyElement( p_reader ) == 1;

    char *psz_meta_name = NULL, *psz_meta_content = NULL;
    char const *psz_attr, *psz_value;
    while( ( psz_attr = xml_ReaderNextAttr( p_reader, &psz_value ) ) )
    {
        if( psz_value == NULL )
            continue;

        if( !strcasecmp( psz_attr, "name" ) && !psz_meta_name )
            psz_meta_name = strdup( psz_value );
        else
            if( !strcasecmp( psz_attr, "content" ) && !psz_meta_content )
                psz_meta_content = strdup( psz_value );

        if( psz_meta_name && psz_meta_content )
            break;
    }

    if( b_empty == false )
        consume_tag( p_reader, "meta" );

    if( !psz_meta_name || !psz_meta_content )
        goto done;

    if( !strcasecmp( psz_meta_name, "TotalDuration" ) )
        input_item_AddInfo( p_input, _("Playlist"), _("Total duration"),
                            "%lld", atoll( psz_meta_content ) );
    else
        if( !strcasecmp( psz_meta_name, "Author" ) )
            input_item_SetPublisher( p_input, psz_meta_content );
    else
        if( !strcasecmp( psz_meta_name, "Rating" ) )
            input_item_SetRating( p_input, psz_meta_content );
    else
        if( !strcasecmp( psz_meta_name, "Genre" ) )
            input_item_SetGenre( p_input, psz_meta_content );
    else
        msg_Warn( p_demux, "ignoring unknown meta-attribute %s", psz_meta_name );

done:
    free( psz_meta_name );
    free( psz_meta_content );
}