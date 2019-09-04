#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_2__* decoder; } ;
struct TYPE_6__ {int /*<<< orphan*/  is_t1; } ;
struct TYPE_7__ {int /*<<< orphan*/ * glyph_width; TYPE_1__ builder; } ;
typedef  TYPE_2__ PS_Decoder ;
typedef  TYPE_3__* CF2_Outline ;
typedef  int /*<<< orphan*/  CF2_Fixed ;

/* Variables and functions */
 int /*<<< orphan*/  FT_ASSERT (TYPE_2__*) ; 
 int /*<<< orphan*/  cf2_fixedToInt (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
  cf2_setGlyphWidth( CF2_Outline  outline,
                     CF2_Fixed    width )
  {
    PS_Decoder*  decoder = outline->decoder;


    FT_ASSERT( decoder );

    if ( !decoder->builder.is_t1 )
      *decoder->glyph_width = cf2_fixedToInt( width );
  }