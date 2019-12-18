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
typedef  int /*<<< orphan*/  zbuf ;

/* Variables and functions */
 int e (char*,char*) ; 
 int zget8 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int parse_zlib_header(zbuf *a)
{
   int cmf   = zget8(a);
   int cm    = cmf & 15;
   /* int cinfo = cmf >> 4; */
   int flg   = zget8(a);
   if ((cmf*256+flg) % 31 != 0) return e("bad zlib header","Corrupt PNG"); // zlib spec
   if (flg & 32) return e("no preset dict","Corrupt PNG"); // preset dictionary not allowed in png
   if (cm != 8) return e("bad compression","Corrupt PNG"); // DEFLATE required for png
   // window = 1 << (8 + cinfo)... but who cares, we fully buffer output
   return 1;
}