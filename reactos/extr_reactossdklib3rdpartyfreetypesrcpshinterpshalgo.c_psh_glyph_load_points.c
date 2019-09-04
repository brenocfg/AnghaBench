#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  x; int /*<<< orphan*/  y; } ;
struct TYPE_8__ {scalar_t__ num_points; TYPE_2__* points; TYPE_1__* outline; } ;
struct TYPE_7__ {int /*<<< orphan*/  org_v; int /*<<< orphan*/  org_u; int /*<<< orphan*/ * hint; scalar_t__ flags2; } ;
struct TYPE_6__ {TYPE_4__* points; } ;
typedef  TYPE_2__* PSH_Point ;
typedef  TYPE_3__* PSH_Glyph ;
typedef  TYPE_4__ FT_Vector ;
typedef  scalar_t__ FT_UInt ;
typedef  scalar_t__ FT_Int ;

/* Variables and functions */

__attribute__((used)) static void
  psh_glyph_load_points( PSH_Glyph  glyph,
                         FT_Int     dimension )
  {
    FT_Vector*  vec   = glyph->outline->points;
    PSH_Point   point = glyph->points;
    FT_UInt     count = glyph->num_points;


    for ( ; count > 0; count--, point++, vec++ )
    {
      point->flags2 = 0;
      point->hint   = NULL;
      if ( dimension == 0 )
      {
        point->org_u = vec->x;
        point->org_v = vec->y;
      }
      else
      {
        point->org_u = vec->y;
        point->org_v = vec->x;
      }

#ifdef DEBUG_HINTER
      point->org_x = vec->x;
      point->org_y = vec->y;
#endif

    }
  }