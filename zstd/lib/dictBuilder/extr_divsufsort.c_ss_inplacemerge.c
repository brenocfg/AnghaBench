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
 int ss_compare (unsigned char const*,int const*,int const*,int) ; 
 int /*<<< orphan*/  ss_rotate (int*,int*,int*) ; 

__attribute__((used)) static
void
ss_inplacemerge(const unsigned char *T, const int *PA,
                int *first, int *middle, int *last,
                int depth) {
  const int *p;
  int *a, *b;
  int len, half;
  int q, r;
  int x;

  for(;;) {
    if(*(last - 1) < 0) { x = 1; p = PA + ~*(last - 1); }
    else                { x = 0; p = PA +  *(last - 1); }
    for(a = first, len = middle - first, half = len >> 1, r = -1;
        0 < len;
        len = half, half >>= 1) {
      b = a + half;
      q = ss_compare(T, PA + ((0 <= *b) ? *b : ~*b), p, depth);
      if(q < 0) {
        a = b + 1;
        half -= (len & 1) ^ 1;
      } else {
        r = q;
      }
    }
    if(a < middle) {
      if(r == 0) { *a = ~*a; }
      ss_rotate(a, middle, last);
      last -= middle - a;
      middle = a;
      if(first == middle) { break; }
    }
    --last;
    if(x != 0) { while(*--last < 0) { } }
    if(middle == last) { break; }
  }
}