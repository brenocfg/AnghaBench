#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int /*<<< orphan*/  CoUninitialize () ; 
 int /*<<< orphan*/  ITfCategoryMgr_Release (scalar_t__) ; 
 int /*<<< orphan*/  ITfInputProcessorProfiles_Release (scalar_t__) ; 
 int /*<<< orphan*/  ITfThreadMgr_Release (scalar_t__) ; 
 scalar_t__ g_cm ; 
 scalar_t__ g_ipp ; 
 scalar_t__ g_tm ; 

__attribute__((used)) static void cleanup(void)
{
    if (g_ipp)
        ITfInputProcessorProfiles_Release(g_ipp);
    if (g_cm)
        ITfCategoryMgr_Release(g_cm);
    if (g_tm)
        ITfThreadMgr_Release(g_tm);
    CoUninitialize();
}