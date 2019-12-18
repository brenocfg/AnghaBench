#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ format; int /*<<< orphan*/  outline; } ;
struct TYPE_8__ {scalar_t__ glyph_format; } ;
struct TYPE_7__ {int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
typedef  TYPE_1__ FT_Vector ;
typedef  TYPE_2__* FT_Renderer ;
typedef  int /*<<< orphan*/  FT_Matrix ;
typedef  TYPE_3__* FT_GlyphSlot ;
typedef  int /*<<< orphan*/  FT_Error ;

/* Variables and functions */
 int /*<<< orphan*/  FT_Err_Ok ; 
 int /*<<< orphan*/  FT_Outline_Transform (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  FT_Outline_Translate (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FT_THROW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Invalid_Argument ; 

__attribute__((used)) static FT_Error
  ft_smooth_transform( FT_Renderer       render,
                       FT_GlyphSlot      slot,
                       const FT_Matrix*  matrix,
                       const FT_Vector*  delta )
  {
    FT_Error  error = FT_Err_Ok;


    if ( slot->format != render->glyph_format )
    {
      error = FT_THROW( Invalid_Argument );
      goto Exit;
    }

    if ( matrix )
      FT_Outline_Transform( &slot->outline, matrix );

    if ( delta )
      FT_Outline_Translate( &slot->outline, delta->x, delta->y );

  Exit:
    return error;
  }