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
typedef  int /*<<< orphan*/  vlc_family_t ;
typedef  int /*<<< orphan*/  filter_t ;

/* Variables and functions */
 int /*<<< orphan*/  ANDROID_FONT_PATH ; 
 int /*<<< orphan*/  NewFont (char*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *) ; 
 int VLC_EGENERIC ; 
 int VLC_ENOMEM ; 
 int VLC_SUCCESS ; 
 int XML_READER_TEXT ; 
 scalar_t__ asprintf (char**,char*,int /*<<< orphan*/ ,char const*) ; 
 int atoi (char const*) ; 
 int /*<<< orphan*/  msg_Warn (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  strcasecmp (char*,char const*) ; 
 char* xml_ReaderNextAttr (int /*<<< orphan*/ *,char const**) ; 
 int xml_ReaderNextNode (int /*<<< orphan*/ *,char const**) ; 

__attribute__((used)) static int Android_ParseFont( filter_t *p_filter, xml_reader_t *p_xml,
                              vlc_family_t *p_family )
{
    bool              b_bold      = false;
    bool              b_italic    = false;
    const char       *psz_val     = NULL;
    const char       *psz_attr    = NULL;
    int               i_type      = 0;
    int               i_weight    = 0;

    while( ( psz_attr = xml_ReaderNextAttr( p_xml, &psz_val ) ) )
    {
        if( !strcasecmp( "weight", psz_attr ) && psz_val && *psz_val )
            i_weight = atoi( psz_val );
        else if( !strcasecmp( "style", psz_attr ) && psz_val && *psz_val )
            if( !strcasecmp( "italic", psz_val ) )
                b_italic = true;
    }

    if( i_weight == 700 )
        b_bold = true;

    i_type = xml_ReaderNextNode( p_xml, &psz_val );

    if( i_type != XML_READER_TEXT || !psz_val || !*psz_val )
    {
        msg_Warn( p_filter, "Android_ParseFont: no file name" );
        return VLC_EGENERIC;
    }

    char *psz_fontfile;

    /*
     * We don't need all font weights. Only 400 (regular) and 700 (bold)
     */
    if( i_weight == 400 || i_weight == 700 )
        if( asprintf( &psz_fontfile, "%s/%s", ANDROID_FONT_PATH, psz_val ) < 0
         || !NewFont( psz_fontfile, 0, b_bold, b_italic, p_family ) )
            return VLC_ENOMEM;

    return VLC_SUCCESS;
}