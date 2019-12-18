#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/ * cmsHANDLE ;
typedef  int /*<<< orphan*/  cmsContext ;
struct TYPE_2__ {int* buf; scalar_t__* bits; } ;
typedef  TYPE_1__ _cmsMD5 ;

/* Variables and functions */
 scalar_t__ _cmsMallocZero (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static
cmsHANDLE  MD5alloc(cmsContext ContextID)
{
    _cmsMD5* ctx = (_cmsMD5*) _cmsMallocZero(ContextID, sizeof(_cmsMD5));
    if (ctx == NULL) return NULL;

    ctx->buf[0] = 0x67452301;
    ctx->buf[1] = 0xefcdab89;
    ctx->buf[2] = 0x98badcfe;
    ctx->buf[3] = 0x10325476;

    ctx->bits[0] = 0;
    ctx->bits[1] = 0;

    return (cmsHANDLE) ctx;
}