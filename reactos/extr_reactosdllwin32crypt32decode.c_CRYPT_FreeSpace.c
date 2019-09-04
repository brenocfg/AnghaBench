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
struct TYPE_3__ {int /*<<< orphan*/  (* pfnFree ) (int /*<<< orphan*/ ) ;} ;
typedef  int /*<<< orphan*/  LPVOID ;
typedef  TYPE_1__ CRYPT_DECODE_PARA ;

/* Variables and functions */
 int /*<<< orphan*/  LocalFree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void CRYPT_FreeSpace(const CRYPT_DECODE_PARA *pDecodePara, LPVOID pv)
{
    if (pDecodePara && pDecodePara->pfnFree)
        pDecodePara->pfnFree(pv);
    else
        LocalFree(pv);
}