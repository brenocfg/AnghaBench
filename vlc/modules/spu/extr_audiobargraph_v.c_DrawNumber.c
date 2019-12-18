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
typedef  int /*<<< orphan*/  plane_t ;

/* Variables and functions */
 int /*<<< orphan*/  DrawHLine (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  black ; 

__attribute__((used)) static void DrawNumber(plane_t *p, int h, const uint8_t data[5], int l)
{
    for (int i = 0; i < 5; i++) {
        uint8_t x = data[i];
        for (int j = 0; j < 7; j++) {
            x <<= 1;
            if (x & 0x80)
                DrawHLine(p, h - l + 2 - 1 - i, 12 + j, black, 1);
        }
    }
}