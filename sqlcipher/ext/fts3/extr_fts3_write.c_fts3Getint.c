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

__attribute__((used)) static int fts3Getint(const char **pz){
  const char *z = *pz;
  int i = 0;
  while( (*z)>='0' && (*z)<='9' && i<214748363 ) i = 10*i + *(z++) - '0';
  *pz = z;
  return i;
}