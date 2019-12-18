#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  OTV_Validator ;
typedef  scalar_t__ FT_UInt ;
typedef  scalar_t__ FT_Bytes ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ FT_NEXT_USHORT (scalar_t__) ; 
 int /*<<< orphan*/  OTV_EXIT ; 
 int /*<<< orphan*/  OTV_LIMIT_CHECK (int) ; 
 int /*<<< orphan*/  OTV_NAME_ENTER (char*) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  otv_Coverage_validate (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  otv_MathItalicsCorrectionInfo_validate (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  otv_MathKernInfo_validate (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
  otv_MathGlyphInfo_validate( FT_Bytes       table,
                              OTV_Validator  otvalid )
  {
    FT_Bytes  p = table;
    FT_UInt   MathItalicsCorrectionInfo, MathTopAccentAttachment;
    FT_UInt   ExtendedShapeCoverage, MathKernInfo;


    OTV_NAME_ENTER( "MathGlyphInfo" );

    OTV_LIMIT_CHECK( 8 );

    MathItalicsCorrectionInfo = FT_NEXT_USHORT( p );
    MathTopAccentAttachment   = FT_NEXT_USHORT( p );
    ExtendedShapeCoverage     = FT_NEXT_USHORT( p );
    MathKernInfo              = FT_NEXT_USHORT( p );

    if ( MathItalicsCorrectionInfo )
      otv_MathItalicsCorrectionInfo_validate(
        table + MathItalicsCorrectionInfo, otvalid, TRUE );

    /* Italic correction and Top Accent Attachment have the same format */
    if ( MathTopAccentAttachment )
      otv_MathItalicsCorrectionInfo_validate(
        table + MathTopAccentAttachment, otvalid, FALSE );

    if ( ExtendedShapeCoverage )
    {
      OTV_NAME_ENTER( "ExtendedShapeCoverage" );
      otv_Coverage_validate( table + ExtendedShapeCoverage, otvalid, -1 );
      OTV_EXIT;
    }

    if ( MathKernInfo )
      otv_MathKernInfo_validate( table + MathKernInfo, otvalid );

    OTV_EXIT;
  }