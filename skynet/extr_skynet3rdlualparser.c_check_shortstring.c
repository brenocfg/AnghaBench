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
typedef  int lu_byte ;
typedef  int /*<<< orphan*/  TValue ;

/* Variables and functions */
 scalar_t__ ttisshrstring (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static lu_byte check_shortstring(const TValue *k, int sizek) {
  int i;
  for (i=0;i<sizek;i++) {
    if (ttisshrstring(&k[i]))
      return 0;
  }
  return 1;
}