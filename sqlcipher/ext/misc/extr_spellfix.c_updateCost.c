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
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static void updateCost(
  unsigned int *m,
  int i,
  int j,
  int iCost
){
  unsigned int b;
  assert( iCost>=0 );
  assert( iCost<10000 );
  b = m[j] + iCost;
  if( b<m[i] ) m[i] = b;
}