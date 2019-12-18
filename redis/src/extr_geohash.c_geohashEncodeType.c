#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_6__ {int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ GeoHashRange ;
typedef  int /*<<< orphan*/  GeoHashBits ;

/* Variables and functions */
 int geohashEncode (TYPE_1__*,TYPE_1__*,double,double,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  geohashGetCoordRange (TYPE_1__*,TYPE_1__*) ; 

int geohashEncodeType(double longitude, double latitude, uint8_t step, GeoHashBits *hash) {
    GeoHashRange r[2] = {{0}};
    geohashGetCoordRange(&r[0], &r[1]);
    return geohashEncode(&r[0], &r[1], longitude, latitude, step, hash);
}