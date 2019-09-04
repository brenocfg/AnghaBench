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
struct TYPE_3__ {int /*<<< orphan*/  sha512; int /*<<< orphan*/  sha384; int /*<<< orphan*/  sha256; int /*<<< orphan*/  sha; int /*<<< orphan*/  md5; int /*<<< orphan*/  md4; int /*<<< orphan*/  md2; } ;
typedef  TYPE_1__ HASH_CONTEXT ;
typedef  int /*<<< orphan*/  BOOL ;
typedef  int ALG_ID ;

/* Variables and functions */
 int /*<<< orphan*/  A_SHAInit (int /*<<< orphan*/ *) ; 
#define  CALG_MD2 134 
#define  CALG_MD4 133 
#define  CALG_MD5 132 
#define  CALG_SHA 131 
#define  CALG_SHA_256 130 
#define  CALG_SHA_384 129 
#define  CALG_SHA_512 128 
 int /*<<< orphan*/  MD4Init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MD5Init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SHA256_Init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SHA384_Init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SHA512_Init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  md2_init (int /*<<< orphan*/ *) ; 

BOOL init_hash_impl(ALG_ID aiAlgid, HASH_CONTEXT *pHashContext) 
{
    switch (aiAlgid) 
    {
        case CALG_MD2:
            md2_init(&pHashContext->md2);
            break;
        
        case CALG_MD4:
            MD4Init(&pHashContext->md4);
            break;
        
        case CALG_MD5:
            MD5Init(&pHashContext->md5);
            break;
        
        case CALG_SHA:
            A_SHAInit(&pHashContext->sha);
            break;

        case CALG_SHA_256:
            SHA256_Init(&pHashContext->sha256);
            break;

        case CALG_SHA_384:
            SHA384_Init(&pHashContext->sha384);
            break;

        case CALG_SHA_512:
            SHA512_Init(&pHashContext->sha512);
            break;
    }

    return TRUE;
}