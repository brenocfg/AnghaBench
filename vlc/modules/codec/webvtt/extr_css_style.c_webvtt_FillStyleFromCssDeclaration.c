#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
struct TYPE_19__ {scalar_t__ type; char const* psz; double val; } ;
typedef  TYPE_3__ vlc_css_term_t ;
struct TYPE_20__ {char const* psz_property; TYPE_2__* expr; } ;
typedef  TYPE_4__ vlc_css_declaration_t ;
struct TYPE_21__ {int i_style_flags; char* psz_fontname; double i_font_size; double f_font_relsize; int /*<<< orphan*/  e_wrapinfo; int /*<<< orphan*/  i_features; int /*<<< orphan*/  i_background_alpha; int /*<<< orphan*/  i_background_color; int /*<<< orphan*/  i_font_alpha; int /*<<< orphan*/  i_font_color; } ;
typedef  TYPE_5__ text_style_t ;
struct TYPE_18__ {int i_count; TYPE_1__* seq; } ;
struct TYPE_17__ {TYPE_3__ term; } ;

/* Variables and functions */
 int /*<<< orphan*/  Color (TYPE_3__,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OutlineColor (TYPE_3__,TYPE_5__*) ; 
 int /*<<< orphan*/  OutlineWidth (TYPE_3__,TYPE_5__*) ; 
 int STYLE_BACKGROUND ; 
 int STYLE_BOLD ; 
 int /*<<< orphan*/  STYLE_HAS_BACKGROUND_ALPHA ; 
 int /*<<< orphan*/  STYLE_HAS_BACKGROUND_COLOR ; 
 int /*<<< orphan*/  STYLE_HAS_FLAGS ; 
 int /*<<< orphan*/  STYLE_HAS_FONT_ALPHA ; 
 int /*<<< orphan*/  STYLE_HAS_FONT_COLOR ; 
 int STYLE_ITALIC ; 
 int STYLE_STRIKEOUT ; 
 int STYLE_UNDERLINE ; 
 int /*<<< orphan*/  STYLE_WRAP_DEFAULT ; 
 int /*<<< orphan*/  STYLE_WRAP_NONE ; 
 int /*<<< orphan*/  ShadowColor (TYPE_3__,TYPE_5__*) ; 
 int /*<<< orphan*/  ShadowDrop (TYPE_3__,TYPE_5__*) ; 
 scalar_t__ TYPE_EMS ; 
 scalar_t__ TYPE_NONE ; 
 scalar_t__ TYPE_PERCENT ; 
 scalar_t__ TYPE_PIXELS ; 
 scalar_t__ TYPE_STRING ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  strcasecmp (char const*,char*) ; 
 char* strchr (char const*,char) ; 
 char* strdup (char const*) ; 
 char* strndup (char const*,int) ; 
 char* vlc_css_unquoted (char*) ; 

void webvtt_FillStyleFromCssDeclaration( const vlc_css_declaration_t *p_decl, text_style_t *p_style )
{
    if( !p_decl->psz_property || !p_style )
        return;

    /* Only support simple expressions for now */
    if( p_decl->expr->i_count < 1 )
        return;

    vlc_css_term_t term0 = p_decl->expr->seq[0].term;

    if( !strcasecmp( p_decl->psz_property, "color" ) )
    {
        Color( term0, &p_style->i_font_color, &p_style->i_font_alpha,
               &p_style->i_features, STYLE_HAS_FONT_COLOR, STYLE_HAS_FONT_ALPHA );
    }
    else if( !strcasecmp( p_decl->psz_property, "text-decoration" ) )
    {
        if( term0.type == TYPE_STRING )
        {
            if( !strcasecmp( term0.psz, "none" ) )
            {
                p_style->i_style_flags &= ~(STYLE_STRIKEOUT|STYLE_UNDERLINE);
                p_style->i_features |= STYLE_HAS_FLAGS;
            }
            else if( !strcasecmp( term0.psz, "line-through" ) )
            {
                p_style->i_style_flags |= STYLE_STRIKEOUT;
                p_style->i_features |= STYLE_HAS_FLAGS;
            }
            else if( !strcasecmp( term0.psz, "underline" ) )
            {
                p_style->i_style_flags |= STYLE_UNDERLINE;
                p_style->i_features |= STYLE_HAS_FLAGS;
            }
        }
    }
    else if( !strcasecmp( p_decl->psz_property, "text-shadow" ) )
    {
        ShadowDrop( term0, p_style );
        if( p_decl->expr->i_count == 3 )
            ShadowColor( p_decl->expr->seq[2].term, p_style );
    }
    else if( !strcasecmp( p_decl->psz_property, "background-color" ) )
    {
        Color( term0, &p_style->i_background_color, &p_style->i_background_alpha,
               &p_style->i_features, STYLE_HAS_BACKGROUND_COLOR, STYLE_HAS_BACKGROUND_ALPHA );
        p_style->i_style_flags |= STYLE_BACKGROUND;
        p_style->i_features |= STYLE_HAS_FLAGS;
    }
    else if( !strcasecmp( p_decl->psz_property, "outline-color" ) )
    {
        OutlineColor( term0, p_style );
    }
    else if( !strcasecmp( p_decl->psz_property, "outline-width" ) )
    {
        OutlineWidth( term0, p_style );
    }
    else if( !strcasecmp( p_decl->psz_property, "outline" ) )
    {
        OutlineWidth( term0, p_style );
        if( p_decl->expr->i_count == 3 )
            OutlineColor( p_decl->expr->seq[2].term, p_style );
    }
    else if( !strcasecmp( p_decl->psz_property, "font-family" ) )
    {
        if( term0.type >= TYPE_STRING )
        {
            char *psz_font = NULL;
            const char *psz = strchr( term0.psz, ',' );
            if( psz )
                psz_font = strndup( term0.psz, psz - term0.psz + 1 );
            else
                psz_font = strdup( term0.psz );
            free( p_style->psz_fontname );
            p_style->psz_fontname = vlc_css_unquoted( psz_font );
            free( psz_font );
        }
    }
    else if( !strcasecmp( p_decl->psz_property, "font-style" ) )
    {
        if( term0.type >= TYPE_STRING )
        {
            if( !strcasecmp(term0.psz, "normal") )
            {
                p_style->i_style_flags &= ~STYLE_ITALIC;
                p_style->i_features |= STYLE_HAS_FLAGS;
            }
            else if( !strcasecmp(term0.psz, "italic") )
            {
                p_style->i_style_flags |= STYLE_ITALIC;
                p_style->i_features |= STYLE_HAS_FLAGS;
            }
        }
    }
    else if( !strcasecmp( p_decl->psz_property, "font-weight" ) )
    {
        if( term0.type >= TYPE_STRING )
        {
            if( !strcasecmp(term0.psz, "normal") )
            {
                p_style->i_style_flags &= ~STYLE_BOLD;
                p_style->i_features |= STYLE_HAS_FLAGS;
            }
            if( !strcasecmp(term0.psz, "bold") )
            {
                p_style->i_style_flags |= STYLE_BOLD;
                p_style->i_features |= STYLE_HAS_FLAGS;
            }
        }
        else if( term0.type == TYPE_NONE )
        {
            if( term0.val >= 700.0 )
                p_style->i_style_flags |= STYLE_BOLD;
            else
                p_style->i_style_flags &= ~STYLE_BOLD;
            p_style->i_features |= STYLE_HAS_FLAGS;
        }
    }
    else if( !strcasecmp( p_decl->psz_property, "font-size" ) )
    {
        if( term0.type == TYPE_PIXELS )
            p_style->i_font_size = term0.val;
        else if( term0.type == TYPE_EMS )
            p_style->f_font_relsize = term0.val * 5.33 / 1.06;
        else if( term0.type == TYPE_PERCENT )
            p_style->f_font_relsize = term0.val * 5.33 / 100;
    }
    else if( !strcasecmp( p_decl->psz_property, "font" ) )
    {
        /* what to do ? */
    }
    else if( !strcasecmp( p_decl->psz_property, "white-space" ) )
    {
        if( term0.type >= TYPE_STRING )
        {
            if( !strcasecmp(term0.psz, "normal" ) )
                p_style->e_wrapinfo = STYLE_WRAP_DEFAULT;
            if( !strcasecmp(term0.psz, "nowrap" ) )
                p_style->e_wrapinfo = STYLE_WRAP_NONE;
        }
    }
}