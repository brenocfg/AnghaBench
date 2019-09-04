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
typedef  int WCHAR ;

/* Variables and functions */
 int* hexDigits ; 

__attribute__((used)) static inline void pct_encode_val(WCHAR val, WCHAR *dest) {
    dest[0] = '%';
    dest[1] = hexDigits[(val >> 4) & 0xf];
    dest[2] = hexDigits[val & 0xf];
}