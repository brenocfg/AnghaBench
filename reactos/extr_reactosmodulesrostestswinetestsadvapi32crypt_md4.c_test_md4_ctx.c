#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  message ;
typedef  int /*<<< orphan*/  expect ;
typedef  int /*<<< orphan*/  ctx ;
struct TYPE_11__ {int member_0; int /*<<< orphan*/  member_1; } ;
struct TYPE_10__ {int member_0; int member_1; int member_2; int member_3; } ;
struct TYPE_12__ {int /*<<< orphan*/  digest; TYPE_2__ member_1; TYPE_1__ member_0; } ;
typedef  TYPE_3__ MD4_CTX ;

/* Variables and functions */
 int ctxcmp (TYPE_3__*,TYPE_3__*) ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ ,unsigned char*,int) ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ok (int,char*) ; 
 int /*<<< orphan*/  pMD4Final (TYPE_3__*) ; 
 int /*<<< orphan*/  pMD4Init (TYPE_3__*) ; 
 int /*<<< orphan*/  pMD4Update (TYPE_3__*,unsigned char*,int) ; 

__attribute__((used)) static void test_md4_ctx(void)
{
    static unsigned char message[] =
        "In our Life there's If"
        "In our beliefs there's Lie"
        "In our business there is Sin"
        "In our bodies, there is Die";

    int size = sizeof(message) - 1;

    MD4_CTX ctx;
    MD4_CTX ctx_initialized = 
    {
        { 0x67452301, 0xefcdab89, 0x98badcfe, 0x10325476 },
        { 0, 0 }
    };

    MD4_CTX ctx_update1 =
    {
        { 0x5e592ef7, 0xbdcb1567, 0x2b626d17, 0x7d1198bd },
        { 0x00000338, 0 }
    };

    MD4_CTX ctx_update2 =
    {
        { 0x05dcfd65, 0xb3711c0d, 0x9e3369c2, 0x903ead11 },
        { 0x00000670, 0 }
    };

    unsigned char expect[16] =
        { 0x5f, 0xd3, 0x9b, 0x29, 0x47, 0x53, 0x47, 0xaf,
          0xa5, 0xba, 0x0c, 0x05, 0xff, 0xc0, 0xc7, 0xda };


    memset( &ctx, 0, sizeof(ctx) );
    pMD4Init( &ctx );
    ok( !ctxcmp( &ctx, &ctx_initialized ), "invalid initialization\n" );

    pMD4Update( &ctx, message, size );
    ok( !ctxcmp( &ctx, &ctx_update1 ), "update doesn't work correctly\n" );

    pMD4Update( &ctx, message, size );
    ok( !ctxcmp( &ctx, &ctx_update2 ), "update doesn't work correctly\n" );

    pMD4Final( &ctx );
    ok( ctxcmp( &ctx, &ctx_initialized ), "context has changed\n" );
    ok( !memcmp( ctx.digest, expect, sizeof(expect) ), "incorrect result\n" );

}