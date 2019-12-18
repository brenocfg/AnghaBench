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
typedef  size_t stb_uint ;
typedef  int /*<<< orphan*/  stb_uchar ;

/* Variables and functions */
 size_t STB__SCRAMBLE (size_t) ; 
 int /*<<< orphan*/  STB__TRY (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  outliterals (int /*<<< orphan*/ *,int) ; 
 size_t stb__hc2 (int /*<<< orphan*/ *,size_t,int,int) ; 
 size_t stb__hc3 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  stb__running_adler ; 
 int stb__window ; 
 int /*<<< orphan*/  stb_adler32 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stb_out (int) ; 
 int /*<<< orphan*/  stb_out2 (int) ; 
 int /*<<< orphan*/  stb_out3 (int) ; 

__attribute__((used)) static int stb_compress_chunk(stb_uchar *history,
                              stb_uchar *start,
                              stb_uchar *end,
                              int length,
                              int *pending_literals,
                              stb_uchar **chash,
                              stb_uint mask)
{
   int window = stb__window;
   stb_uint match_max;
   stb_uchar *lit_start = start - *pending_literals;
   stb_uchar *q = start;

   #define STB__SCRAMBLE(h)   (((h) + ((h) >> 16)) & mask)

   // stop short of the end so we don't scan off the end doing
   // the hashing; this means we won't compress the last few bytes
   // unless they were part of something longer
   while (q < start+length && q+12 < end) {
      int m;
      stb_uint h1,h2,h3,h4, h;
      stb_uchar *t;
      int best = 2, dist=0;

      if (q+65536 > end)
         match_max = (stb_uint) (end-q);
      else
         match_max = 65536u;

      #define stb__nc(b,d)  ((d) <= window && ((b) > 9 || stb_not_crap(b,d)))

      #define STB__TRY(t,p)  /* avoid retrying a match we already tried */ \
                      if (p ? dist != (int) (q-t) : 1)                     \
                      if ((m = (int) stb_matchlen(t, q, match_max)) > best)\
                      if (stb__nc(m,(int) (q-(t))))                        \
                          best = m, dist = (int) (q - (t))

      // rather than search for all matches, only try 4 candidate locations,
      // chosen based on 4 different hash functions of different lengths.
      // this strategy is inspired by LZO; hashing is unrolled here using the
      // 'hc' macro
      h = stb__hc3(q,0, 1, 2); h1 = STB__SCRAMBLE(h);
                                      t = chash[h1]; if (t) STB__TRY(t,0);
      h = stb__hc2(q,h, 3, 4); h2 = STB__SCRAMBLE(h);
      h = stb__hc2(q,h, 5, 6);        t = chash[h2]; if (t) STB__TRY(t,1);
      h = stb__hc2(q,h, 7, 8); h3 = STB__SCRAMBLE(h);
      h = stb__hc2(q,h, 9,10);        t = chash[h3]; if (t) STB__TRY(t,1);
      h = stb__hc2(q,h,11,12); h4 = STB__SCRAMBLE(h);
                                      t = chash[h4]; if (t) STB__TRY(t,1);

      // because we use a shared hash table, can only update it
      // _after_ we've probed all of them
      chash[h1] = chash[h2] = chash[h3] = chash[h4] = q;

      if (best > 2)
         assert(dist > 0);

      // see if our best match qualifies
      if (best < 3) { // fast path literals
         ++q;
      } else if (best > 2  &&  best <= 0x80    &&  dist <= 0x100) {
         outliterals(lit_start, q-lit_start); lit_start = (q += best);
         stb_out(0x80 + best-1);
         stb_out(dist-1);
      } else if (best > 5  &&  best <= 0x100   &&  dist <= 0x4000) {
         outliterals(lit_start, q-lit_start); lit_start = (q += best);
         stb_out2(0x4000 + dist-1);       
         stb_out(best-1);
      } else if (best > 7  &&  best <= 0x100   &&  dist <= 0x80000) {
         outliterals(lit_start, q-lit_start); lit_start = (q += best);
         stb_out3(0x180000 + dist-1);     
         stb_out(best-1);
      } else if (best > 8  &&  best <= 0x10000 &&  dist <= 0x80000) {
         outliterals(lit_start, q-lit_start); lit_start = (q += best);
         stb_out3(0x100000 + dist-1);     
         stb_out2(best-1);
      } else if (best > 9                      &&  dist <= 0x1000000) {
         if (best > 65536) best = 65536;
         outliterals(lit_start, q-lit_start); lit_start = (q += best);
         if (best <= 0x100) {
            stb_out(0x06);
            stb_out3(dist-1);
            stb_out(best-1);
         } else {
            stb_out(0x04);
            stb_out3(dist-1);
            stb_out2(best-1);
         }
      } else {  // fallback literals if no match was a balanced tradeoff
         ++q;
      }
   }

   // if we didn't get all the way, add the rest to literals
   if (q-start < length)
      q = start+length;

   // the literals are everything from lit_start to q
   *pending_literals = (int) (q - lit_start);

   stb__running_adler = stb_adler32(stb__running_adler, start, (int) (q - start));
   return (int) (q - start);
}