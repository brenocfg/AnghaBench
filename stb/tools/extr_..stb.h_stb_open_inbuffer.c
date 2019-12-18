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
struct TYPE_3__ {unsigned char* buffer; unsigned char* indata; unsigned char* inend; int /*<<< orphan*/  member_7; int /*<<< orphan*/  member_6; int /*<<< orphan*/  member_5; int /*<<< orphan*/  member_4; int /*<<< orphan*/  member_3; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ stbfile ;

/* Variables and functions */
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  stb__bclose ; 
 int /*<<< orphan*/  stb__bgetbyte ; 
 int /*<<< orphan*/  stb__bgetdata ; 
 int /*<<< orphan*/  stb__bsize ; 
 int /*<<< orphan*/  stb__btell ; 
 int /*<<< orphan*/  stb__nobackpatch ; 
 int /*<<< orphan*/  stb__noputbyte ; 
 int /*<<< orphan*/  stb__noputdata ; 

stbfile *stb_open_inbuffer(void *buffer, unsigned int len)
{
   stbfile m = { stb__bgetbyte, stb__bgetdata,
                 stb__noputbyte, stb__noputdata,
                 stb__bsize, stb__btell, stb__nobackpatch, stb__bclose };
   stbfile *z = (stbfile *) malloc(sizeof(*z));
   if (z) {
      *z = m;
      z->buffer = (unsigned char *) buffer;
      z->indata = z->buffer;
      z->inend = z->indata + len;
   }
   return z;
}