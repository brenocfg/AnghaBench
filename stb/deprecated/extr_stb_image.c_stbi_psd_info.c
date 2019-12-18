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
 int get16 (int /*<<< orphan*/ *) ; 
 int get32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skip (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stbi_rewind (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int stbi_psd_info(stbi *s, int *x, int *y, int *comp)
{
   int channelCount;
   if (get32(s) != 0x38425053) {
       stbi_rewind( s );
       return 0;
   }
   if (get16(s) != 1) {
       stbi_rewind( s );
       return 0;
   }
   skip(s, 6);
   channelCount = get16(s);
   if (channelCount < 0 || channelCount > 16) {
       stbi_rewind( s );
       return 0;
   }
   *y = get32(s);
   *x = get32(s);
   if (get16(s) != 8) {
       stbi_rewind( s );
       return 0;
   }
   if (get16(s) != 3) {
       stbi_rewind( s );
       return 0;
   }
   *comp = 4;
   return 1;
}