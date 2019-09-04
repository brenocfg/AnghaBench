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
typedef  int /*<<< orphan*/  GXV_Validator ;
typedef  int FT_UShort ;
typedef  int /*<<< orphan*/  FT_Bool ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FT_UNUSED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GXV_TRACE (char*) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  cross_stream ; 
 int /*<<< orphan*/  horizontal ; 
 int /*<<< orphan*/  minimum ; 
 int /*<<< orphan*/  override ; 

__attribute__((used)) static FT_Bool
  gxv_kern_coverage_classic_microsoft_validate( FT_UShort      coverage,
                                                FT_UShort*     format,
                                                GXV_Validator  gxvalid )
  {
    /* classic Microsoft-dialect */
#ifdef GXV_LOAD_TRACE_VARS
    FT_Bool  horizontal;
    FT_Bool  minimum;
    FT_Bool  cross_stream;
    FT_Bool  override;
#endif

    FT_UNUSED( gxvalid );


    /* reserved bits = 0 */
    if ( coverage & 0xFDF0 )
      return FALSE;

#ifdef GXV_LOAD_TRACE_VARS
    horizontal   = FT_BOOL(   coverage        & 1 );
    minimum      = FT_BOOL( ( coverage >> 1 ) & 1 );
    cross_stream = FT_BOOL( ( coverage >> 2 ) & 1 );
    override     = FT_BOOL( ( coverage >> 3 ) & 1 );
#endif

    *format = (FT_UShort)( ( coverage >> 8 ) & 0x0003 );

    GXV_TRACE(( "classic Microsoft-dialect: "
                "horizontal=%d, minimum=%d, cross-stream=%d, "
                "override=%d, format=%d\n",
                horizontal, minimum, cross_stream, override, *format ));

    if ( *format == 2 )
      GXV_TRACE((
        "kerning values in Microsoft format 2 subtable are ignored\n" ));

    return TRUE;
  }