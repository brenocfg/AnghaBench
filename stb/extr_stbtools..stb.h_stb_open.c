#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  various; int /*<<< orphan*/  close; } ;
typedef  TYPE_1__ stbfile ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  stb__fclose2 ; 
 int /*<<< orphan*/ * stb_fopen (char*,char*) ; 
 int /*<<< orphan*/  stb_keep_if_different ; 
 int /*<<< orphan*/  stb_keep_yes ; 
 TYPE_1__* stb_openf (int /*<<< orphan*/ *) ; 

stbfile *stb_open(char *filename, char *mode)
{
   FILE *f = stb_fopen(filename, mode[0] == 'k' ? mode+1 : mode);
   stbfile *s;
   if (f == NULL) return NULL;
   s = stb_openf(f);
   if (s) {
      s->close = stb__fclose2;
      s->various = mode[0] == 'k' ? stb_keep_if_different : stb_keep_yes;
   }
   return s;
}