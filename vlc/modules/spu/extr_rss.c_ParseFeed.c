#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xml_reader_t ;
struct TYPE_6__ {char* psz_title; char* psz_link; char* psz_description; } ;
typedef  TYPE_1__ rss_item_t ;
struct TYPE_7__ {int i_items; char* psz_link; char* psz_image; char* psz_title; char* psz_description; TYPE_3__* p_items; } ;
typedef  TYPE_2__ rss_feed_t ;
typedef  int /*<<< orphan*/  filter_t ;
struct TYPE_8__ {int /*<<< orphan*/ * psz_link; int /*<<< orphan*/ * psz_description; int /*<<< orphan*/ * psz_title; } ;

/* Variables and functions */
 int /*<<< orphan*/  FREENULL (char*) ; 
 int /*<<< orphan*/  VLC_UNUSED (int /*<<< orphan*/ *) ; 
#define  XML_READER_ENDELEM 130 
#define  XML_READER_STARTELEM 129 
#define  XML_READER_TEXT 128 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  msg_Dbg (int /*<<< orphan*/ *,char*,char const*) ; 
 char* removeWhiteChars (char const*) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 char* strdup (char const*) ; 
 int /*<<< orphan*/  unlikely (int) ; 
 char* xml_ReaderNextAttr (int /*<<< orphan*/ *,char const**) ; 
 int xml_ReaderNextNode (int /*<<< orphan*/ *,char const**) ; 
 TYPE_3__* xrealloc (TYPE_3__*,int) ; 

__attribute__((used)) static bool ParseFeed( filter_t *p_filter, xml_reader_t *p_xml_reader,
                      rss_feed_t *p_feed )
{
    VLC_UNUSED(p_filter);
    const char *node;
    char *psz_eltname = NULL;

    bool b_is_item = false;
    bool b_is_image = false;

    int i_item = 0;
    int type;

    while( (type = xml_ReaderNextNode( p_xml_reader, &node )) > 0 )
    {
        switch( type )
        {
        case XML_READER_STARTELEM:
#ifdef RSS_DEBUG
            msg_Dbg( p_filter, "element <%s>", node );
#endif
            free(psz_eltname);
            psz_eltname = strdup( node );
            if( unlikely(!psz_eltname) )
                goto end;

            /* rss or atom */
            if( !strcmp( node, "item" ) || !strcmp( node, "entry" ) )
            {
                b_is_item = true;
                p_feed->i_items++;
                p_feed->p_items = xrealloc( p_feed->p_items,
                                     p_feed->i_items * sizeof( rss_item_t ) );
                p_feed->p_items[p_feed->i_items-1].psz_title = NULL;
                p_feed->p_items[p_feed->i_items-1].psz_description = NULL;
                p_feed->p_items[p_feed->i_items-1].psz_link = NULL;
            }
            /* rss */
            else if( !strcmp( node, "image" ) )
            {
                b_is_image = true;
            }
            /* atom */
            else if( !strcmp( node, "link" ) )
            {
                const char *name, *value;
                char *psz_href = NULL;
                char *psz_rel = NULL;

                while( (name = xml_ReaderNextAttr( p_xml_reader, &value )) != NULL )
                {
                    if( !strcmp( name, "rel" ) )
                    {
                        free( psz_rel );
                        psz_rel = strdup( value );
                    }
                    else if( !strcmp( name, "href" ) )
                    {
                        free( psz_href );
                        psz_href = strdup( value );
                    }
                }

                /* "rel" and "href" must be defined */
                if( psz_rel && psz_href )
                {
                    if( !strcmp( psz_rel, "alternate" ) && !b_is_item &&
                        !b_is_image && !p_feed->psz_link )
                    {
                        p_feed->psz_link = psz_href;
                    }
                    /* this isn't in the rfc but i found some ... */
                    else if( ( !strcmp( psz_rel, "logo" ) ||
                               !strcmp( psz_rel, "icon" ) )
                             && !b_is_item && !b_is_image
                             && !p_feed->psz_image )
                    {
                        p_feed->psz_image = psz_href;
                    }
                    else
                    {
                        free( psz_href );
                    }
                }
                else
                {
                    free( psz_href );
                }
                free( psz_rel );
            }
            break;

        case XML_READER_ENDELEM:
            FREENULL( psz_eltname );
#ifdef RSS_DEBUG
            msg_Dbg( p_filter, "element end </%s>", node );
#endif
            /* rss or atom */
            if( !strcmp( node, "item" ) || !strcmp( node, "entry" ) )
            {
                b_is_item = false;
                i_item++;
            }
            /* rss */
            else if( !strcmp( node, "image" ) )
            {
                b_is_image = false;
            }
            break;

        case XML_READER_TEXT:
        {
            if( !psz_eltname )
                break;

            char *psz_eltvalue = removeWhiteChars( node );

#ifdef RSS_DEBUG
            msg_Dbg( p_filter, "  text : \"%s\"", psz_eltvalue );
#endif
            /* Is it an item ? */
            if( b_is_item )
            {
                rss_item_t *p_item = p_feed->p_items+i_item;
                /* rss/atom */
                if( !strcmp( psz_eltname, "title" ) && !p_item->psz_title )
                {
                    p_item->psz_title = psz_eltvalue;
                }
                else if( !strcmp( psz_eltname, "link" ) /* rss */
                         && !p_item->psz_link )
                {
                    p_item->psz_link = psz_eltvalue;
                }
                /* rss/atom */
                else if( ( !strcmp( psz_eltname, "description" ) ||
                           !strcmp( psz_eltname, "summary" ) )
                          && !p_item->psz_description )
                {
                    p_item->psz_description = psz_eltvalue;
                }
                else
                {
                    free( psz_eltvalue );
                }
            }
            /* Is it an image ? */
            else if( b_is_image )
            {
                if( !strcmp( psz_eltname, "url" ) && !p_feed->psz_image )
                    p_feed->psz_image = psz_eltvalue;
                else
                    free( psz_eltvalue );
            }
            else
            {
                /* rss/atom */
                if( !strcmp( psz_eltname, "title" ) && !p_feed->psz_title )
                {
                    p_feed->psz_title = psz_eltvalue;
                }
                /* rss */
                else if( !strcmp( psz_eltname, "link" ) && !p_feed->psz_link )
                {
                    p_feed->psz_link = psz_eltvalue;
                }
                /* rss ad atom */
                else if( ( !strcmp( psz_eltname, "description" ) ||
                           !strcmp( psz_eltname, "subtitle" ) )
                         && !p_feed->psz_description )
                {
                    p_feed->psz_description = psz_eltvalue;
                }
                /* rss */
                else if( ( !strcmp( psz_eltname, "logo" ) ||
                           !strcmp( psz_eltname, "icon" ) )
                         && !p_feed->psz_image )
                {
                    p_feed->psz_image = psz_eltvalue;
                }
                else
                {
                    free( psz_eltvalue );
                }
            }
            break;
        }
        }
    }

    free( psz_eltname );
    return true;

end:
    return false;
}