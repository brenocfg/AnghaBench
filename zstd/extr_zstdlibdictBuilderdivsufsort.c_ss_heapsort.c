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
 int /*<<< orphan*/  SWAP (int,int) ; 
 int /*<<< orphan*/  ss_fixdown (unsigned char const*,int const*,int*,int,int) ; 

__attribute__((used)) static
void
ss_heapsort(const unsigned char *Td, const int *PA, int *SA, int size) {
  int i, m;
  int t;

  m = size;
  if((size % 2) == 0) {
    m--;
    if(Td[PA[SA[m / 2]]] < Td[PA[SA[m]]]) { SWAP(SA[m], SA[m / 2]); }
  }

  for(i = m / 2 - 1; 0 <= i; --i) { ss_fixdown(Td, PA, SA, i, m); }
  if((size % 2) == 0) { SWAP(SA[0], SA[m]); ss_fixdown(Td, PA, SA, 0, m); }
  for(i = m - 1; 0 < i; --i) {
    t = SA[0], SA[0] = SA[i];
    ss_fixdown(Td, PA, SA, 0, i);
    SA[i] = t;
  }
}