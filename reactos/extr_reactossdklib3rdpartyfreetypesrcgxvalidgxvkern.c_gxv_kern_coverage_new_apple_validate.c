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
 int /*<<< orphan*/  kernCrossStream ; 
 int /*<<< orphan*/  kernVariation ; 
 int /*<<< orphan*/  kernVertical ; 

__attribute__((used)) static FT_Bool
  gxv_kern_coverage_new_apple_validate( FT_UShort      coverage,
                                        FT_UShort*     format,
                                        GXV_Validator  gxvalid )
  {
    /* new Apple-dialect */
#ifdef GXV_LOAD_TRACE_VARS
    FT_Bool  kernVertical;
    FT_Bool  kernCrossStream;
    FT_Bool  kernVariation;
#endif

    FT_UNUSED( gxvalid );


    /* reserved bits = 0 */
    if ( coverage & 0x1FFC )
      return FALSE;

#ifdef GXV_LOAD_TRACE_VARS
    kernVertical    = FT_BOOL( ( coverage >> 15 ) & 1 );
    kernCrossStream = FT_BOOL( ( coverage >> 14 ) & 1 );
    kernVariation   = FT_BOOL( ( coverage >> 13 ) & 1 );
#endif

    *format = (FT_UShort)( coverage & 0x0003 );

    GXV_TRACE(( "new Apple-dialect: "
                "horizontal=%d, cross-stream=%d, variation=%d, format=%d\n",
                 !kernVertical, kernCrossStream, kernVariation, *format ));

    GXV_TRACE(( "kerning values in Apple format subtable are ignored\n" ));

    return TRUE;
  }