#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  char uint8_t ;
struct TYPE_6__ {void* psz_text; TYPE_1__* style; struct TYPE_6__* p_next; } ;
typedef  TYPE_2__ text_segment_t ;
struct eia608_screen {char** characters; size_t** colors; int** fonts; } ;
typedef  int eia608_font_t ;
typedef  size_t eia608_color_t ;
struct TYPE_5__ {int /*<<< orphan*/  i_features; int /*<<< orphan*/  i_font_color; int /*<<< orphan*/  i_style_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAT (char*) ; 
 size_t EIA608_COLOR_DEFAULT ; 
 int EIA608_FONT_ITALICS ; 
 int EIA608_FONT_REGULAR ; 
 int EIA608_FONT_UNDERLINE ; 
 int EIA608_SCREEN_COLUMNS ; 
 int /*<<< orphan*/  Eia608TextUtf8 (char*,char const) ; 
 int /*<<< orphan*/  EnsureUTF8 (char*) ; 
 int /*<<< orphan*/  STYLE_HAS_FLAGS ; 
 int /*<<< orphan*/  STYLE_HAS_FONT_COLOR ; 
 int /*<<< orphan*/  STYLE_ITALIC ; 
 int /*<<< orphan*/  STYLE_MONOSPACED ; 
 int /*<<< orphan*/  STYLE_NO_DEFAULTS ; 
 int /*<<< orphan*/  STYLE_UNDERLINE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/ * rgi_eia608_colors ; 
 void* strdup (char*) ; 
 int /*<<< orphan*/  text_segment_Delete (TYPE_2__*) ; 
 void* text_segment_New (int /*<<< orphan*/ *) ; 
 void* text_style_Create (int /*<<< orphan*/ ) ; 

__attribute__((used)) static text_segment_t * Eia608TextLine( struct eia608_screen *screen, int i_row )
{
    const uint8_t *p_char = screen->characters[i_row];
    const eia608_color_t *p_color = screen->colors[i_row];
    const eia608_font_t *p_font = screen->fonts[i_row];
    int i_start;
    int i_end;
    int x;
    eia608_color_t prev_color = EIA608_COLOR_DEFAULT;
    eia608_font_t prev_font = EIA608_FONT_REGULAR;

    char utf8[4];
    const unsigned i_text_max = 4 * EIA608_SCREEN_COLUMNS + 1;
    char psz_text[i_text_max + 1];
    psz_text[0] = '\0';

    /* Search the start */
    i_start = 0;

    /* Convert leading spaces to non-breaking so that they don't get
       stripped by the RenderHtml routine as regular whitespace */
    while( i_start < EIA608_SCREEN_COLUMNS && p_char[i_start] == ' ' ) {
        Eia608TextUtf8( utf8, 0x89 );
        CAT( utf8 );
        i_start++;
    }

    /* Search the end */
    i_end = EIA608_SCREEN_COLUMNS-1;
    while( i_end > i_start && p_char[i_end] == ' ' )
        i_end--;

    /* */
    if( i_start > i_end ) /* Nothing to render */
        return NULL;

    text_segment_t *p_segment, *p_segments_head = p_segment = text_segment_New( NULL );
    if(!p_segment)
        return NULL;

    p_segment->style = text_style_Create( STYLE_NO_DEFAULTS );
    if(!p_segment->style)
    {
        text_segment_Delete(p_segment);
        return NULL;
    }
    /* Ensure we get a monospaced font (required for accurate positioning */
    p_segment->style->i_style_flags |= STYLE_MONOSPACED;

    for( x = i_start; x <= i_end; x++ )
    {
        eia608_color_t color = p_color[x];
        eia608_font_t font = p_font[x];

        if(font != prev_font || color != prev_color)
        {
            EnsureUTF8(psz_text);
            p_segment->psz_text = strdup(psz_text);
            psz_text[0] = '\0';
            p_segment->p_next = text_segment_New( NULL );
            p_segment = p_segment->p_next;
            if(!p_segment)
                return p_segments_head;

            p_segment->style = text_style_Create( STYLE_NO_DEFAULTS );
            if(!p_segment->style)
            {
                text_segment_Delete(p_segment);
                return p_segments_head;
            }
            p_segment->style->i_style_flags |= STYLE_MONOSPACED;

            /* start segment with new style */
            if(font & EIA608_FONT_ITALICS)
            {
                p_segment->style->i_style_flags |= STYLE_ITALIC;
                p_segment->style->i_features |= STYLE_HAS_FLAGS;
            }
            if(font & EIA608_FONT_UNDERLINE)
            {
                p_segment->style->i_style_flags |= STYLE_UNDERLINE;
                p_segment->style->i_features |= STYLE_HAS_FLAGS;
            }

            if(color != EIA608_COLOR_DEFAULT)
            {
                p_segment->style->i_font_color = rgi_eia608_colors[color];
                p_segment->style->i_features |= STYLE_HAS_FONT_COLOR;
            }
        }

        Eia608TextUtf8( utf8, p_char[x] );
        CAT( utf8 );

        /* */
        prev_font = font;
        prev_color = color;
    }

#undef CAT

    if( p_segment )
    {
        assert(!p_segment->psz_text); // shouldn't happen
        EnsureUTF8(psz_text);
        p_segment->psz_text = strdup(psz_text);
    }

    return p_segments_head;
}