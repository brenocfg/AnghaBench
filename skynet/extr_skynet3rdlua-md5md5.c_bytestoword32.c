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
typedef  int WORD32 ;

/* Variables and functions */

__attribute__((used)) static void bytestoword32 (WORD32 *x, const char *pt) {
  int i;
  for (i=0; i<16; i++) {
    int j=i*4;
    x[i] = (((WORD32)(unsigned char)pt[j+3] << 8 |
           (WORD32)(unsigned char)pt[j+2]) << 8 |
           (WORD32)(unsigned char)pt[j+1]) << 8 |
           (WORD32)(unsigned char)pt[j];
  }

}