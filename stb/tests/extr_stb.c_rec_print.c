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
struct TYPE_4__ {char* relpath; float weight; struct TYPE_4__** files; struct TYPE_4__** subdirs; } ;
typedef  TYPE_1__ stb_dirtree2 ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,...) ; 
 int stb_arr_len (TYPE_1__**) ; 

void rec_print(stb_dirtree2 *d, int depth)
{
   int i;
   for (i=0; i < depth; ++i) printf("  ");
   printf("%s (%d)\n", d->relpath, stb_arr_len(d->files));
   for (i=0; i < stb_arr_len(d->subdirs); ++i)
      rec_print(d->subdirs[i], depth+1);
   d->weight = (float) stb_arr_len(d->files);
}