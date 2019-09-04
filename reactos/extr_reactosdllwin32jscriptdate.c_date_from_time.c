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
typedef  int DOUBLE ;

/* Variables and functions */
 int NAN ; 
 int day_within_year (int) ; 
 int in_leap_year (int) ; 
 scalar_t__ isnan (int) ; 
 int month_from_time (int) ; 

__attribute__((used)) static inline DOUBLE date_from_time(DOUBLE time)
{
    int dwy = day_within_year(time);
    int ily = in_leap_year(time);
    int mft = month_from_time(time);

    if(isnan(time))
        return NAN;

    if(mft==0) return dwy+1;
    if(mft==1) return dwy-30;
    if(mft==2) return dwy-58-ily;
    if(mft==3) return dwy-89-ily;
    if(mft==4) return dwy-119-ily;
    if(mft==5) return dwy-150-ily;
    if(mft==6) return dwy-180-ily;
    if(mft==7) return dwy-211-ily;
    if(mft==8) return dwy-242-ily;
    if(mft==9) return dwy-272-ily;
    if(mft==10) return dwy-303-ily;
    return dwy-333-ily;
}