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
typedef  int int64_t ;

/* Variables and functions */
 int sqrt (int) ; 

__attribute__((used)) static bool IsSimilar( int u, int v,
                       int refu, int refv, int reflength,
                       int i_satthres, int i_simthres )
{
    int length = sqrt(u * u + v * v);

    int diffu = refu * length - u * reflength;
    int diffv = refv * length - v * reflength;
    int64_t difflen2 = diffu * diffu + diffv * diffv;
    int64_t thres = length * reflength;
    thres *= thres;
    return length > i_satthres && (difflen2 * i_simthres < thres);
}