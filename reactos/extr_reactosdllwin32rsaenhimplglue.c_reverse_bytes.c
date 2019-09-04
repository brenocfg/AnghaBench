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
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */

__attribute__((used)) static inline void reverse_bytes(BYTE *pbData, DWORD dwLen) {
    BYTE swap;
    DWORD i;

    for (i=0; i<dwLen/2; i++) {
        swap = pbData[i];
        pbData[i] = pbData[dwLen-i-1];
        pbData[dwLen-i-1] = swap;
    }
}