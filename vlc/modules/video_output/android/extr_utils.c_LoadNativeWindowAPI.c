#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {void* setBuffersGeometry; void* unlockAndPost; void* winLock; } ;
struct TYPE_6__ {void* p_anw_dl; TYPE_1__ anw_api; void* pf_winRelease; void* pf_winFromSurface; } ;
typedef  TYPE_2__ AWindowHandler ;

/* Variables and functions */
 int /*<<< orphan*/  LoadNativeSurfaceAPI (TYPE_2__*) ; 
 int /*<<< orphan*/  RTLD_NOW ; 
 int /*<<< orphan*/  dlclose (void*) ; 
 void* dlopen (char*,int /*<<< orphan*/ ) ; 
 void* dlsym (void*,char*) ; 

__attribute__((used)) static void
LoadNativeWindowAPI(AWindowHandler *p_awh)
{
    void *p_library = dlopen("libandroid.so", RTLD_NOW);
    if (!p_library)
    {
        LoadNativeSurfaceAPI(p_awh);
        return;
    }

    p_awh->pf_winFromSurface = dlsym(p_library, "ANativeWindow_fromSurface");
    p_awh->pf_winRelease = dlsym(p_library, "ANativeWindow_release");
    p_awh->anw_api.winLock = dlsym(p_library, "ANativeWindow_lock");
    p_awh->anw_api.unlockAndPost = dlsym(p_library, "ANativeWindow_unlockAndPost");
    p_awh->anw_api.setBuffersGeometry = dlsym(p_library, "ANativeWindow_setBuffersGeometry");

    if (p_awh->pf_winFromSurface && p_awh->pf_winRelease
     && p_awh->anw_api.winLock && p_awh->anw_api.unlockAndPost
     && p_awh->anw_api.setBuffersGeometry)
    {
        p_awh->p_anw_dl = p_library;
    }
    else
    {
        dlclose(p_library);
        LoadNativeSurfaceAPI(p_awh);
    }
}