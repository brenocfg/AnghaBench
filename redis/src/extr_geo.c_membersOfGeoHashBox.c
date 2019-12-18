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
typedef  int /*<<< orphan*/  robj ;
typedef  int /*<<< orphan*/  geoArray ;
typedef  int /*<<< orphan*/  GeoHashFix52Bits ;
typedef  int /*<<< orphan*/  GeoHashBits ;

/* Variables and functions */
 int geoGetPointsInRange (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,double,double,double,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scoresOfGeoHashBox (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int membersOfGeoHashBox(robj *zobj, GeoHashBits hash, geoArray *ga, double lon, double lat, double radius) {
    GeoHashFix52Bits min, max;

    scoresOfGeoHashBox(hash,&min,&max);
    return geoGetPointsInRange(zobj, min, max, lon, lat, radius, ga);
}