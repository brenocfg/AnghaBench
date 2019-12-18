#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_7__ ;
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_21__ {int /*<<< orphan*/  face; } ;
struct TYPE_20__ {int horiResolution; int vertResolution; scalar_t__ type; } ;
struct TYPE_19__ {scalar_t__ (* set_sbit_strike ) (TYPE_4__*,TYPE_6__*,int /*<<< orphan*/ *) ;} ;
struct TYPE_18__ {int /*<<< orphan*/  sfnt; } ;
struct TYPE_16__ {int /*<<< orphan*/  ppem; } ;
struct TYPE_17__ {int strike_index; TYPE_2__ ttmetrics; int /*<<< orphan*/  point_size; TYPE_1__* metrics; } ;
struct TYPE_15__ {scalar_t__ x_ppem; scalar_t__ y_ppem; } ;
typedef  TYPE_3__* TT_Size ;
typedef  TYPE_4__* TT_Face ;
typedef  TYPE_5__* SFNT_Service ;
typedef  int /*<<< orphan*/  FT_ULong ;
typedef  int FT_UInt ;
typedef  TYPE_6__* FT_Size_Request ;
typedef  TYPE_7__* FT_Size ;
typedef  scalar_t__ FT_Error ;

/* Variables and functions */
 scalar_t__ FT_Err_Ok ; 
 scalar_t__ FT_HAS_FIXED_SIZES (int /*<<< orphan*/ ) ; 
 scalar_t__ FT_IS_SCALABLE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FT_MulDiv (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  FT_Request_Metrics (int /*<<< orphan*/ ,TYPE_6__*) ; 
 scalar_t__ FT_SIZE_REQUEST_TYPE_SCALES ; 
 scalar_t__ stub1 (TYPE_4__*,TYPE_6__*,int /*<<< orphan*/ *) ; 
 scalar_t__ tt_size_reset (TYPE_3__*,int /*<<< orphan*/ ) ; 
 scalar_t__ tt_size_select (TYPE_7__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static FT_Error
  tt_size_request( FT_Size          size,
                   FT_Size_Request  req )
  {
    TT_Size   ttsize = (TT_Size)size;
    FT_Error  error  = FT_Err_Ok;


#ifdef TT_CONFIG_OPTION_EMBEDDED_BITMAPS

    if ( FT_HAS_FIXED_SIZES( size->face ) )
    {
      TT_Face       ttface = (TT_Face)size->face;
      SFNT_Service  sfnt   = (SFNT_Service)ttface->sfnt;
      FT_ULong      strike_index;


      error = sfnt->set_sbit_strike( ttface, req, &strike_index );

      if ( error )
        ttsize->strike_index = 0xFFFFFFFFUL;
      else
        return tt_size_select( size, strike_index );
    }

#endif /* TT_CONFIG_OPTION_EMBEDDED_BITMAPS */

    FT_Request_Metrics( size->face, req );

    if ( FT_IS_SCALABLE( size->face ) )
    {
      error = tt_size_reset( ttsize, 0 );

#ifdef TT_USE_BYTECODE_INTERPRETER
      /* for the `MPS' bytecode instruction we need the point size */
      if ( !error )
      {
        FT_UInt  resolution =
                   ttsize->metrics->x_ppem > ttsize->metrics->y_ppem
                     ? req->horiResolution
                     : req->vertResolution;


        /* if we don't have a resolution value, assume 72dpi */
        if ( req->type == FT_SIZE_REQUEST_TYPE_SCALES ||
             !resolution                              )
          resolution = 72;

        ttsize->point_size = FT_MulDiv( ttsize->ttmetrics.ppem,
                                        64 * 72,
                                        resolution );
      }
#endif
    }

    return error;
  }