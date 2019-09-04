#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  buffer; } ;
struct TYPE_5__ {int rows; int /*<<< orphan*/  buffer; scalar_t__ pitch; } ;
typedef  int FT_ULong ;
typedef  int /*<<< orphan*/  FT_Memory ;
typedef  scalar_t__ FT_Int ;
typedef  int /*<<< orphan*/  FT_Error ;
typedef  TYPE_1__ FT_Bitmap ;
typedef  TYPE_2__* FTC_SBit ;

/* Variables and functions */
 int /*<<< orphan*/  FT_ALLOC (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  FT_Err_Ok ; 
 int /*<<< orphan*/  FT_MEM_COPY (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static FT_Error
  ftc_sbit_copy_bitmap( FTC_SBit    sbit,
                        FT_Bitmap*  bitmap,
                        FT_Memory   memory )
  {
    FT_Error  error;
    FT_Int    pitch = bitmap->pitch;
    FT_ULong  size;


    if ( pitch < 0 )
      pitch = -pitch;

    size = (FT_ULong)pitch * bitmap->rows;
    if ( !size )
      return FT_Err_Ok;

    if ( !FT_ALLOC( sbit->buffer, size ) )
      FT_MEM_COPY( sbit->buffer, bitmap->buffer, size );

    return error;
  }