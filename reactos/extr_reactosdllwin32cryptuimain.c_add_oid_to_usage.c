#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int cUsageIdentifier; int /*<<< orphan*/ * rgpszUsageIdentifier; } ;
typedef  int /*<<< orphan*/  LPSTR ;
typedef  TYPE_1__ CERT_ENHKEY_USAGE ;

/* Variables and functions */
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/ * HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/ * HeapReAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static CERT_ENHKEY_USAGE *add_oid_to_usage(CERT_ENHKEY_USAGE *usage, LPSTR oid)
{
    if (!usage->cUsageIdentifier)
        usage->rgpszUsageIdentifier = HeapAlloc(GetProcessHeap(), 0,
         sizeof(LPSTR));
    else
        usage->rgpszUsageIdentifier = HeapReAlloc(GetProcessHeap(), 0,
         usage->rgpszUsageIdentifier,
         (usage->cUsageIdentifier + 1) * sizeof(LPSTR));
    if (usage->rgpszUsageIdentifier)
        usage->rgpszUsageIdentifier[usage->cUsageIdentifier++] = oid;
    else
    {
        HeapFree(GetProcessHeap(), 0, usage);
        usage = NULL;
    }
    return usage;
}