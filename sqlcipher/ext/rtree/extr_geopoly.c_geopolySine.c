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

/* Variables and functions */
 double GEOPOLY_PI ; 
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static double geopolySine(double r){
  assert( r>=-0.5*GEOPOLY_PI && r<=2.0*GEOPOLY_PI );
  if( r>=1.5*GEOPOLY_PI ){
    r -= 2.0*GEOPOLY_PI;
  }
  if( r>=0.5*GEOPOLY_PI ){
    return -geopolySine(r-GEOPOLY_PI);
  }else{
    double r2 = r*r;
    double r3 = r2*r;
    double r5 = r3*r2;
    return 0.9996949*r - 0.1656700*r3 + 0.0075134*r5;
  }
}