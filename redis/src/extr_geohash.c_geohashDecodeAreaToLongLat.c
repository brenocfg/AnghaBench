#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int min; int max; } ;
struct TYPE_5__ {int min; int max; } ;
struct TYPE_7__ {TYPE_2__ latitude; TYPE_1__ longitude; } ;
typedef  TYPE_3__ GeoHashArea ;

/* Variables and functions */

int geohashDecodeAreaToLongLat(const GeoHashArea *area, double *xy) {
    if (!xy) return 0;
    xy[0] = (area->longitude.min + area->longitude.max) / 2;
    xy[1] = (area->latitude.min + area->latitude.max) / 2;
    return 1;
}