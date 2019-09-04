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
typedef  int int32_t ;

/* Variables and functions */

__attribute__((used)) static inline int32_t
get_length(const uint8_t * data) {
	const uint8_t * b = (const uint8_t *)data;
	int32_t len = b[0] | b[1]<<8 | b[2]<<16 | b[3]<<24;
	return len;
}