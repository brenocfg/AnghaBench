#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int nVertex; } ;
typedef  TYPE_1__ GeoPoly ;

/* Variables and functions */
 double GeoX (TYPE_1__*,int) ; 
 double GeoY (TYPE_1__*,int) ; 

__attribute__((used)) static double geopolyArea(GeoPoly *p){
  double rArea = 0.0;
  int ii;
  for(ii=0; ii<p->nVertex-1; ii++){
    rArea += (GeoX(p,ii) - GeoX(p,ii+1))           /* (x0 - x1) */
              * (GeoY(p,ii) + GeoY(p,ii+1))        /* (y0 + y1) */
              * 0.5;
  }
  rArea += (GeoX(p,ii) - GeoX(p,0))                /* (xN - x0) */
           * (GeoY(p,ii) + GeoY(p,0))              /* (yN + y0) */
           * 0.5;
  return rArea;
}