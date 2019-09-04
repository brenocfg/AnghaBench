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
 int /*<<< orphan*/  GXV_TRACE (char*) ; 
 scalar_t__ KERN_ALLOWS_MS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  cross_stream ; 
 int /*<<< orphan*/  horizontal ; 

__attribute__((used)) static FT_Bool
  gxv_kern_coverage_classic_apple_validate( FT_UShort      coverage,
                                            FT_UShort*     format,
                                            GXV_Validator  gxvalid )
  {
    /* classic Apple-dialect */
#ifdef GXV_LOAD_TRACE_VARS
    FT_Bool  horizontal;
    FT_Bool  cross_stream;
#endif


    /* check expected flags, but don't check if MS-dialect is impossible */
    if ( !( coverage & 0xFD00 ) && KERN_ALLOWS_MS( gxvalid ) )
      return FALSE;

    /* reserved bits = 0 */
    if ( coverage & 0x02FC )
      return FALSE;

#ifdef GXV_LOAD_TRACE_VARS
    horizontal   = FT_BOOL( ( coverage >> 15 ) & 1 );
    cross_stream = FT_BOOL( ( coverage >> 13 ) & 1 );
#endif

    *format = (FT_UShort)( coverage & 0x0003 );

    GXV_TRACE(( "classic Apple-dialect: "
                "horizontal=%d, cross-stream=%d, format=%d\n",
                 horizontal, cross_stream, *format ));

    /* format 1 requires GX State Machine, too new for classic */
    if ( *format == 1 )
      return FALSE;

    GXV_TRACE(( "kerning values in Apple format subtable are ignored\n" ));

    return TRUE;
  }