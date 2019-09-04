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
typedef  scalar_t__ FT_Bytes ;

/* Variables and functions */
 scalar_t__ BaseTagList ; 
 scalar_t__ FT_NEXT_USHORT (scalar_t__) ; 
 int /*<<< orphan*/  OTV_EXIT ; 
 int /*<<< orphan*/  OTV_LIMIT_CHECK (int) ; 
 int /*<<< orphan*/  OTV_NAME_ENTER (char*) ; 
 int /*<<< orphan*/  OTV_OPTIONAL_OFFSET (scalar_t__) ; 
 int /*<<< orphan*/  OTV_OPTIONAL_TABLE (scalar_t__) ; 
 int /*<<< orphan*/  OTV_SIZE_CHECK (scalar_t__) ; 
 int /*<<< orphan*/  otv_BaseScriptList_validate (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  otv_BaseTagList_validate (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
  otv_Axis_validate( FT_Bytes       table,
                     OTV_Validator  otvalid )
  {
    FT_Bytes  p = table;
    FT_UInt   table_size;

    OTV_OPTIONAL_TABLE( BaseTagList );


    OTV_NAME_ENTER( "Axis" );

    OTV_LIMIT_CHECK( 4 );
    OTV_OPTIONAL_OFFSET( BaseTagList );

    table_size = 4;

    OTV_SIZE_CHECK( BaseTagList );
    if ( BaseTagList )
      otv_BaseTagList_validate( table + BaseTagList, otvalid );

    /* BaseScriptList */
    otv_BaseScriptList_validate( table + FT_NEXT_USHORT( p ), otvalid );

    OTV_EXIT;
  }