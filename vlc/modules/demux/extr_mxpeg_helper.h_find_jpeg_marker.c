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

/* Variables and functions */

__attribute__((used)) static uint8_t find_jpeg_marker(int *position, const uint8_t *data, int size)
{
    for (int i = *position; i + 1 < size; i++) {
        if (data[i] != 0xff)
            continue;
        if (data[i + 1] != 0xff) {
            *position = i + 2;
            return data[i + 1];
        }
    }
    return 0xff;
}