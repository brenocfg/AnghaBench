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
struct TYPE_3__ {unsigned char** ptr; int /*<<< orphan*/  member_7; int /*<<< orphan*/  member_6; int /*<<< orphan*/  member_5; int /*<<< orphan*/  member_4; int /*<<< orphan*/  member_3; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ stbfile ;

/* Variables and functions */
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  stb__abackpatch ; 
 int /*<<< orphan*/  stb__aclose ; 
 int /*<<< orphan*/  stb__aputbyte ; 
 int /*<<< orphan*/  stb__aputdata ; 
 int /*<<< orphan*/  stb__asize ; 
 int /*<<< orphan*/  stb__nogetbyte ; 
 int /*<<< orphan*/  stb__nogetdata ; 

stbfile *stb_open_outbuffer(unsigned char **update_on_close)
{
   stbfile m = { stb__nogetbyte, stb__nogetdata,
                 stb__aputbyte, stb__aputdata,
                 stb__asize, stb__asize, stb__abackpatch, stb__aclose };
   stbfile *z = (stbfile *) malloc(sizeof(*z));
   if (z) {
      z->ptr = update_on_close;
      *z = m;
   }
   return z;
}