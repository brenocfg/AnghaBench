#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vlc_fourcc_t ;
typedef  int /*<<< orphan*/ * cvt_t ;
struct TYPE_2__ {scalar_t__ src; scalar_t__ dst; int /*<<< orphan*/ * convert; } ;

/* Variables and functions */
 TYPE_1__* cvt_directs ; 

__attribute__((used)) static cvt_t FindConversion(vlc_fourcc_t src, vlc_fourcc_t dst)
{
    for (int i = 0; cvt_directs[i].convert; i++) {
        if (cvt_directs[i].src == src &&
            cvt_directs[i].dst == dst)
            return cvt_directs[i].convert;
    }
    return NULL;
}