#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_5__ {scalar_t__ wProcessorArchitecture; } ;
struct TYPE_6__ {TYPE_1__ s; } ;
struct TYPE_7__ {TYPE_2__ u; } ;
typedef  TYPE_3__ SYSTEM_INFO ;

/* Variables and functions */
 int /*<<< orphan*/  GetNativeSystemInfo (TYPE_3__*) ; 
 scalar_t__ PROCESSOR_ARCHITECTURE_AMD64 ; 
 int /*<<< orphan*/  const* os_32bitW ; 
 int /*<<< orphan*/  const* os_64bitW ; 

__attribute__((used)) static const WCHAR *get_osarchitecture(void)
{
    SYSTEM_INFO info;
    GetNativeSystemInfo( &info );
    if (info.u.s.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_AMD64) return os_64bitW;
    return os_32bitW;
}