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
struct TYPE_3__ {int /*<<< orphan*/ * memory; scalar_t__ num_contours; scalar_t__ num_points; int /*<<< orphan*/  contours; int /*<<< orphan*/  points; int /*<<< orphan*/ * hint_tables; } ;
typedef  TYPE_1__* PSH_Glyph ;
typedef  int /*<<< orphan*/ * FT_Memory ;

/* Variables and functions */
 int /*<<< orphan*/  FT_FREE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  psh_hint_table_done (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
  psh_glyph_done( PSH_Glyph  glyph )
  {
    FT_Memory  memory = glyph->memory;


    psh_hint_table_done( &glyph->hint_tables[1], memory );
    psh_hint_table_done( &glyph->hint_tables[0], memory );

    FT_FREE( glyph->points );
    FT_FREE( glyph->contours );

    glyph->num_points   = 0;
    glyph->num_contours = 0;

    glyph->memory = NULL;
  }