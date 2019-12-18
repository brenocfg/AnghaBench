#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {TYPE_2__* font; } ;
struct TYPE_17__ {int /*<<< orphan*/  y_ppem; } ;
struct TYPE_16__ {TYPE_1__* face; } ;
struct TYPE_15__ {int type; } ;
struct TYPE_14__ {int pixel_height; } ;
struct TYPE_13__ {TYPE_3__ header; } ;
struct TYPE_12__ {TYPE_6__* available_sizes; } ;
typedef  TYPE_3__* FT_WinFNT_Header ;
typedef  TYPE_4__* FT_Size_Request ;
typedef  TYPE_5__* FT_Size ;
typedef  int FT_Long ;
typedef  scalar_t__ FT_Error ;
typedef  TYPE_6__ FT_Bitmap_Size ;
typedef  TYPE_7__* FNT_Face ;

/* Variables and functions */
 scalar_t__ FNT_Size_Select (TYPE_5__*,int /*<<< orphan*/ ) ; 
 scalar_t__ FT_ERR (int /*<<< orphan*/ ) ; 
 scalar_t__ FT_Err_Ok ; 
 int FT_REQUEST_HEIGHT (TYPE_4__*) ; 
#define  FT_SIZE_REQUEST_TYPE_NOMINAL 129 
#define  FT_SIZE_REQUEST_TYPE_REAL_DIM 128 
 scalar_t__ FT_THROW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Invalid_Pixel_Size ; 
 int /*<<< orphan*/  Unimplemented_Feature ; 

__attribute__((used)) static FT_Error
  FNT_Size_Request( FT_Size          size,
                    FT_Size_Request  req )
  {
    FNT_Face          face    = (FNT_Face)size->face;
    FT_WinFNT_Header  header  = &face->font->header;
    FT_Bitmap_Size*   bsize   = size->face->available_sizes;
    FT_Error          error   = FT_ERR( Invalid_Pixel_Size );
    FT_Long           height;


    height = FT_REQUEST_HEIGHT( req );
    height = ( height + 32 ) >> 6;

    switch ( req->type )
    {
    case FT_SIZE_REQUEST_TYPE_NOMINAL:
      if ( height == ( ( bsize->y_ppem + 32 ) >> 6 ) )
        error = FT_Err_Ok;
      break;

    case FT_SIZE_REQUEST_TYPE_REAL_DIM:
      if ( height == header->pixel_height )
        error = FT_Err_Ok;
      break;

    default:
      error = FT_THROW( Unimplemented_Feature );
      break;
    }

    if ( error )
      return error;
    else
      return FNT_Size_Select( size, 0 );
  }