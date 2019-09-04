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
typedef  int /*<<< orphan*/  trbudget_t ;

/* Variables and functions */
 int /*<<< orphan*/  STACK_POP5 (int const*,int*,int*,int,int) ; 
 int /*<<< orphan*/  STACK_PUSH5 (int const*,int*,int*,int,int) ; 
 int /*<<< orphan*/  SWAP (int,int) ; 
 int TR_INSERTIONSORT_THRESHOLD ; 
 int TR_STACKSIZE ; 
 int /*<<< orphan*/  tr_copy (int*,int*,int*,int*,int*,int*,int) ; 
 int /*<<< orphan*/  tr_heapsort (int const*,int*,int) ; 
 int tr_ilg (int) ; 
 int /*<<< orphan*/  tr_insertionsort (int const*,int*,int*) ; 
 int /*<<< orphan*/  tr_partialcopy (int*,int*,int*,int*,int*,int*,int) ; 
 int /*<<< orphan*/  tr_partition (int const*,int*,int*,int*,int**,int**,int) ; 
 int* tr_pivot (int const*,int*,int*) ; 
 scalar_t__ trbudget_check (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static
void
tr_introsort(int *ISA, const int *ISAd,
             int *SA, int *first, int *last,
             trbudget_t *budget) {
#define STACK_SIZE TR_STACKSIZE
  struct { const int *a; int *b, *c; int d, e; }stack[STACK_SIZE];
  int *a, *b, *c;
  int t;
  int v, x = 0;
  int incr = ISAd - ISA;
  int limit, next;
  int ssize, trlink = -1;

  for(ssize = 0, limit = tr_ilg(last - first);;) {

    if(limit < 0) {
      if(limit == -1) {
        /* tandem repeat partition */
        tr_partition(ISAd - incr, first, first, last, &a, &b, last - SA - 1);

        /* update ranks */
        if(a < last) {
          for(c = first, v = a - SA - 1; c < a; ++c) { ISA[*c] = v; }
        }
        if(b < last) {
          for(c = a, v = b - SA - 1; c < b; ++c) { ISA[*c] = v; }
        }

        /* push */
        if(1 < (b - a)) {
          STACK_PUSH5(NULL, a, b, 0, 0);
          STACK_PUSH5(ISAd - incr, first, last, -2, trlink);
          trlink = ssize - 2;
        }
        if((a - first) <= (last - b)) {
          if(1 < (a - first)) {
            STACK_PUSH5(ISAd, b, last, tr_ilg(last - b), trlink);
            last = a, limit = tr_ilg(a - first);
          } else if(1 < (last - b)) {
            first = b, limit = tr_ilg(last - b);
          } else {
            STACK_POP5(ISAd, first, last, limit, trlink);
          }
        } else {
          if(1 < (last - b)) {
            STACK_PUSH5(ISAd, first, a, tr_ilg(a - first), trlink);
            first = b, limit = tr_ilg(last - b);
          } else if(1 < (a - first)) {
            last = a, limit = tr_ilg(a - first);
          } else {
            STACK_POP5(ISAd, first, last, limit, trlink);
          }
        }
      } else if(limit == -2) {
        /* tandem repeat copy */
        a = stack[--ssize].b, b = stack[ssize].c;
        if(stack[ssize].d == 0) {
          tr_copy(ISA, SA, first, a, b, last, ISAd - ISA);
        } else {
          if(0 <= trlink) { stack[trlink].d = -1; }
          tr_partialcopy(ISA, SA, first, a, b, last, ISAd - ISA);
        }
        STACK_POP5(ISAd, first, last, limit, trlink);
      } else {
        /* sorted partition */
        if(0 <= *first) {
          a = first;
          do { ISA[*a] = a - SA; } while((++a < last) && (0 <= *a));
          first = a;
        }
        if(first < last) {
          a = first; do { *a = ~*a; } while(*++a < 0);
          next = (ISA[*a] != ISAd[*a]) ? tr_ilg(a - first + 1) : -1;
          if(++a < last) { for(b = first, v = a - SA - 1; b < a; ++b) { ISA[*b] = v; } }

          /* push */
          if(trbudget_check(budget, a - first)) {
            if((a - first) <= (last - a)) {
              STACK_PUSH5(ISAd, a, last, -3, trlink);
              ISAd += incr, last = a, limit = next;
            } else {
              if(1 < (last - a)) {
                STACK_PUSH5(ISAd + incr, first, a, next, trlink);
                first = a, limit = -3;
              } else {
                ISAd += incr, last = a, limit = next;
              }
            }
          } else {
            if(0 <= trlink) { stack[trlink].d = -1; }
            if(1 < (last - a)) {
              first = a, limit = -3;
            } else {
              STACK_POP5(ISAd, first, last, limit, trlink);
            }
          }
        } else {
          STACK_POP5(ISAd, first, last, limit, trlink);
        }
      }
      continue;
    }

    if((last - first) <= TR_INSERTIONSORT_THRESHOLD) {
      tr_insertionsort(ISAd, first, last);
      limit = -3;
      continue;
    }

    if(limit-- == 0) {
      tr_heapsort(ISAd, first, last - first);
      for(a = last - 1; first < a; a = b) {
        for(x = ISAd[*a], b = a - 1; (first <= b) && (ISAd[*b] == x); --b) { *b = ~*b; }
      }
      limit = -3;
      continue;
    }

    /* choose pivot */
    a = tr_pivot(ISAd, first, last);
    SWAP(*first, *a);
    v = ISAd[*first];

    /* partition */
    tr_partition(ISAd, first, first + 1, last, &a, &b, v);
    if((last - first) != (b - a)) {
      next = (ISA[*a] != v) ? tr_ilg(b - a) : -1;

      /* update ranks */
      for(c = first, v = a - SA - 1; c < a; ++c) { ISA[*c] = v; }
      if(b < last) { for(c = a, v = b - SA - 1; c < b; ++c) { ISA[*c] = v; } }

      /* push */
      if((1 < (b - a)) && (trbudget_check(budget, b - a))) {
        if((a - first) <= (last - b)) {
          if((last - b) <= (b - a)) {
            if(1 < (a - first)) {
              STACK_PUSH5(ISAd + incr, a, b, next, trlink);
              STACK_PUSH5(ISAd, b, last, limit, trlink);
              last = a;
            } else if(1 < (last - b)) {
              STACK_PUSH5(ISAd + incr, a, b, next, trlink);
              first = b;
            } else {
              ISAd += incr, first = a, last = b, limit = next;
            }
          } else if((a - first) <= (b - a)) {
            if(1 < (a - first)) {
              STACK_PUSH5(ISAd, b, last, limit, trlink);
              STACK_PUSH5(ISAd + incr, a, b, next, trlink);
              last = a;
            } else {
              STACK_PUSH5(ISAd, b, last, limit, trlink);
              ISAd += incr, first = a, last = b, limit = next;
            }
          } else {
            STACK_PUSH5(ISAd, b, last, limit, trlink);
            STACK_PUSH5(ISAd, first, a, limit, trlink);
            ISAd += incr, first = a, last = b, limit = next;
          }
        } else {
          if((a - first) <= (b - a)) {
            if(1 < (last - b)) {
              STACK_PUSH5(ISAd + incr, a, b, next, trlink);
              STACK_PUSH5(ISAd, first, a, limit, trlink);
              first = b;
            } else if(1 < (a - first)) {
              STACK_PUSH5(ISAd + incr, a, b, next, trlink);
              last = a;
            } else {
              ISAd += incr, first = a, last = b, limit = next;
            }
          } else if((last - b) <= (b - a)) {
            if(1 < (last - b)) {
              STACK_PUSH5(ISAd, first, a, limit, trlink);
              STACK_PUSH5(ISAd + incr, a, b, next, trlink);
              first = b;
            } else {
              STACK_PUSH5(ISAd, first, a, limit, trlink);
              ISAd += incr, first = a, last = b, limit = next;
            }
          } else {
            STACK_PUSH5(ISAd, first, a, limit, trlink);
            STACK_PUSH5(ISAd, b, last, limit, trlink);
            ISAd += incr, first = a, last = b, limit = next;
          }
        }
      } else {
        if((1 < (b - a)) && (0 <= trlink)) { stack[trlink].d = -1; }
        if((a - first) <= (last - b)) {
          if(1 < (a - first)) {
            STACK_PUSH5(ISAd, b, last, limit, trlink);
            last = a;
          } else if(1 < (last - b)) {
            first = b;
          } else {
            STACK_POP5(ISAd, first, last, limit, trlink);
          }
        } else {
          if(1 < (last - b)) {
            STACK_PUSH5(ISAd, first, a, limit, trlink);
            first = b;
          } else if(1 < (a - first)) {
            last = a;
          } else {
            STACK_POP5(ISAd, first, last, limit, trlink);
          }
        }
      }
    } else {
      if(trbudget_check(budget, last - first)) {
        limit = tr_ilg(last - first), ISAd += incr;
      } else {
        if(0 <= trlink) { stack[trlink].d = -1; }
        STACK_POP5(ISAd, first, last, limit, trlink);
      }
    }
  }
#undef STACK_SIZE
}