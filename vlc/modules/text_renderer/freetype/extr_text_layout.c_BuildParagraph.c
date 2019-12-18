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
typedef  int /*<<< orphan*/  uni_char_t ;
typedef  int /*<<< orphan*/  text_style_t ;
typedef  int /*<<< orphan*/  ruby_block_t ;
typedef  int /*<<< orphan*/  paragraph_t ;
typedef  int /*<<< orphan*/  filter_t ;

/* Variables and functions */
 scalar_t__ AnalyzeParagraph (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FreeParagraph (int /*<<< orphan*/ *) ; 
 scalar_t__ ItemizeParagraph (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ LoadGlyphs (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,unsigned int*) ; 
 int /*<<< orphan*/ * NewParagraph (int /*<<< orphan*/ *,int,int /*<<< orphan*/  const*,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int) ; 
 scalar_t__ RemoveZeroWidthCharacters (int /*<<< orphan*/ *) ; 
 scalar_t__ ShapeParagraphFriBidi (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ ShapeParagraphHarfBuzz (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 scalar_t__ ZeroNsmAdvance (int /*<<< orphan*/ *) ; 

__attribute__((used)) static paragraph_t * BuildParagraph( filter_t *p_filter,
                                     int i_size,
                                     const uni_char_t *p_uchars,
                                     text_style_t **pp_styles,
                                     ruby_block_t **pp_ruby,
                                     int i_runs_size,
                                     unsigned *pi_max_advance_x )
{
    paragraph_t *p_paragraph = NewParagraph( p_filter, i_size,
                                p_uchars,
                                pp_styles,
                                pp_ruby,
                                i_runs_size );
    if( !p_paragraph )
        return NULL;

#ifdef HAVE_FRIBIDI
    if( AnalyzeParagraph( p_paragraph ) )
        goto error;
#endif

    if( ItemizeParagraph( p_filter, p_paragraph ) )
        goto error;

#if defined HAVE_HARFBUZZ
    if( ShapeParagraphHarfBuzz( p_filter, &p_paragraph ) )
        goto error;

    if( LoadGlyphs( p_filter, p_paragraph, true, false, pi_max_advance_x ) )
        goto error;

#elif defined HAVE_FRIBIDI
    if( ShapeParagraphFriBidi( p_filter, p_paragraph ) )
        goto error;
    if( LoadGlyphs( p_filter, p_paragraph, false, true, pi_max_advance_x ) )
        goto error;
    if( RemoveZeroWidthCharacters( p_paragraph ) )
        goto error;
    if( ZeroNsmAdvance( p_paragraph ) )
        goto error;
#else
    if( LoadGlyphs( p_filter, p_paragraph, false, true, pi_max_advance_x ) )
        goto error;
#endif

    return p_paragraph;

error:
    if( p_paragraph )
        FreeParagraph( p_paragraph );

    return NULL;
}