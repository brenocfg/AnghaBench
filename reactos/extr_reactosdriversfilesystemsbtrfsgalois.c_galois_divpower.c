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
typedef  size_t UINT8 ;
typedef  scalar_t__ UINT32 ;

/* Variables and functions */
 size_t* gilog ; 
 size_t* glog ; 

void galois_divpower(UINT8* data, UINT8 div, UINT32 len) {
    while (len > 0) {
        if (data[0] != 0) {
            if (gilog[data[0]] <= div)
                data[0] = glog[(gilog[data[0]] + (255 - div)) % 255];
            else
                data[0] = glog[(gilog[data[0]] - div) % 255];
        }

        data++;
        len--;
    }
}