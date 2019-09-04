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
struct TYPE_3__ {scalar_t__ view; scalar_t__ browser_service; } ;
typedef  TYPE_1__ DocHost ;

/* Variables and functions */
 int /*<<< orphan*/  IOleDocumentView_Release (scalar_t__) ; 
 int /*<<< orphan*/  detach_browser_service (scalar_t__) ; 

void DocHost_ClientSite_Release(DocHost *This)
{
    if(This->browser_service)
        detach_browser_service(This->browser_service);
    if(This->view)
        IOleDocumentView_Release(This->view);
}