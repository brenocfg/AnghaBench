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
typedef  int /*<<< orphan*/  client ;

/* Variables and functions */
 int C_ERR ; 
 scalar_t__ C_OK ; 
 double GEO_LAT_MAX ; 
 double GEO_LAT_MIN ; 
 double GEO_LONG_MAX ; 
 double GEO_LONG_MIN ; 
 int /*<<< orphan*/  addReplySds (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ getDoubleFromObjectOrReply (int /*<<< orphan*/ *,int /*<<< orphan*/ *,double*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sdscatprintf (int /*<<< orphan*/ ,char*,double,double) ; 
 int /*<<< orphan*/  sdsempty () ; 

int extractLongLatOrReply(client *c, robj **argv, double *xy) {
    int i;
    for (i = 0; i < 2; i++) {
        if (getDoubleFromObjectOrReply(c, argv[i], xy + i, NULL) !=
            C_OK) {
            return C_ERR;
        }
    }
    if (xy[0] < GEO_LONG_MIN || xy[0] > GEO_LONG_MAX ||
        xy[1] < GEO_LAT_MIN  || xy[1] > GEO_LAT_MAX) {
        addReplySds(c, sdscatprintf(sdsempty(),
            "-ERR invalid longitude,latitude pair %f,%f\r\n",xy[0],xy[1]));
        return C_ERR;
    }
    return C_OK;
}