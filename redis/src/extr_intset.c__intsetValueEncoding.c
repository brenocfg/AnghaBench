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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ int64_t ;

/* Variables and functions */
 scalar_t__ INT16_MAX ; 
 scalar_t__ INT16_MIN ; 
 scalar_t__ INT32_MAX ; 
 scalar_t__ INT32_MIN ; 
 int /*<<< orphan*/  INTSET_ENC_INT16 ; 
 int /*<<< orphan*/  INTSET_ENC_INT32 ; 
 int /*<<< orphan*/  INTSET_ENC_INT64 ; 

__attribute__((used)) static uint8_t _intsetValueEncoding(int64_t v) {
    if (v < INT32_MIN || v > INT32_MAX)
        return INTSET_ENC_INT64;
    else if (v < INT16_MIN || v > INT16_MAX)
        return INTSET_ENC_INT32;
    else
        return INTSET_ENC_INT16;
}