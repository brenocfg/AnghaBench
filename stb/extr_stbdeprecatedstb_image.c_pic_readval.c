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
typedef  int /*<<< orphan*/  stbi_uc ;
typedef  int /*<<< orphan*/  stbi ;

/* Variables and functions */
 scalar_t__ at_eof (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * epuc (char*,char*) ; 
 int /*<<< orphan*/  get8u (int /*<<< orphan*/ *) ; 

__attribute__((used)) static stbi_uc *pic_readval(stbi *s, int channel, stbi_uc *dest)
{
   int mask=0x80, i;

   for (i=0; i<4; ++i, mask>>=1) {
      if (channel & mask) {
         if (at_eof(s)) return epuc("bad file","PIC file too short");
         dest[i]=get8u(s);
      }
   }

   return dest;
}