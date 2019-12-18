#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xml_reader_t ;
struct TYPE_12__ {char* psz_name; int /*<<< orphan*/  p_fonts; } ;
typedef  TYPE_1__ vlc_family_t ;
typedef  int /*<<< orphan*/  vlc_dictionary_t ;
struct TYPE_13__ {TYPE_3__* p_sys; } ;
typedef  TYPE_2__ filter_t ;
struct TYPE_14__ {int /*<<< orphan*/  fallback_map; int /*<<< orphan*/  family_map; int /*<<< orphan*/  p_families; } ;
typedef  TYPE_3__ filter_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  ANDROID_FONT_PATH ; 
 int /*<<< orphan*/ * FB_LIST_DEFAULT ; 
 int /*<<< orphan*/  FB_NAME ; 
 TYPE_1__* NewFamily (TYPE_2__*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NewFont (char*,int /*<<< orphan*/ ,int,int,TYPE_1__*) ; 
 char* ToLower (char const*) ; 
 int VLC_EGENERIC ; 
 int VLC_ENOMEM ; 
 int VLC_SUCCESS ; 
#define  XML_READER_ENDELEM 129 
#define  XML_READER_STARTELEM 128 
 int XML_READER_TEXT ; 
 int /*<<< orphan*/  asprintf (char**,char*,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  free (char*) ; 
 TYPE_1__* kVLCDictionaryNotFound ; 
 int /*<<< orphan*/  msg_Warn (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  strcasecmp (char*,char const*) ; 
 int /*<<< orphan*/  strcasestr (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlikely (int) ; 
 int /*<<< orphan*/  vlc_dictionary_insert (int /*<<< orphan*/ *,char*,TYPE_1__*) ; 
 TYPE_1__* vlc_dictionary_value_for_key (int /*<<< orphan*/ *,char*) ; 
 int xml_ReaderNextNode (int /*<<< orphan*/ *,char const**) ; 

__attribute__((used)) static int Android_Legacy_ParseFamily( filter_t *p_filter, xml_reader_t *p_xml )
{
    filter_sys_t     *p_sys       = p_filter->p_sys;
    vlc_dictionary_t *p_dict      = &p_sys->family_map;
    vlc_family_t     *p_family    = NULL;
    char             *psz_lc      = NULL;
    int               i_counter   = 0;
    bool              b_bold      = false;
    bool              b_italic    = false;
    const char       *p_node      = NULL;
    int               i_type      = 0;

    while( ( i_type = xml_ReaderNextNode( p_xml, &p_node ) ) > 0 )
    {
        switch( i_type )
        {
        case XML_READER_STARTELEM:
            /*
             * Multiple names can reference the same family in Android. When
             * the first name is encountered we set p_family to the vlc_family_t
             * in the master list matching this name, and if no such family
             * exists we create a new one and add it to the master list.
             * If the master list does contain a family with that name it's one
             * of the font attachments, and the family will end up having embedded
             * fonts and system fonts.
             */
            if( !strcasecmp( "name", p_node ) )
            {
                i_type = xml_ReaderNextNode( p_xml, &p_node );

                if( i_type != XML_READER_TEXT || !p_node || !*p_node )
                {
                    msg_Warn( p_filter, "Android_ParseFamily: empty name" );
                    continue;
                }

                psz_lc = ToLower( p_node );
                if( unlikely( !psz_lc ) )
                    return VLC_ENOMEM;

                if( !p_family )
                {
                    p_family = vlc_dictionary_value_for_key( p_dict, psz_lc );
                    if( p_family == kVLCDictionaryNotFound )
                    {
                        p_family =
                            NewFamily( p_filter, psz_lc, &p_sys->p_families, NULL, NULL );

                        if( unlikely( !p_family ) )
                        {
                            free( psz_lc );
                            return VLC_ENOMEM;
                        }

                    }
                }

                if( vlc_dictionary_value_for_key( p_dict, psz_lc ) == kVLCDictionaryNotFound )
                    vlc_dictionary_insert( p_dict, psz_lc, p_family );
                free( psz_lc );
            }
            /*
             * If p_family has not been set by the time we encounter the first file,
             * it means this family has no name, and should be used only as a fallback.
             * We create a new family for it in the master list with the name "fallback-xxxx"
             * and later add it to the "default" fallback list.
             */
            else if( !strcasecmp( "file", p_node ) )
            {
                i_type = xml_ReaderNextNode( p_xml, &p_node );

                if( i_type != XML_READER_TEXT || !p_node || !*p_node )
                {
                    ++i_counter;
                    continue;
                }

                if( !p_family )
                    p_family = NewFamily( p_filter, NULL, &p_sys->p_families,
                                          &p_sys->family_map, NULL );

                if( unlikely( !p_family ) )
                    return VLC_ENOMEM;

                switch( i_counter )
                {
                case 0:
                    b_bold = false;
                    b_italic = false;
                    break;
                case 1:
                    b_bold = true;
                    b_italic = false;
                    break;
                case 2:
                    b_bold = false;
                    b_italic = true;
                    break;
                case 3:
                    b_bold = true;
                    b_italic = true;
                    break;
                default:
                    msg_Warn( p_filter, "Android_ParseFamily: too many files" );
                    return VLC_EGENERIC;
                }

                char *psz_fontfile = NULL;
                if( asprintf( &psz_fontfile, "%s/%s", ANDROID_FONT_PATH, p_node ) < 0
                 || !NewFont( psz_fontfile, 0, b_bold, b_italic, p_family ) )
                    return VLC_ENOMEM;

                ++i_counter;
            }
            break;

        case XML_READER_ENDELEM:
            if( !strcasecmp( "family", p_node ) )
            {
                if( !p_family )
                {
                    msg_Warn( p_filter, "Android_ParseFamily: empty family" );
                    return VLC_EGENERIC;
                }

                /*
                 * If the family name has "fallback" in it, add it to the
                 * "default" fallback list.
                 */
                if( strcasestr( p_family->psz_name, FB_NAME ) )
                {
                    vlc_family_t *p_fallback =
                        NewFamily( p_filter, p_family->psz_name,
                                   NULL, &p_sys->fallback_map, FB_LIST_DEFAULT );

                    if( unlikely( !p_fallback ) )
                        return VLC_ENOMEM;

                    p_fallback->p_fonts = p_family->p_fonts;
                }

                return VLC_SUCCESS;
            }
            break;
        }
    }

    msg_Warn( p_filter, "Android_ParseOldFamily: Corrupt font configuration file" );
    return VLC_EGENERIC;
}