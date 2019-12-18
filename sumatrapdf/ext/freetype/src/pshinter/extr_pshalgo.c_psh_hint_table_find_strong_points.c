#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int org_pos; int org_len; } ;
struct TYPE_10__ {scalar_t__ num_hints; TYPE_3__** sort; } ;
struct TYPE_9__ {int org_u; int dir_in; int dir_out; scalar_t__ flags2; TYPE_3__* hint; } ;
typedef  TYPE_1__* PSH_Point ;
typedef  TYPE_2__* PSH_Hint_Table ;
typedef  TYPE_3__* PSH_Hint ;
typedef  scalar_t__ FT_UInt ;
typedef  int FT_Pos ;
typedef  int FT_Int ;

/* Variables and functions */
 int ADD_INT (int,int) ; 
 scalar_t__ PSH_DIR_COMPARE (int,int) ; 
 int PSH_DIR_HORIZONTAL ; 
 scalar_t__ PSH_POINT_EDGE_MAX ; 
 scalar_t__ PSH_POINT_EDGE_MIN ; 
 scalar_t__ PSH_POINT_NEGATIVE ; 
 scalar_t__ PSH_POINT_POSITIVE ; 
 scalar_t__ psh_point_is_extremum (TYPE_1__*) ; 
 scalar_t__ psh_point_is_strong (TYPE_1__*) ; 
 int /*<<< orphan*/  psh_point_set_strong (TYPE_1__*) ; 

__attribute__((used)) static void
  psh_hint_table_find_strong_points( PSH_Hint_Table  table,
                                     PSH_Point       point,
                                     FT_UInt         count,
                                     FT_Int          threshold,
                                     FT_Int          major_dir )
  {
    PSH_Hint*  sort      = table->sort;
    FT_UInt    num_hints = table->num_hints;


    for ( ; count > 0; count--, point++ )
    {
      FT_Int  point_dir = 0;
      FT_Pos  org_u     = point->org_u;


      if ( psh_point_is_strong( point ) )
        continue;

      if ( PSH_DIR_COMPARE( point->dir_in, major_dir ) )
        point_dir = point->dir_in;

      else if ( PSH_DIR_COMPARE( point->dir_out, major_dir ) )
        point_dir = point->dir_out;

      if ( point_dir )
      {
        if ( point_dir == major_dir )
        {
          FT_UInt  nn;


          for ( nn = 0; nn < num_hints; nn++ )
          {
            PSH_Hint  hint = sort[nn];
            FT_Pos    d    = org_u - hint->org_pos;


            if ( d < threshold && -d < threshold )
            {
              psh_point_set_strong( point );
              point->flags2 |= PSH_POINT_EDGE_MIN;
              point->hint    = hint;
              break;
            }
          }
        }
        else if ( point_dir == -major_dir )
        {
          FT_UInt  nn;


          for ( nn = 0; nn < num_hints; nn++ )
          {
            PSH_Hint  hint = sort[nn];
            FT_Pos    d    = org_u - hint->org_pos - hint->org_len;


            if ( d < threshold && -d < threshold )
            {
              psh_point_set_strong( point );
              point->flags2 |= PSH_POINT_EDGE_MAX;
              point->hint    = hint;
              break;
            }
          }
        }
      }

#if 1
      else if ( psh_point_is_extremum( point ) )
      {
        /* treat extrema as special cases for stem edge alignment */
        FT_UInt  nn, min_flag, max_flag;


        if ( major_dir == PSH_DIR_HORIZONTAL )
        {
          min_flag = PSH_POINT_POSITIVE;
          max_flag = PSH_POINT_NEGATIVE;
        }
        else
        {
          min_flag = PSH_POINT_NEGATIVE;
          max_flag = PSH_POINT_POSITIVE;
        }

        if ( point->flags2 & min_flag )
        {
          for ( nn = 0; nn < num_hints; nn++ )
          {
            PSH_Hint  hint = sort[nn];
            FT_Pos    d    = org_u - hint->org_pos;


            if ( d < threshold && -d < threshold )
            {
              point->flags2 |= PSH_POINT_EDGE_MIN;
              point->hint    = hint;
              psh_point_set_strong( point );
              break;
            }
          }
        }
        else if ( point->flags2 & max_flag )
        {
          for ( nn = 0; nn < num_hints; nn++ )
          {
            PSH_Hint  hint = sort[nn];
            FT_Pos    d    = org_u - hint->org_pos - hint->org_len;


            if ( d < threshold && -d < threshold )
            {
              point->flags2 |= PSH_POINT_EDGE_MAX;
              point->hint    = hint;
              psh_point_set_strong( point );
              break;
            }
          }
        }

        if ( !point->hint )
        {
          for ( nn = 0; nn < num_hints; nn++ )
          {
            PSH_Hint  hint = sort[nn];


            if ( org_u >=          hint->org_pos                  &&
                 org_u <= ADD_INT( hint->org_pos, hint->org_len ) )
            {
              point->hint = hint;
              break;
            }
          }
        }
      }

#endif /* 1 */
    }
  }