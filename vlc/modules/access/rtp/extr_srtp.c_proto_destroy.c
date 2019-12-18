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
 int /*<<< orphan*/  gcry_cipher_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcry_md_close (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void proto_destroy (srtp_proto_t *p)
{
    gcry_md_close (p->mac);
    gcry_cipher_close (p->cipher);
}