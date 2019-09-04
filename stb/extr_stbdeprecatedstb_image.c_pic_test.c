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
 int /*<<< orphan*/  get8 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pic_is4 (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int pic_test(stbi *s)
{
   int i;

   if (!pic_is4(s,"\x53\x80\xF6\x34"))
      return 0;

   for(i=0;i<84;++i)
      get8(s);

   if (!pic_is4(s,"PICT"))
      return 0;

   return 1;
}