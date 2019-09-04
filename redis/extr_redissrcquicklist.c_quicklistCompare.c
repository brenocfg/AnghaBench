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

/* Variables and functions */
 int ziplistCompare (unsigned char*,unsigned char*,int) ; 

int quicklistCompare(unsigned char *p1, unsigned char *p2, int p2_len) {
    return ziplistCompare(p1, p2, p2_len);
}