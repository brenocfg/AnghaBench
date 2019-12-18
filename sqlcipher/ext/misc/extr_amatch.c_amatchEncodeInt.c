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

__attribute__((used)) static void amatchEncodeInt(int x, char *z){
  static const char a[] = 
    "0123456789"
    "ABCDEFGHIJ"
    "KLMNOPQRST"
    "UVWXYZ^abc"
    "defghijklm"
    "nopqrstuvw"
    "xyz~";
  z[0] = a[(x>>18)&0x3f];
  z[1] = a[(x>>12)&0x3f];
  z[2] = a[(x>>6)&0x3f];
  z[3] = a[x&0x3f];
}