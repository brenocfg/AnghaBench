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
typedef  int UINT8 ;

/* Variables and functions */
 scalar_t__* gilog ; 
 int* glog ; 

UINT8 gdiv(UINT8 a, UINT8 b) {
    if (b == 0) {
        return 0xff; // shouldn't happen
    } else if (a == 0) {
        return 0;
    } else {
        if (gilog[a] >= gilog[b])
            return glog[(gilog[a] - gilog[b]) % 255];
        else
            return glog[255-((gilog[b] - gilog[a]) % 255)];
    }
}