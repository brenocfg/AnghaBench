#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct TYPE_9__ {size_t num_points; TYPE_1__* outline; TYPE_2__* points; } ;
struct TYPE_8__ {int flags_x; int flags2; int flags; int flags_y; int /*<<< orphan*/  cur_u; int /*<<< orphan*/  cur_y; int /*<<< orphan*/  cur_x; } ;
struct TYPE_7__ {char* tags; TYPE_4__* points; } ;
typedef  TYPE_2__* PSH_Point ;
typedef  TYPE_3__* PSH_Glyph ;
typedef  TYPE_4__ FT_Vector ;
typedef  size_t FT_UInt ;
typedef  scalar_t__ FT_Int ;

/* Variables and functions */
 scalar_t__ psh_point_is_strong (TYPE_2__*) ; 

__attribute__((used)) static void
  psh_glyph_save_points( PSH_Glyph  glyph,
                         FT_Int     dimension )
  {
    FT_UInt     n;
    PSH_Point   point = glyph->points;
    FT_Vector*  vec   = glyph->outline->points;
    char*       tags  = glyph->outline->tags;


    for ( n = 0; n < glyph->num_points; n++ )
    {
      if ( dimension == 0 )
        vec[n].x = point->cur_u;
      else
        vec[n].y = point->cur_u;

      if ( psh_point_is_strong( point ) )
        tags[n] |= (char)( ( dimension == 0 ) ? 32 : 64 );

#ifdef DEBUG_HINTER

      if ( dimension == 0 )
      {
        point->cur_x   = point->cur_u;
        point->flags_x = point->flags2 | point->flags;
      }
      else
      {
        point->cur_y   = point->cur_u;
        point->flags_y = point->flags2 | point->flags;
      }

#endif

      point++;
    }
  }