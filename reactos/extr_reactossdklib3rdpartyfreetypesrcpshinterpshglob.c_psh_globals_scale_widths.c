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
struct TYPE_6__ {size_t count; TYPE_2__* widths; } ;
struct TYPE_9__ {int /*<<< orphan*/  scale_mult; TYPE_1__ stdw; } ;
struct TYPE_8__ {TYPE_4__* dimension; } ;
struct TYPE_7__ {int cur; void* fit; int /*<<< orphan*/  org; } ;
typedef  TYPE_1__* PSH_Widths ;
typedef  TYPE_2__* PSH_Width ;
typedef  TYPE_3__* PSH_Globals ;
typedef  TYPE_4__* PSH_Dimension ;
typedef  size_t FT_UInt ;
typedef  int FT_Pos ;
typedef  int /*<<< orphan*/  FT_Fixed ;

/* Variables and functions */
 void* FT_MulFix (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* FT_PIX_ROUND (int) ; 

__attribute__((used)) static void
  psh_globals_scale_widths( PSH_Globals  globals,
                            FT_UInt      direction )
  {
    PSH_Dimension  dim   = &globals->dimension[direction];
    PSH_Widths     stdw  = &dim->stdw;
    FT_UInt        count = stdw->count;
    PSH_Width      width = stdw->widths;
    PSH_Width      stand = width;               /* standard width/height */
    FT_Fixed       scale = dim->scale_mult;


    if ( count > 0 )
    {
      width->cur = FT_MulFix( width->org, scale );
      width->fit = FT_PIX_ROUND( width->cur );

      width++;
      count--;

      for ( ; count > 0; count--, width++ )
      {
        FT_Pos  w, dist;


        w    = FT_MulFix( width->org, scale );
        dist = w - stand->cur;

        if ( dist < 0 )
          dist = -dist;

        if ( dist < 128 )
          w = stand->cur;

        width->cur = w;
        width->fit = FT_PIX_ROUND( w );
      }
    }
  }