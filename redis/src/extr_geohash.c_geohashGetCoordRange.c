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
struct TYPE_4__ {int /*<<< orphan*/  min; int /*<<< orphan*/  max; } ;
typedef  TYPE_1__ GeoHashRange ;

/* Variables and functions */
 int /*<<< orphan*/  GEO_LAT_MAX ; 
 int /*<<< orphan*/  GEO_LAT_MIN ; 
 int /*<<< orphan*/  GEO_LONG_MAX ; 
 int /*<<< orphan*/  GEO_LONG_MIN ; 

void geohashGetCoordRange(GeoHashRange *long_range, GeoHashRange *lat_range) {
    /* These are constraints from EPSG:900913 / EPSG:3785 / OSGEO:41001 */
    /* We can't geocode at the north/south pole. */
    long_range->max = GEO_LONG_MAX;
    long_range->min = GEO_LONG_MIN;
    lat_range->max = GEO_LAT_MAX;
    lat_range->min = GEO_LAT_MIN;
}