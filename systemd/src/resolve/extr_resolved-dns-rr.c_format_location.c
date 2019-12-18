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
typedef  int uint8_t ;
typedef  unsigned int uint32_t ;

/* Variables and functions */
 scalar_t__ asprintf (char**,char*,int,int,int,char,int,int,int,char,double,double,double,double) ; 
 int exp10 (double) ; 

__attribute__((used)) static char* format_location(uint32_t latitude, uint32_t longitude, uint32_t altitude,
                             uint8_t size, uint8_t horiz_pre, uint8_t vert_pre) {
        char *s;
        char NS = latitude >= 1U<<31 ? 'N' : 'S';
        char EW = longitude >= 1U<<31 ? 'E' : 'W';

        int lat = latitude >= 1U<<31 ? (int) (latitude - (1U<<31)) : (int) ((1U<<31) - latitude);
        int lon = longitude >= 1U<<31 ? (int) (longitude - (1U<<31)) : (int) ((1U<<31) - longitude);
        double alt = altitude >= 10000000u ? altitude - 10000000u : -(double)(10000000u - altitude);
        double siz = (size >> 4) * exp10((double) (size & 0xF));
        double hor = (horiz_pre >> 4) * exp10((double) (horiz_pre & 0xF));
        double ver = (vert_pre >> 4) * exp10((double) (vert_pre & 0xF));

        if (asprintf(&s, "%d %d %.3f %c %d %d %.3f %c %.2fm %.2fm %.2fm %.2fm",
                     (lat / 60000 / 60),
                     (lat / 60000) % 60,
                     (lat % 60000) / 1000.,
                     NS,
                     (lon / 60000 / 60),
                     (lon / 60000) % 60,
                     (lon % 60000) / 1000.,
                     EW,
                     alt / 100.,
                     siz / 100.,
                     hor / 100.,
                     ver / 100.) < 0)
                return NULL;

        return s;
}