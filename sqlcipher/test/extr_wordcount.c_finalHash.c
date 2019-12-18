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
 int /*<<< orphan*/  sqlite3_snprintf (int,char*,char*,unsigned int,unsigned int) ; 

__attribute__((used)) static void finalHash(unsigned int *a, char *z){
  a[3] += a[1] + a[4] + a[0];
  a[4] += a[2] + a[3];
  sqlite3_snprintf(17, z, "%08x%08x", a[3], a[4]);
}