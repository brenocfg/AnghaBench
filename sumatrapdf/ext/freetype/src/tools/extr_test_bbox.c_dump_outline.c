#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  yMax; int /*<<< orphan*/  xMax; int /*<<< orphan*/  yMin; int /*<<< orphan*/  xMin; } ;
typedef  int /*<<< orphan*/  FT_Outline ;
typedef  TYPE_1__ FT_BBox ;

/* Variables and functions */
 int /*<<< orphan*/  FT_Outline_Get_BBox (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  FT_Outline_Get_CBox (int /*<<< orphan*/ *,TYPE_1__*) ; 
 double XVAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,double,double,double,double) ; 

__attribute__((used)) static void
  dump_outline( FT_Outline*  outline )
  {
    FT_BBox  bbox;

    /* compute and display cbox */
    FT_Outline_Get_CBox( outline, &bbox );
    printf( "cbox = [%.2f %.2f %.2f %.2f]\n",
             XVAL( bbox.xMin ),
             XVAL( bbox.yMin ),
             XVAL( bbox.xMax ),
             XVAL( bbox.yMax ) );

    /* compute and display bbox */
    FT_Outline_Get_BBox( outline, &bbox );
    printf( "bbox = [%.2f %.2f %.2f %.2f]\n",
             XVAL( bbox.xMin ),
             XVAL( bbox.yMin ),
             XVAL( bbox.xMax ),
             XVAL( bbox.yMax ) );
  }