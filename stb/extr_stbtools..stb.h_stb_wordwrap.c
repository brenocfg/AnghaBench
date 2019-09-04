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
 scalar_t__ isspace (char) ; 

int stb_wordwrap(int *pairs, int pair_max, int count, char *str)
{
   int n=0,i=0, start=0,nonwhite=0;
   if (pairs == NULL) pair_max = 0x7ffffff0;
   else pair_max *= 2;
   // parse 
   for(;;) {
      int s=i; // first whitespace char; last nonwhite+1
      int w;   // word start
      // accept whitespace
      while (isspace(str[i])) {
         if (str[i] == '\n' || str[i] == '\r') {
            if (str[i] + str[i+1] == '\n' + '\r') ++i;
            if (n >= pair_max) return -1;
            if (pairs) pairs[n] = start, pairs[n+1] = s-start;
            n += 2;
            nonwhite=0;
            start = i+1;
            s = start;
         }
         ++i;
      }
      if (i >= start+count) {
         // we've gone off the end using whitespace
         if (nonwhite) {
            if (n >= pair_max) return -1;
            if (pairs) pairs[n] = start, pairs[n+1] = s-start;
            n += 2;
            start = s = i;
            nonwhite=0;
         } else {
            // output all the whitespace
            while (i >= start+count) {
               if (n >= pair_max) return -1;
               if (pairs) pairs[n] = start, pairs[n+1] = count;
               n += 2;
               start += count;
            }
            s = start;
         }
      }

      if (str[i] == 0) break;
      // now scan out a word and see if it fits
      w = i;
      while (str[i] && !isspace(str[i])) {
         ++i;
      }
      // wrapped?
      if (i > start + count) {
         // huge?
         if (i-s <= count) {
            if (n >= pair_max) return -1;
            if (pairs) pairs[n] = start, pairs[n+1] = s-start;
            n += 2;
            start = w;
         } else {
            // This word is longer than one line. If we wrap it onto N lines
            // there are leftover chars. do those chars fit on the cur line?
            // But if we have leading whitespace, we force it to start here.
            if ((w-start) + ((i-w) % count) <= count || !nonwhite) {
               // output a full line
               if (n >= pair_max) return -1;
               if (pairs) pairs[n] = start, pairs[n+1] = count;
               n += 2;
               start += count;
               w = start;
            } else {
               // output a partial line, trimming trailing whitespace
               if (s != start) {
                  if (n >= pair_max) return -1;
                  if (pairs) pairs[n] = start, pairs[n+1] = s-start;
                  n += 2;
                  start = w;
               }
            }
            // now output full lines as needed
            while (start + count <= i) {
               if (n >= pair_max) return -1;
               if (pairs) pairs[n] = start, pairs[n+1] = count;
               n += 2;
               start += count;
            }
         }
      }
      nonwhite=1;
   }
   if (start < i) {
      if (n >= pair_max) return -1;
      if (pairs) pairs[n] = start, pairs[n+1] = i-start;
      n += 2;
   }
   return n>>1;
}