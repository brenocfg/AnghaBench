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
 int SS_BLOCKSIZE ; 
 scalar_t__ ss_compare (unsigned char const*,int*,int const*,int) ; 
 int /*<<< orphan*/  ss_inplacemerge (unsigned char const*,int const*,int*,int*,int*,int) ; 
 int /*<<< orphan*/  ss_insertionsort (unsigned char const*,int const*,int*,int*,int) ; 
 int ss_isqrt (int) ; 
 int /*<<< orphan*/  ss_mintrosort (unsigned char const*,int const*,int*,int*,int) ; 
 int /*<<< orphan*/  ss_swapmerge (unsigned char const*,int const*,int*,int*,int*,int*,int,int) ; 

__attribute__((used)) static
void
sssort(const unsigned char *T, const int *PA,
       int *first, int *last,
       int *buf, int bufsize,
       int depth, int n, int lastsuffix) {
  int *a;
#if SS_BLOCKSIZE != 0
  int *b, *middle, *curbuf;
  int j, k, curbufsize, limit;
#endif
  int i;

  if(lastsuffix != 0) { ++first; }

#if SS_BLOCKSIZE == 0
  ss_mintrosort(T, PA, first, last, depth);
#else
  if((bufsize < SS_BLOCKSIZE) &&
      (bufsize < (last - first)) &&
      (bufsize < (limit = ss_isqrt(last - first)))) {
    if(SS_BLOCKSIZE < limit) { limit = SS_BLOCKSIZE; }
    buf = middle = last - limit, bufsize = limit;
  } else {
    middle = last, limit = 0;
  }
  for(a = first, i = 0; SS_BLOCKSIZE < (middle - a); a += SS_BLOCKSIZE, ++i) {
#if SS_INSERTIONSORT_THRESHOLD < SS_BLOCKSIZE
    ss_mintrosort(T, PA, a, a + SS_BLOCKSIZE, depth);
#elif 1 < SS_BLOCKSIZE
    ss_insertionsort(T, PA, a, a + SS_BLOCKSIZE, depth);
#endif
    curbufsize = last - (a + SS_BLOCKSIZE);
    curbuf = a + SS_BLOCKSIZE;
    if(curbufsize <= bufsize) { curbufsize = bufsize, curbuf = buf; }
    for(b = a, k = SS_BLOCKSIZE, j = i; j & 1; b -= k, k <<= 1, j >>= 1) {
      ss_swapmerge(T, PA, b - k, b, b + k, curbuf, curbufsize, depth);
    }
  }
#if SS_INSERTIONSORT_THRESHOLD < SS_BLOCKSIZE
  ss_mintrosort(T, PA, a, middle, depth);
#elif 1 < SS_BLOCKSIZE
  ss_insertionsort(T, PA, a, middle, depth);
#endif
  for(k = SS_BLOCKSIZE; i != 0; k <<= 1, i >>= 1) {
    if(i & 1) {
      ss_swapmerge(T, PA, a - k, a, middle, buf, bufsize, depth);
      a -= k;
    }
  }
  if(limit != 0) {
#if SS_INSERTIONSORT_THRESHOLD < SS_BLOCKSIZE
    ss_mintrosort(T, PA, middle, last, depth);
#elif 1 < SS_BLOCKSIZE
    ss_insertionsort(T, PA, middle, last, depth);
#endif
    ss_inplacemerge(T, PA, first, middle, last, depth);
  }
#endif

  if(lastsuffix != 0) {
    /* Insert last type B* suffix. */
    int PAi[2]; PAi[0] = PA[*(first - 1)], PAi[1] = n - 2;
    for(a = first, i = *(first - 1);
        (a < last) && ((*a < 0) || (0 < ss_compare(T, &(PAi[0]), PA + *a, depth)));
        ++a) {
      *(a - 1) = *a;
    }
    *(a - 1) = i;
  }
}