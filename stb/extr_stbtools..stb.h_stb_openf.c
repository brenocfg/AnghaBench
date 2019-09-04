#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * f; int /*<<< orphan*/  member_10; int /*<<< orphan*/  member_9; int /*<<< orphan*/  member_8; int /*<<< orphan*/  member_7; int /*<<< orphan*/  member_6; int /*<<< orphan*/  member_5; int /*<<< orphan*/  member_4; int /*<<< orphan*/  member_3; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ stbfile ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  stb__fbackpatch ; 
 int /*<<< orphan*/  stb__fclose ; 
 int /*<<< orphan*/  stb__fgetbyte ; 
 int /*<<< orphan*/  stb__fgetdata ; 
 int /*<<< orphan*/  stb__fputbyte ; 
 int /*<<< orphan*/  stb__fputdata ; 
 int /*<<< orphan*/  stb__fsize ; 
 int /*<<< orphan*/  stb__ftell ; 

stbfile *stb_openf(FILE *f)
{
   stbfile m = { stb__fgetbyte, stb__fgetdata,
                 stb__fputbyte, stb__fputdata,
                 stb__fsize, stb__ftell, stb__fbackpatch, stb__fclose,
                 0,0,0, };
   stbfile *z = (stbfile *) malloc(sizeof(*z));
   if (z) {
      *z = m;
      z->f = f;
   }
   return z;
}