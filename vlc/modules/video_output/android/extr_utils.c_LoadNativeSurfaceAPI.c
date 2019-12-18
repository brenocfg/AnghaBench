#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * setBuffersGeometry; int /*<<< orphan*/  unlockAndPost; int /*<<< orphan*/  winLock; } ;
struct TYPE_5__ {TYPE_1__ anw_api; int /*<<< orphan*/  pf_winRelease; int /*<<< orphan*/  pf_winFromSurface; } ;
typedef  TYPE_2__ AWindowHandler ;

/* Variables and functions */
 int /*<<< orphan*/  NativeSurface_fromSurface ; 
 int /*<<< orphan*/  NativeSurface_lock ; 
 int /*<<< orphan*/  NativeSurface_release ; 
 int /*<<< orphan*/  NativeSurface_unlockAndPost ; 

__attribute__((used)) static void
LoadNativeSurfaceAPI(AWindowHandler *p_awh)
{
    p_awh->pf_winFromSurface = NativeSurface_fromSurface;
    p_awh->pf_winRelease = NativeSurface_release;
    p_awh->anw_api.winLock = NativeSurface_lock;
    p_awh->anw_api.unlockAndPost = NativeSurface_unlockAndPost;
    p_awh->anw_api.setBuffersGeometry = NULL;
}