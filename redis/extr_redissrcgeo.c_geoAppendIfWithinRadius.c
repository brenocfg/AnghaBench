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
typedef  int /*<<< orphan*/  sds ;
struct TYPE_3__ {double longitude; double latitude; double dist; double score; int /*<<< orphan*/  member; } ;
typedef  TYPE_1__ geoPoint ;
typedef  int /*<<< orphan*/  geoArray ;

/* Variables and functions */
 int C_ERR ; 
 int C_OK ; 
 int /*<<< orphan*/  decodeGeohash (double,double*) ; 
 TYPE_1__* geoArrayAppend (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  geohashGetDistanceIfInRadiusWGS84 (double,double,double,double,double,double*) ; 

int geoAppendIfWithinRadius(geoArray *ga, double lon, double lat, double radius, double score, sds member) {
    double distance, xy[2];

    if (!decodeGeohash(score,xy)) return C_ERR; /* Can't decode. */
    /* Note that geohashGetDistanceIfInRadiusWGS84() takes arguments in
     * reverse order: longitude first, latitude later. */
    if (!geohashGetDistanceIfInRadiusWGS84(lon,lat, xy[0], xy[1],
                                           radius, &distance))
    {
        return C_ERR;
    }

    /* Append the new element. */
    geoPoint *gp = geoArrayAppend(ga);
    gp->longitude = xy[0];
    gp->latitude = xy[1];
    gp->dist = distance;
    gp->member = member;
    gp->score = score;
    return C_OK;
}