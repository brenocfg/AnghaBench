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
struct TYPE_2__ {int /*<<< orphan*/  storage; int /*<<< orphan*/ * property; } ;
typedef  TYPE_1__ MSISUMMARYINFO ;
typedef  int /*<<< orphan*/  MSIOBJECTHDR ;
typedef  size_t DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  IStorage_Release (int /*<<< orphan*/ ) ; 
 size_t MSI_MAX_PROPS ; 
 int /*<<< orphan*/  free_prop (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void MSI_CloseSummaryInfo( MSIOBJECTHDR *arg )
{
    MSISUMMARYINFO *si = (MSISUMMARYINFO *) arg;
    DWORD i;

    for( i = 0; i < MSI_MAX_PROPS; i++ )
        free_prop( &si->property[i] );
    IStorage_Release( si->storage );
}