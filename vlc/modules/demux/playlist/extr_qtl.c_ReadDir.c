#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xml_reader_t ;
struct TYPE_6__ {int /*<<< orphan*/  s; } ;
typedef  TYPE_1__ stream_t ;
typedef  size_t qtl_loop_t ;
typedef  size_t qtl_fullscreen_t ;
typedef  int /*<<< orphan*/  input_item_t ;
typedef  int /*<<< orphan*/  input_item_node_t ;

/* Variables and functions */
 size_t FULLSCREEN_CURRENT ; 
 size_t FULLSCREEN_DOUBLE ; 
 size_t FULLSCREEN_FULL ; 
 size_t FULLSCREEN_HALF ; 
 size_t FULLSCREEN_NORMAL ; 
 size_t LOOP_FALSE ; 
 size_t LOOP_PALINDROME ; 
 size_t LOOP_TRUE ; 
 int ROOT_NODE_MAX_DEPTH ; 
 int /*<<< orphan*/  SADD_INFO (char*,char*) ; 
 scalar_t__ XML_READER_STARTELEM ; 
 char* _ (char*) ; 
 int atoi (char const*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/ * input_item_New (char*,char*) ; 
 int /*<<< orphan*/  input_item_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  input_item_node_AppendItem (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msg_Dbg (TYPE_1__*,char*,...) ; 
 int /*<<< orphan*/  msg_Err (TYPE_1__*,char*) ; 
 int* ppsz_fullscreen ; 
 int* ppsz_loop ; 
 scalar_t__ strcmp (char const*,char*) ; 
 char* strdup (char const*) ; 
 int /*<<< orphan*/  vlc_xml_decode (char*) ; 
 int /*<<< orphan*/ * xml_ReaderCreate (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xml_ReaderDelete (int /*<<< orphan*/ *) ; 
 char* xml_ReaderNextAttr (int /*<<< orphan*/ *,char const**) ; 
 scalar_t__ xml_ReaderNextNode (int /*<<< orphan*/ *,char const**) ; 

__attribute__((used)) static int ReadDir( stream_t *p_demux, input_item_node_t *p_subitems )
{
    xml_reader_t *p_xml_reader;
    input_item_t *p_input;
    int i_ret = -1;

    /* List of all possible attributes. The only required one is "src" */
    bool b_autoplay = false;
    bool b_controller = true;
    qtl_fullscreen_t fullscreen = false;
    char *psz_href = NULL;
    bool b_kioskmode = false;
    qtl_loop_t loop = LOOP_FALSE;
    int i_movieid = -1;
    char *psz_moviename = NULL;
    bool b_playeveryframe = false;
    char *psz_qtnext = NULL;
    bool b_quitwhendone = false;
    char *psz_src = NULL;
    char *psz_mimetype = NULL;
    int i_volume = 100;

    p_xml_reader = xml_ReaderCreate( p_demux, p_demux->s );
    if( !p_xml_reader )
        goto error;

    for( int i = 0;; ++i ) /* locate root node */
    {
        const char *node;
        if( i == ROOT_NODE_MAX_DEPTH ||
            xml_ReaderNextNode( p_xml_reader, &node ) != XML_READER_STARTELEM )
        {
            msg_Err( p_demux, "unable to locate root-node" );
            goto error;
        }

        if( strcmp( node, "embed" ) == 0 )
            break; /* found it */

        msg_Dbg( p_demux, "invalid root node <%s>, trying next (%d / %d)",
                           node, i + 1, ROOT_NODE_MAX_DEPTH );
    }

    const char *attrname, *value;
    while( (attrname = xml_ReaderNextAttr( p_xml_reader, &value )) != NULL )
    {
        if( !strcmp( attrname, "autoplay" ) )
            b_autoplay = !strcmp( value, "true" );
        else if( !strcmp( attrname, "controller" ) )
            b_controller = !strcmp( attrname, "false" );
        else if( !strcmp( attrname, "fullscreen" ) )
        {
            if( !strcmp( value, "double" ) )
                fullscreen = FULLSCREEN_DOUBLE;
            else if( !strcmp( value, "half" ) )
                fullscreen = FULLSCREEN_HALF;
            else if( !strcmp( value, "current" ) )
                fullscreen = FULLSCREEN_CURRENT;
            else if( !strcmp( value, "full" ) )
                fullscreen = FULLSCREEN_FULL;
            else
                fullscreen = FULLSCREEN_NORMAL;
        }
        else if( !strcmp( attrname, "href" ) )
        {
            free( psz_href );
            psz_href = strdup( value );
        }
        else if( !strcmp( attrname, "kioskmode" ) )
            b_kioskmode = !strcmp( value, "true" );
        else if( !strcmp( attrname, "loop" ) )
        {
            if( !strcmp( value, "true" ) )
                loop = LOOP_TRUE;
            else if( !strcmp( value, "palindrome" ) )
                loop = LOOP_PALINDROME;
            else
                loop = LOOP_FALSE;
        }
        else if( !strcmp( attrname, "movieid" ) )
            i_movieid = atoi( value );
        else if( !strcmp( attrname, "moviename" ) )
        {
            free( psz_moviename );
            psz_moviename = strdup( value );
        }
        else if( !strcmp( attrname, "playeveryframe" ) )
            b_playeveryframe = !strcmp( value, "true" );
        else if( !strcmp( attrname, "qtnext" ) )
        {
            free( psz_qtnext );
            psz_qtnext = strdup( value );
        }
        else if( !strcmp( attrname, "quitwhendone" ) )
            b_quitwhendone = !strcmp( value, "true" );
        else if( !strcmp( attrname, "src" ) )
        {
            free( psz_src );
            psz_src = strdup( value );
        }
        else if( !strcmp( attrname, "mimetype" ) )
        {
            free( psz_mimetype );
            psz_mimetype = strdup( value );
        }
        else if( !strcmp( attrname, "volume" ) )
            i_volume = atoi( value );
        else
            msg_Dbg( p_demux, "Attribute %s with value %s isn't valid",
                     attrname, value );
    }

    msg_Dbg( p_demux, "autoplay: %s (unused by VLC)",
             b_autoplay ? "true": "false" );
    msg_Dbg( p_demux, "controller: %s (unused by VLC)",
             b_controller ? "true": "false" );
    msg_Dbg( p_demux, "fullscreen: %s (unused by VLC)",
             ppsz_fullscreen[fullscreen] );
    msg_Dbg( p_demux, "href: %s", psz_href );
    msg_Dbg( p_demux, "kioskmode: %s (unused by VLC)",
             b_kioskmode ? "true":"false" );
    msg_Dbg( p_demux, "loop: %s (unused by VLC)", ppsz_loop[loop] );
    msg_Dbg( p_demux, "movieid: %d (unused by VLC)", i_movieid );
    msg_Dbg( p_demux, "moviename: %s", psz_moviename );
    msg_Dbg( p_demux, "playeverframe: %s (unused by VLC)",
             b_playeveryframe ? "true":"false" );
    msg_Dbg( p_demux, "qtnext: %s", psz_qtnext );
    msg_Dbg( p_demux, "quitwhendone: %s (unused by VLC)",
             b_quitwhendone ? "true":"false" );
    msg_Dbg( p_demux, "src: %s", psz_src );
    msg_Dbg( p_demux, "mimetype: %s", psz_mimetype );
    msg_Dbg( p_demux, "volume: %d (unused by VLC)", i_volume );


    if( !psz_src )
    {
        msg_Err( p_demux, "Mandatory attribute 'src' not found" );
    }
    else
    {
        p_input = input_item_New( psz_src, psz_moviename );
#define SADD_INFO( type, field ) if( field ) { input_item_AddInfo( \
                    p_input, "QuickTime Media Link", type, "%s", field ) ; }
        SADD_INFO( "href", psz_href );
        SADD_INFO( _("Mime"), psz_mimetype );
        input_item_node_AppendItem( p_subitems, p_input );
        input_item_Release( p_input );
        if( psz_qtnext )
        {
            vlc_xml_decode( psz_qtnext );
            p_input = input_item_New( psz_qtnext, NULL );
            input_item_node_AppendItem( p_subitems, p_input );
            input_item_Release( p_input );
        }
    }

    i_ret = 0; /* Needed for correct operation of go back */

error:
    if( p_xml_reader )
        xml_ReaderDelete( p_xml_reader );

    free( psz_href );
    free( psz_moviename );
    free( psz_qtnext );
    free( psz_src );
    free( psz_mimetype );
    return i_ret;
}