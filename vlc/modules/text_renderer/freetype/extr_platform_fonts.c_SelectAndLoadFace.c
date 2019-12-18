#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uni_char_t ;
struct TYPE_10__ {int i_style_flags; char* psz_monofontname; char* psz_fontname; } ;
typedef  TYPE_1__ text_style_t ;
struct TYPE_11__ {TYPE_3__* p_sys; } ;
typedef  TYPE_2__ filter_t ;
struct TYPE_12__ {char* (* pf_select ) (TYPE_2__*,char const*,int,int,int*,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_3__ filter_sys_t ;
typedef  int /*<<< orphan*/ * FT_Face ;

/* Variables and functions */
 int /*<<< orphan*/ * LoadFace (TYPE_2__*,char*,int,TYPE_1__ const*) ; 
 int STYLE_BOLD ; 
 int STYLE_ITALIC ; 
 int STYLE_MONOSPACED ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  msg_Warn (TYPE_2__*,char*,char const*,int /*<<< orphan*/ ) ; 
 char* stub1 (TYPE_2__*,char const*,int,int,int*,int /*<<< orphan*/ ) ; 

FT_Face SelectAndLoadFace( filter_t *p_filter, const text_style_t *p_style,
                           uni_char_t codepoint )
{
    filter_sys_t *p_sys = p_filter->p_sys;

    const char *psz_fontname = (p_style->i_style_flags & STYLE_MONOSPACED)
                               ? p_style->psz_monofontname : p_style->psz_fontname;

    bool b_bold = p_style->i_style_flags & STYLE_BOLD;
    bool b_italic = p_style->i_style_flags & STYLE_ITALIC;

    FT_Face p_face = NULL;


    int  i_idx = 0;
    char *psz_fontfile = NULL;
    if( p_sys->pf_select )
        psz_fontfile = p_sys->pf_select( p_filter, psz_fontname, b_bold, b_italic,
                                         &i_idx, codepoint );
    else
        psz_fontfile = NULL;

    if( !psz_fontfile || *psz_fontfile == '\0' )
    {
        msg_Warn( p_filter,
                  "SelectAndLoadFace: no font found for family: %s, codepoint: 0x%x",
                  psz_fontname, codepoint );
        free( psz_fontfile );
        return NULL;
    }

    p_face = LoadFace( p_filter, psz_fontfile, i_idx, p_style );

    free( psz_fontfile );
    return p_face;
}