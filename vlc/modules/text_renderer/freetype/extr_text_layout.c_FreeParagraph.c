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
struct TYPE_4__ {struct TYPE_4__* p_levels; struct TYPE_4__* p_btypes; struct TYPE_4__* p_types; struct TYPE_4__* pi_reordered_indices; struct TYPE_4__* p_scripts; struct TYPE_4__* p_code_points; struct TYPE_4__* pp_styles; struct TYPE_4__* pp_ruby; struct TYPE_4__* pp_faces; struct TYPE_4__* pi_run_ids; struct TYPE_4__* p_glyph_bitmaps; struct TYPE_4__* pi_glyph_indices; struct TYPE_4__* p_runs; } ;
typedef  TYPE_1__ paragraph_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 

__attribute__((used)) static void FreeParagraph( paragraph_t *p_paragraph )
{
    free( p_paragraph->p_runs );
    free( p_paragraph->pi_glyph_indices );
    free( p_paragraph->p_glyph_bitmaps );
    free( p_paragraph->pi_run_ids );
    free( p_paragraph->pp_faces );
    free( p_paragraph->pp_ruby );
    free( p_paragraph->pp_styles );
    free( p_paragraph->p_code_points );

#ifdef HAVE_HARFBUZZ
    free( p_paragraph->p_scripts );
#endif

#ifdef HAVE_FRIBIDI
    free( p_paragraph->pi_reordered_indices );
    free( p_paragraph->p_types );
#if FRIBIDI_MAJOR_VERSION >= 1
    free( p_paragraph->p_btypes );
#endif
    free( p_paragraph->p_levels );
#endif

    free( p_paragraph );
}