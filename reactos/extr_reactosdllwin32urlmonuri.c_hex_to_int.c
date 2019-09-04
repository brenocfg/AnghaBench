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
typedef  char WCHAR ;

/* Variables and functions */

__attribute__((used)) static int hex_to_int(WCHAR val) {
    if(val >= '0' && val <= '9')
        return val - '0';
    else if(val >= 'a' && val <= 'f')
        return val - 'a' + 10;
    else if(val >= 'A' && val <= 'F')
        return val - 'A' + 10;

    return -1;
}