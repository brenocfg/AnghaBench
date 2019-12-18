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
typedef  int FT_UInt ;
typedef  int /*<<< orphan*/  FT_Bytes ;

/* Variables and functions */
 int /*<<< orphan*/  FT_INVALID_FORMAT ; 
 int FT_NEXT_USHORT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Ligature ; 
 int /*<<< orphan*/  LigatureSet ; 
 int /*<<< orphan*/  LigatureSubstFormat1 ; 
 int /*<<< orphan*/  OTV_EXIT ; 
 int /*<<< orphan*/  OTV_LIMIT_CHECK (int) ; 
 int /*<<< orphan*/  OTV_NAME_ENTER (char*) ; 
 int /*<<< orphan*/  OTV_NEST3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OTV_RUN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OTV_TRACE (char*) ; 

__attribute__((used)) static void
  otv_LigatureSubst_validate( FT_Bytes       table,
                              OTV_Validator  otvalid )
  {
    FT_Bytes  p = table;
    FT_UInt   SubstFormat;


    OTV_NAME_ENTER( "LigatureSubst" );

    OTV_LIMIT_CHECK( 2 );
    SubstFormat = FT_NEXT_USHORT( p );

    OTV_TRACE(( " (format %d)\n", SubstFormat ));

    switch ( SubstFormat )
    {
    case 1:
      OTV_NEST3( LigatureSubstFormat1, LigatureSet, Ligature );
      OTV_RUN( table, otvalid );
      break;

    default:
      FT_INVALID_FORMAT;
    }

    OTV_EXIT;
  }