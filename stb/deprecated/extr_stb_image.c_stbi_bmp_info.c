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
typedef  int /*<<< orphan*/  stbi ;

/* Variables and functions */
 int get16le (int /*<<< orphan*/ *) ; 
 int get32le (int /*<<< orphan*/ *) ; 
 char get8 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skip (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stbi_rewind (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int stbi_bmp_info(stbi *s, int *x, int *y, int *comp)
{
   int hsz;
   if (get8(s) != 'B' || get8(s) != 'M') {
       stbi_rewind( s );
       return 0;
   }
   skip(s,12);
   hsz = get32le(s);
   if (hsz != 12 && hsz != 40 && hsz != 56 && hsz != 108) {
       stbi_rewind( s );
       return 0;
   }
   if (hsz == 12) {
      *x = get16le(s);
      *y = get16le(s);
   } else {
      *x = get32le(s);
      *y = get32le(s);
   }
   if (get16le(s) != 1) {
       stbi_rewind( s );
       return 0;
   }
   *comp = get16le(s) / 8;
   return 1;
}