#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  pbData; } ;
struct TYPE_12__ {int /*<<< orphan*/  pbData; } ;
struct TYPE_11__ {int /*<<< orphan*/  pbData; } ;
struct TYPE_10__ {int /*<<< orphan*/  pbData; } ;
struct TYPE_9__ {int /*<<< orphan*/  pbData; } ;
struct TYPE_8__ {int /*<<< orphan*/  pbData; } ;
struct protect_data_t {TYPE_1__ fingerprint; TYPE_6__ cipher; TYPE_5__ salt; TYPE_4__ data0; int /*<<< orphan*/  szDataDescr; TYPE_3__ info1; TYPE_2__ info0; } ;

/* Variables and functions */
 int /*<<< orphan*/  CryptMemFree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*) ; 

__attribute__((used)) static
void free_protect_data(struct protect_data_t * pInfo)
{
    TRACE("called\n");

    if (!pInfo) return;

    CryptMemFree(pInfo->info0.pbData);
    CryptMemFree(pInfo->info1.pbData);
    CryptMemFree(pInfo->szDataDescr);
    CryptMemFree(pInfo->data0.pbData);
    CryptMemFree(pInfo->salt.pbData);
    CryptMemFree(pInfo->cipher.pbData);
    CryptMemFree(pInfo->fingerprint.pbData);
}