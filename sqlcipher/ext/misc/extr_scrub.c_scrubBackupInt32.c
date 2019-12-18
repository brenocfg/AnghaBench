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
typedef  int u8 ;
typedef  int u32 ;

/* Variables and functions */

__attribute__((used)) static u32 scrubBackupInt32(const u8 *a){
  u32 v = a[3];
  v += ((u32)a[2])<<8;
  v += ((u32)a[1])<<16;
  v += ((u32)a[0])<<24;
  return v;
}