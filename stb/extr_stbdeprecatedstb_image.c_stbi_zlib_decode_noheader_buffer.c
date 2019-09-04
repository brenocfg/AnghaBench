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
struct TYPE_3__ {scalar_t__ zout_start; scalar_t__ zout; int /*<<< orphan*/ * zbuffer_end; int /*<<< orphan*/ * zbuffer; } ;
typedef  TYPE_1__ zbuf ;
typedef  int /*<<< orphan*/  stbi__uint8 ;

/* Variables and functions */
 scalar_t__ do_zlib (TYPE_1__*,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int stbi_zlib_decode_noheader_buffer(char *obuffer, int olen, const char *ibuffer, int ilen)
{
   zbuf a;
   a.zbuffer = (stbi__uint8 *) ibuffer;
   a.zbuffer_end = (stbi__uint8 *) ibuffer + ilen;
   if (do_zlib(&a, obuffer, olen, 0, 0))
      return (int) (a.zout - a.zout_start);
   else
      return -1;
}