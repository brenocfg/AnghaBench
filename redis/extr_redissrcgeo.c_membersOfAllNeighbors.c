#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  robj ;
typedef  int /*<<< orphan*/  neighbors ;
typedef  int /*<<< orphan*/  geoArray ;
struct TYPE_16__ {unsigned int min; unsigned int max; } ;
struct TYPE_15__ {unsigned int min; unsigned int max; } ;
struct TYPE_14__ {int /*<<< orphan*/  member_0; } ;
struct TYPE_19__ {TYPE_4__ latitude; TYPE_3__ longitude; TYPE_2__ member_0; } ;
struct TYPE_18__ {scalar_t__ bits; scalar_t__ step; } ;
struct TYPE_13__ {TYPE_6__ south_west; TYPE_6__ south_east; TYPE_6__ north_west; TYPE_6__ north_east; TYPE_6__ west; TYPE_6__ east; TYPE_6__ south; TYPE_6__ north; } ;
struct TYPE_17__ {TYPE_1__ neighbors; TYPE_6__ hash; } ;
typedef  int /*<<< orphan*/  GeoHashRange ;
typedef  TYPE_5__ GeoHashRadius ;
typedef  TYPE_6__ GeoHashBits ;
typedef  TYPE_7__ GeoHashArea ;

/* Variables and functions */
 int /*<<< orphan*/  D (char*,...) ; 
 scalar_t__ HASHISZERO (TYPE_6__) ; 
 int /*<<< orphan*/  geohashDecode (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_6__,TYPE_7__*) ; 
 int /*<<< orphan*/  geohashGetCoordRange (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ membersOfGeoHashBox (int /*<<< orphan*/ *,TYPE_6__,int /*<<< orphan*/ *,double,double,double) ; 

int membersOfAllNeighbors(robj *zobj, GeoHashRadius n, double lon, double lat, double radius, geoArray *ga) {
    GeoHashBits neighbors[9];
    unsigned int i, count = 0, last_processed = 0;
    int debugmsg = 0;

    neighbors[0] = n.hash;
    neighbors[1] = n.neighbors.north;
    neighbors[2] = n.neighbors.south;
    neighbors[3] = n.neighbors.east;
    neighbors[4] = n.neighbors.west;
    neighbors[5] = n.neighbors.north_east;
    neighbors[6] = n.neighbors.north_west;
    neighbors[7] = n.neighbors.south_east;
    neighbors[8] = n.neighbors.south_west;

    /* For each neighbor (*and* our own hashbox), get all the matching
     * members and add them to the potential result list. */
    for (i = 0; i < sizeof(neighbors) / sizeof(*neighbors); i++) {
        if (HASHISZERO(neighbors[i])) {
            if (debugmsg) D("neighbors[%d] is zero",i);
            continue;
        }

        /* Debugging info. */
        if (debugmsg) {
            GeoHashRange long_range, lat_range;
            geohashGetCoordRange(&long_range,&lat_range);
            GeoHashArea myarea = {{0}};
            geohashDecode(long_range, lat_range, neighbors[i], &myarea);

            /* Dump center square. */
            D("neighbors[%d]:\n",i);
            D("area.longitude.min: %f\n", myarea.longitude.min);
            D("area.longitude.max: %f\n", myarea.longitude.max);
            D("area.latitude.min: %f\n", myarea.latitude.min);
            D("area.latitude.max: %f\n", myarea.latitude.max);
            D("\n");
        }

        /* When a huge Radius (in the 5000 km range or more) is used,
         * adjacent neighbors can be the same, leading to duplicated
         * elements. Skip every range which is the same as the one
         * processed previously. */
        if (last_processed &&
            neighbors[i].bits == neighbors[last_processed].bits &&
            neighbors[i].step == neighbors[last_processed].step)
        {
            if (debugmsg)
                D("Skipping processing of %d, same as previous\n",i);
            continue;
        }
        count += membersOfGeoHashBox(zobj, neighbors[i], ga, lon, lat, radius);
        last_processed = i;
    }
    return count;
}