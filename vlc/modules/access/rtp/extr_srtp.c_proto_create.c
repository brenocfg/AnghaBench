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
struct TYPE_3__ {int /*<<< orphan*/  cipher; int /*<<< orphan*/  mac; } ;
typedef  TYPE_1__ srtp_proto_t ;

/* Variables and functions */
 int /*<<< orphan*/  GCRY_CIPHER_MODE_CTR ; 
 int /*<<< orphan*/  GCRY_MD_FLAG_HMAC ; 
 int /*<<< orphan*/  gcry_cipher_close (int /*<<< orphan*/ ) ; 
 scalar_t__ gcry_cipher_open (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ gcry_md_open (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int proto_create (srtp_proto_t *p, int gcipher, int gmd)
{
    if (gcry_cipher_open (&p->cipher, gcipher, GCRY_CIPHER_MODE_CTR, 0) == 0)
    {
        if (gcry_md_open (&p->mac, gmd, GCRY_MD_FLAG_HMAC) == 0)
            return 0;
        gcry_cipher_close (p->cipher);
    }
    return -1;
}