#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* face; } ;
struct TYPE_7__ {TYPE_2__ builder; } ;
struct TYPE_5__ {int units_per_EM; } ;
typedef  TYPE_3__ PS_Decoder ;
typedef  int FT_UShort ;

/* Variables and functions */
 int /*<<< orphan*/  FT_ASSERT (int) ; 

__attribute__((used)) static FT_UShort
  cf2_getUnitsPerEm( PS_Decoder*  decoder )
  {
    FT_ASSERT( decoder && decoder->builder.face );
    FT_ASSERT( decoder->builder.face->units_per_EM );

    return decoder->builder.face->units_per_EM;
  }