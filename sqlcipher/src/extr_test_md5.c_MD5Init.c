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
struct TYPE_3__ {int isInit; int* buf; scalar_t__* bits; } ;
typedef  TYPE_1__ MD5Context ;

/* Variables and functions */

__attribute__((used)) static void MD5Init(MD5Context *ctx){
        ctx->isInit = 1;
        ctx->buf[0] = 0x67452301;
        ctx->buf[1] = 0xefcdab89;
        ctx->buf[2] = 0x98badcfe;
        ctx->buf[3] = 0x10325476;
        ctx->bits[0] = 0;
        ctx->bits[1] = 0;
}