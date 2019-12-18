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
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_3__ {int /*<<< orphan*/  step; int /*<<< orphan*/  bits; } ;
typedef  TYPE_1__ GeoHashBits ;

/* Variables and functions */
 int /*<<< orphan*/  GEO_STEP_MAX ; 
 int geohashDecodeToLongLatWGS84 (TYPE_1__,double*) ; 

int decodeGeohash(double bits, double *xy) {
    GeoHashBits hash = { .bits = (uint64_t)bits, .step = GEO_STEP_MAX };
    return geohashDecodeToLongLatWGS84(hash, xy);
}