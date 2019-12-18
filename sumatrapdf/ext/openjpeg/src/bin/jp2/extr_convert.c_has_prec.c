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

__attribute__((used)) static int has_prec(int val)
{
    if (val < 2) {
        return 1;
    }
    if (val < 4) {
        return 2;
    }
    if (val < 8) {
        return 3;
    }
    if (val < 16) {
        return 4;
    }
    if (val < 32) {
        return 5;
    }
    if (val < 64) {
        return 6;
    }
    if (val < 128) {
        return 7;
    }
    if (val < 256) {
        return 8;
    }
    if (val < 512) {
        return 9;
    }
    if (val < 1024) {
        return 10;
    }
    if (val < 2048) {
        return 11;
    }
    if (val < 4096) {
        return 12;
    }
    if (val < 8192) {
        return 13;
    }
    if (val < 16384) {
        return 14;
    }
    if (val < 32768) {
        return 15;
    }
    return 16;
}