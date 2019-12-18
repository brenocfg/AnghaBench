#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  metrics; int /*<<< orphan*/  layout; } ;
typedef  TYPE_1__ textbox ;
struct TYPE_10__ {int /*<<< orphan*/  metrics; int /*<<< orphan*/  pfd; scalar_t__ height; } ;
typedef  TYPE_2__ TBFontConfig ;

/* Variables and functions */
 int /*<<< orphan*/  WIDGET (TYPE_1__*) ; 
 int /*<<< orphan*/  g_free (TYPE_2__*) ; 
 int /*<<< orphan*/  g_hash_table_insert (int /*<<< orphan*/ ,char*,TYPE_2__*) ; 
 TYPE_2__* g_hash_table_lookup (int /*<<< orphan*/ ,char const*) ; 
 TYPE_2__* g_malloc0 (int) ; 
 scalar_t__ helper_validate_font (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  p_context ; 
 int /*<<< orphan*/  p_metrics ; 
 int /*<<< orphan*/  pango_context_get_metrics (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pango_font_description_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pango_font_description_from_string (char const*) ; 
 scalar_t__ pango_font_metrics_get_ascent (int /*<<< orphan*/ ) ; 
 scalar_t__ pango_font_metrics_get_descent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pango_layout_set_font_description (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* rofi_theme_get_string (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tbfc_cache ; 

__attribute__((used)) static void textbox_initialize_font ( textbox *tb )
{
    tb->metrics = p_metrics;
    const char * font = rofi_theme_get_string ( WIDGET ( tb ), "font", NULL );
    if ( font ) {
        TBFontConfig *tbfc = g_hash_table_lookup ( tbfc_cache, font );
        if ( tbfc == NULL ) {
            tbfc      = g_malloc0 ( sizeof ( TBFontConfig ) );
            tbfc->pfd = pango_font_description_from_string ( font );
            if ( helper_validate_font ( tbfc->pfd, font ) ) {
                tbfc->metrics = pango_context_get_metrics ( p_context, tbfc->pfd, NULL );
                tbfc->height  = pango_font_metrics_get_ascent ( tbfc->metrics ) + pango_font_metrics_get_descent ( tbfc->metrics );

                // Cast away consts. (*yuck*) because table_insert does not know it is const.
                g_hash_table_insert ( tbfc_cache, (char *) font, tbfc );
            }
            else {
                pango_font_description_free ( tbfc->pfd );
                g_free ( tbfc );
                tbfc = NULL;
            }
        }
        if ( tbfc ) {
            // Update for used font.
            pango_layout_set_font_description ( tb->layout, tbfc->pfd );
            tb->metrics     = tbfc->metrics;
        }
    }
}