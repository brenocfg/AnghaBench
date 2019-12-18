#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32 ;
struct TYPE_4__ {unsigned char* in; } ;
struct TYPE_5__ {int* bits; TYPE_1__ u; int /*<<< orphan*/  buf; } ;
typedef  TYPE_2__ MD5Context ;

/* Variables and functions */
 int /*<<< orphan*/  MD5Transform (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  byteReverse (unsigned char*,int) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char const*,unsigned int) ; 

__attribute__((used)) static 
void MD5Update(MD5Context *ctx, const unsigned char *buf, unsigned int len){
  uint32 t;

  /* Update bitcount */

  t = ctx->bits[0];
  if ((ctx->bits[0] = t + ((uint32)len << 3)) < t)
    ctx->bits[1]++; /* Carry from low to high */
  ctx->bits[1] += len >> 29;

  t = (t >> 3) & 0x3f;    /* Bytes already in shsInfo->data */

  /* Handle any leading odd-sized chunks */

  if ( t ) {
    unsigned char *p = (unsigned char *)ctx->u.in + t;

    t = 64-t;
    if (len < t) {
      memcpy(p, buf, len);
      return;
    }
    memcpy(p, buf, t);
    byteReverse(ctx->u.in, 16);
    MD5Transform(ctx->buf, (uint32 *)ctx->u.in);
    buf += t;
    len -= t;
  }

  /* Process data in 64-byte chunks */

  while (len >= 64) {
    memcpy(ctx->u.in, buf, 64);
    byteReverse(ctx->u.in, 16);
    MD5Transform(ctx->buf, (uint32 *)ctx->u.in);
    buf += 64;
    len -= 64;
  }

  /* Handle any remaining bytes of data. */

  memcpy(ctx->u.in, buf, len);
}