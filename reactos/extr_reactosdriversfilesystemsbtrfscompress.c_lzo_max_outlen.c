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
typedef  int UINT32 ;

/* Variables and functions */

__attribute__((used)) static __inline UINT32 lzo_max_outlen(UINT32 inlen) {
    return inlen + (inlen / 16) + 64 + 3; // formula comes from LZO.FAQ
}