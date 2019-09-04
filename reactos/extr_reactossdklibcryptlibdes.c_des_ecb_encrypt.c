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
typedef  int /*<<< orphan*/  ulong32 ;
struct TYPE_3__ {int /*<<< orphan*/  ek; } ;
typedef  TYPE_1__ des_key ;

/* Variables and functions */
 int /*<<< orphan*/  LOAD32H (int /*<<< orphan*/ ,unsigned char const*) ; 
 int /*<<< orphan*/  STORE32H (int /*<<< orphan*/ ,unsigned char*) ; 
 int /*<<< orphan*/  desfunc (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void des_ecb_encrypt(const unsigned char *pt, unsigned char *ct, const des_key *des)
{
    ulong32 work[2];
    LOAD32H(work[0], pt+0);
    LOAD32H(work[1], pt+4);
    desfunc(work, des->ek);
    STORE32H(work[0],ct+0);
    STORE32H(work[1],ct+4);
}