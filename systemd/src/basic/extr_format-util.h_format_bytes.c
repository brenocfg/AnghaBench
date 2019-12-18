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
typedef  int /*<<< orphan*/  uint64_t ;

/* Variables and functions */
 int FORMAT_BYTES_BELOW_POINT ; 
 int FORMAT_BYTES_TRAILING_B ; 
 int FORMAT_BYTES_USE_IEC ; 
 char* format_bytes_full (char*,size_t,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline char *format_bytes(char *buf, size_t l, uint64_t t) {
        return format_bytes_full(buf, l, t, FORMAT_BYTES_USE_IEC | FORMAT_BYTES_BELOW_POINT | FORMAT_BYTES_TRAILING_B);
}