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
typedef  int /*<<< orphan*/  gpointer ;
struct TYPE_4__ {int /*<<< orphan*/ * metrics; scalar_t__ height; } ;
typedef  TYPE_1__ TBFontConfig ;
typedef  int /*<<< orphan*/  PangoContext ;

/* Variables and functions */
 char const* default_font_name ; 
 int /*<<< orphan*/  g_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_hash_table_insert (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*) ; 
 TYPE_1__* g_malloc0 (int) ; 
 int /*<<< orphan*/  g_object_ref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  p_context ; 
 int /*<<< orphan*/ * p_metrics ; 
 int /*<<< orphan*/ * pango_context_get_metrics (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ pango_font_metrics_get_ascent (int /*<<< orphan*/ *) ; 
 scalar_t__ pango_font_metrics_get_descent (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tbfc_cache ; 

void textbox_set_pango_context ( const char *font, PangoContext *p )
{
    g_assert ( p_metrics == NULL );
    p_context = g_object_ref ( p );
    p_metrics = pango_context_get_metrics ( p_context, NULL, NULL );
    TBFontConfig *tbfc = g_malloc0 ( sizeof ( TBFontConfig ) );
    tbfc->metrics = p_metrics;
    tbfc->height  = pango_font_metrics_get_ascent ( tbfc->metrics ) + pango_font_metrics_get_descent ( tbfc->metrics );
    g_hash_table_insert ( tbfc_cache, (gpointer *) ( font ? font : default_font_name ), tbfc );
}