#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  gray_TRaster ;
typedef  TYPE_1__* gray_PRaster ;
struct TYPE_3__ {int /*<<< orphan*/  memory; } ;
typedef  scalar_t__ FT_Raster ;
typedef  int /*<<< orphan*/  FT_Memory ;
typedef  int FT_Error ;

/* Variables and functions */
 int /*<<< orphan*/  FT_ALLOC (TYPE_1__*,int) ; 

__attribute__((used)) static int
  gray_raster_new( FT_Memory   memory,
                   FT_Raster*  araster )
  {
    FT_Error      error;
    gray_PRaster  raster = NULL;


    *araster = 0;
    if ( !FT_ALLOC( raster, sizeof ( gray_TRaster ) ) )
    {
      raster->memory = memory;
      *araster       = (FT_Raster)raster;
    }

    return error;
  }