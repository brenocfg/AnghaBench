#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int num_bits; int code_buffer; scalar_t__ zbuffer; scalar_t__ zbuffer_end; scalar_t__ zout; scalar_t__ zout_end; } ;
typedef  TYPE_1__ zbuf ;
typedef  int stbi__uint8 ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int e (char*,char*) ; 
 int /*<<< orphan*/  expand (TYPE_1__*,int) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,scalar_t__,int) ; 
 scalar_t__ zget8 (TYPE_1__*) ; 
 int /*<<< orphan*/  zreceive (TYPE_1__*,int) ; 

__attribute__((used)) static int parse_uncompressed_block(zbuf *a)
{
   stbi__uint8 header[4];
   int len,nlen,k;
   if (a->num_bits & 7)
      zreceive(a, a->num_bits & 7); // discard
   // drain the bit-packed data into header
   k = 0;
   while (a->num_bits > 0) {
      header[k++] = (stbi__uint8) (a->code_buffer & 255); // wtf this warns?
      a->code_buffer >>= 8;
      a->num_bits -= 8;
   }
   assert(a->num_bits == 0);
   // now fill header the normal way
   while (k < 4)
      header[k++] = (stbi__uint8) zget8(a);
   len  = header[1] * 256 + header[0];
   nlen = header[3] * 256 + header[2];
   if (nlen != (len ^ 0xffff)) return e("zlib corrupt","Corrupt PNG");
   if (a->zbuffer + len > a->zbuffer_end) return e("read past buffer","Corrupt PNG");
   if (a->zout + len > a->zout_end)
      if (!expand(a, len)) return 0;
   memcpy(a->zout, a->zbuffer, len);
   a->zbuffer += len;
   a->zout += len;
   return 1;
}