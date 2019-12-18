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
struct TYPE_4__ {int variation_support; } ;
typedef  TYPE_1__* TT_Face ;
typedef  int /*<<< orphan*/  FT_UShort ;
typedef  scalar_t__ FT_UInt ;
typedef  int /*<<< orphan*/  FT_Short ;
typedef  int FT_Int32 ;
typedef  int /*<<< orphan*/  FT_Fixed ;
typedef  int /*<<< orphan*/  FT_Face ;
typedef  int /*<<< orphan*/  FT_Error ;

/* Variables and functions */
 int /*<<< orphan*/  FT_Err_Ok ; 
 scalar_t__ FT_IS_NAMED_INSTANCE (int /*<<< orphan*/ ) ; 
 scalar_t__ FT_IS_VARIATION (int /*<<< orphan*/ ) ; 
 int FT_LOAD_VERTICAL_LAYOUT ; 
 int /*<<< orphan*/  FT_THROW (int /*<<< orphan*/ ) ; 
 int TT_FACE_FLAG_VAR_HADVANCE ; 
 int TT_FACE_FLAG_VAR_VADVANCE ; 
 int /*<<< orphan*/  TT_Get_HMetrics (TYPE_1__*,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TT_Get_VMetrics (TYPE_1__*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Unimplemented_Feature ; 

__attribute__((used)) static FT_Error
  tt_get_advances( FT_Face    ttface,
                   FT_UInt    start,
                   FT_UInt    count,
                   FT_Int32   flags,
                   FT_Fixed  *advances )
  {
    FT_UInt  nn;
    TT_Face  face = (TT_Face)ttface;


    /* XXX: TODO: check for sbits */

    if ( flags & FT_LOAD_VERTICAL_LAYOUT )
    {
#ifdef TT_CONFIG_OPTION_GX_VAR_SUPPORT
      /* no fast retrieval for blended MM fonts without VVAR table */
      if ( ( FT_IS_NAMED_INSTANCE( ttface ) || FT_IS_VARIATION( ttface ) ) &&
           !( face->variation_support & TT_FACE_FLAG_VAR_VADVANCE )        )
        return FT_THROW( Unimplemented_Feature );
#endif

      for ( nn = 0; nn < count; nn++ )
      {
        FT_Short   tsb;
        FT_UShort  ah;


        /* since we don't need `tsb', we use zero for `yMax' parameter */
        TT_Get_VMetrics( face, start + nn, 0, &tsb, &ah );
        advances[nn] = ah;
      }
    }
    else
    {
#ifdef TT_CONFIG_OPTION_GX_VAR_SUPPORT
      /* no fast retrieval for blended MM fonts without HVAR table */
      if ( ( FT_IS_NAMED_INSTANCE( ttface ) || FT_IS_VARIATION( ttface ) ) &&
           !( face->variation_support & TT_FACE_FLAG_VAR_HADVANCE )        )
        return FT_THROW( Unimplemented_Feature );
#endif

      for ( nn = 0; nn < count; nn++ )
      {
        FT_Short   lsb;
        FT_UShort  aw;


        TT_Get_HMetrics( face, start + nn, &lsb, &aw );
        advances[nn] = aw;
      }
    }

    return FT_Err_Ok;
  }