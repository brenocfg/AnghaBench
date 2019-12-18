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
struct TYPE_3__ {char* psz_fontname; unsigned int i_background_alpha; unsigned int i_font_alpha; int i_features; unsigned int i_font_color; unsigned int i_background_color; unsigned int i_outline_color; unsigned int i_outline_alpha; int i_outline_width; int /*<<< orphan*/  i_style_flags; } ;
typedef  TYPE_1__ text_style_t ;

/* Variables and functions */
 int /*<<< orphan*/  STYLE_BACKGROUND ; 
 int /*<<< orphan*/  STYLE_BOLD ; 
 int STYLE_HAS_BACKGROUND_ALPHA ; 
 int STYLE_HAS_BACKGROUND_COLOR ; 
 int STYLE_HAS_FLAGS ; 
 int STYLE_HAS_FONT_ALPHA ; 
 int STYLE_HAS_FONT_COLOR ; 
 int /*<<< orphan*/  STYLE_ITALIC ; 
 int /*<<< orphan*/  STYLE_STRIKEOUT ; 
 int /*<<< orphan*/  STYLE_UNDERLINE ; 
 void* atoi (char const*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  strcasecmp (char*,char const*) ; 
 void* strdup (char const*) ; 
 char* strtok_r (char*,char*,char**) ; 
 int strtol (char*,char**,int) ; 
 unsigned int vlc_html_color (char const*,int*) ; 

__attribute__((used)) static void FillTextStyle( const char *psz_attr, const char *psz_val,
                           text_style_t *p_text_style )
{
    if( !strcasecmp ( "tts:fontFamily", psz_attr ) )
    {
        free( p_text_style->psz_fontname );
        p_text_style->psz_fontname = strdup( psz_val );
    }
    else if( !strcasecmp( "tts:opacity", psz_attr ) )
    {
        p_text_style->i_background_alpha = atoi( psz_val );
        p_text_style->i_font_alpha = atoi( psz_val );
        p_text_style->i_features |= STYLE_HAS_BACKGROUND_ALPHA | STYLE_HAS_FONT_ALPHA;
    }
    else if( !strcasecmp( "tts:color", psz_attr ) )
    {
        unsigned int i_color = vlc_html_color( psz_val, NULL );
        p_text_style->i_font_color = (i_color & 0xffffff);
        p_text_style->i_font_alpha = (i_color & 0xFF000000) >> 24;
        p_text_style->i_features |= STYLE_HAS_FONT_COLOR | STYLE_HAS_FONT_ALPHA;
    }
    else if( !strcasecmp( "tts:backgroundColor", psz_attr ) )
    {
        unsigned int i_color = vlc_html_color( psz_val, NULL );
        p_text_style->i_background_color = i_color & 0xFFFFFF;
        p_text_style->i_background_alpha = (i_color & 0xFF000000) >> 24;
        p_text_style->i_features |= STYLE_HAS_BACKGROUND_COLOR
                                                  | STYLE_HAS_BACKGROUND_ALPHA;
        p_text_style->i_style_flags |= STYLE_BACKGROUND;
    }
    else if( !strcasecmp( "tts:fontStyle", psz_attr ) )
    {
        if( !strcasecmp ( "italic", psz_val ) || !strcasecmp ( "oblique", psz_val ) )
            p_text_style->i_style_flags |= STYLE_ITALIC;
        else
            p_text_style->i_style_flags &= ~STYLE_ITALIC;
        p_text_style->i_features |= STYLE_HAS_FLAGS;
    }
    else if( !strcasecmp ( "tts:fontWeight", psz_attr ) )
    {
        if( !strcasecmp ( "bold", psz_val ) )
            p_text_style->i_style_flags |= STYLE_BOLD;
        else
            p_text_style->i_style_flags &= ~STYLE_BOLD;
        p_text_style->i_features |= STYLE_HAS_FLAGS;
    }
    else if( !strcasecmp ( "tts:textDecoration", psz_attr ) )
    {
        if( !strcasecmp ( "underline", psz_val ) )
            p_text_style->i_style_flags |= STYLE_UNDERLINE;
        else if( !strcasecmp ( "noUnderline", psz_val ) )
            p_text_style->i_style_flags &= ~STYLE_UNDERLINE;
        if( !strcasecmp ( "lineThrough", psz_val ) )
            p_text_style->i_style_flags |= STYLE_STRIKEOUT;
        else if( !strcasecmp ( "noLineThrough", psz_val ) )
            p_text_style->i_style_flags &= ~STYLE_STRIKEOUT;
        p_text_style->i_features |= STYLE_HAS_FLAGS;
    }
    else if( !strcasecmp( "tts:textOutline", psz_attr ) )
    {
        char *value = strdup( psz_val );
        char* psz_saveptr = NULL;
        char* token = (value) ? strtok_r( value, " ", &psz_saveptr ) : NULL;
        // <color>? <length> <length>?
        if( token != NULL )
        {
            bool b_ok = false;
            unsigned int color = vlc_html_color( token, &b_ok );
            if( b_ok )
            {
                p_text_style->i_outline_color = color & 0xFFFFFF;
                p_text_style->i_outline_alpha = (color & 0xFF000000) >> 24;
                token = strtok_r( NULL, " ", &psz_saveptr );
                if( token != NULL )
                {
                    char* psz_end = NULL;
                    int i_outline_width = strtol( token, &psz_end, 10 );
                    if( psz_end != token )
                    {
                        // Assume unit is pixel, and ignore border radius
                        p_text_style->i_outline_width = i_outline_width;
                    }
                }
            }
        }
        free( value );
    }
}