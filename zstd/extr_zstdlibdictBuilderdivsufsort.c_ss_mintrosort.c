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
 int SS_INSERTIONSORT_THRESHOLD ; 
 int SS_MISORT_STACKSIZE ; 
 int /*<<< orphan*/  STACK_POP (int*,int*,int,int) ; 
 int /*<<< orphan*/  STACK_PUSH (int*,int*,int,int) ; 
 int /*<<< orphan*/  SWAP (int,int) ; 
 int /*<<< orphan*/  ss_heapsort (unsigned char const*,int const*,int*,int) ; 
 int ss_ilg (int) ; 
 int* ss_partition (int const*,int*,int*,int) ; 
 int* ss_pivot (unsigned char const*,int const*,int*,int*) ; 

__attribute__((used)) static
void
ss_mintrosort(const unsigned char *T, const int *PA,
              int *first, int *last,
              int depth) {
#define STACK_SIZE SS_MISORT_STACKSIZE
  struct { int *a, *b, c; int d; } stack[STACK_SIZE];
  const unsigned char *Td;
  int *a, *b, *c, *d, *e, *f;
  int s, t;
  int ssize;
  int limit;
  int v, x = 0;

  for(ssize = 0, limit = ss_ilg(last - first);;) {

    if((last - first) <= SS_INSERTIONSORT_THRESHOLD) {
#if 1 < SS_INSERTIONSORT_THRESHOLD
      if(1 < (last - first)) { ss_insertionsort(T, PA, first, last, depth); }
#endif
      STACK_POP(first, last, depth, limit);
      continue;
    }

    Td = T + depth;
    if(limit-- == 0) { ss_heapsort(Td, PA, first, last - first); }
    if(limit < 0) {
      for(a = first + 1, v = Td[PA[*first]]; a < last; ++a) {
        if((x = Td[PA[*a]]) != v) {
          if(1 < (a - first)) { break; }
          v = x;
          first = a;
        }
      }
      if(Td[PA[*first] - 1] < v) {
        first = ss_partition(PA, first, a, depth);
      }
      if((a - first) <= (last - a)) {
        if(1 < (a - first)) {
          STACK_PUSH(a, last, depth, -1);
          last = a, depth += 1, limit = ss_ilg(a - first);
        } else {
          first = a, limit = -1;
        }
      } else {
        if(1 < (last - a)) {
          STACK_PUSH(first, a, depth + 1, ss_ilg(a - first));
          first = a, limit = -1;
        } else {
          last = a, depth += 1, limit = ss_ilg(a - first);
        }
      }
      continue;
    }

    /* choose pivot */
    a = ss_pivot(Td, PA, first, last);
    v = Td[PA[*a]];
    SWAP(*first, *a);

    /* partition */
    for(b = first; (++b < last) && ((x = Td[PA[*b]]) == v);) { }
    if(((a = b) < last) && (x < v)) {
      for(; (++b < last) && ((x = Td[PA[*b]]) <= v);) {
        if(x == v) { SWAP(*b, *a); ++a; }
      }
    }
    for(c = last; (b < --c) && ((x = Td[PA[*c]]) == v);) { }
    if((b < (d = c)) && (x > v)) {
      for(; (b < --c) && ((x = Td[PA[*c]]) >= v);) {
        if(x == v) { SWAP(*c, *d); --d; }
      }
    }
    for(; b < c;) {
      SWAP(*b, *c);
      for(; (++b < c) && ((x = Td[PA[*b]]) <= v);) {
        if(x == v) { SWAP(*b, *a); ++a; }
      }
      for(; (b < --c) && ((x = Td[PA[*c]]) >= v);) {
        if(x == v) { SWAP(*c, *d); --d; }
      }
    }

    if(a <= d) {
      c = b - 1;

      if((s = a - first) > (t = b - a)) { s = t; }
      for(e = first, f = b - s; 0 < s; --s, ++e, ++f) { SWAP(*e, *f); }
      if((s = d - c) > (t = last - d - 1)) { s = t; }
      for(e = b, f = last - s; 0 < s; --s, ++e, ++f) { SWAP(*e, *f); }

      a = first + (b - a), c = last - (d - c);
      b = (v <= Td[PA[*a] - 1]) ? a : ss_partition(PA, a, c, depth);

      if((a - first) <= (last - c)) {
        if((last - c) <= (c - b)) {
          STACK_PUSH(b, c, depth + 1, ss_ilg(c - b));
          STACK_PUSH(c, last, depth, limit);
          last = a;
        } else if((a - first) <= (c - b)) {
          STACK_PUSH(c, last, depth, limit);
          STACK_PUSH(b, c, depth + 1, ss_ilg(c - b));
          last = a;
        } else {
          STACK_PUSH(c, last, depth, limit);
          STACK_PUSH(first, a, depth, limit);
          first = b, last = c, depth += 1, limit = ss_ilg(c - b);
        }
      } else {
        if((a - first) <= (c - b)) {
          STACK_PUSH(b, c, depth + 1, ss_ilg(c - b));
          STACK_PUSH(first, a, depth, limit);
          first = c;
        } else if((last - c) <= (c - b)) {
          STACK_PUSH(first, a, depth, limit);
          STACK_PUSH(b, c, depth + 1, ss_ilg(c - b));
          first = c;
        } else {
          STACK_PUSH(first, a, depth, limit);
          STACK_PUSH(c, last, depth, limit);
          first = b, last = c, depth += 1, limit = ss_ilg(c - b);
        }
      }
    } else {
      limit += 1;
      if(Td[PA[*first] - 1] < v) {
        first = ss_partition(PA, first, last, depth);
        limit = ss_ilg(last - first);
      }
      depth += 1;
    }
  }
#undef STACK_SIZE
}