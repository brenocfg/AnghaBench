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
typedef  int cmsInt32Number ;
typedef  int /*<<< orphan*/  cmsContext ;

/* Variables and functions */
 int /*<<< orphan*/  DebugMemDontCheckThis (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DupContext (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PluginMemHandler () ; 
 int /*<<< orphan*/  cmsCreateContext (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cmsDeleteContext (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmsPlugin (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

cmsInt32Number CheckAllocContext(void)
{
     cmsContext c1, c2, c3, c4;

     c1 = cmsCreateContext(NULL, NULL);                 // This creates a context by using the normal malloc
     DebugMemDontCheckThis(c1);
     cmsDeleteContext(c1);

     c2 = cmsCreateContext(PluginMemHandler(), NULL);   // This creates a context by using the debug malloc
     DebugMemDontCheckThis(c2);
     cmsDeleteContext(c2);

     c1 = cmsCreateContext(NULL, NULL);
     DebugMemDontCheckThis(c1);

     c2 = cmsCreateContext(PluginMemHandler(), NULL);
     DebugMemDontCheckThis(c2);

     cmsPlugin(c1, PluginMemHandler()); // Now the context have custom allocators

     c3 = DupContext(c1, NULL);
     c4 = DupContext(c2, NULL);

     cmsDeleteContext(c1);  // Should be deleted by using nomal malloc
     cmsDeleteContext(c2);  // Should be deleted by using debug malloc
     cmsDeleteContext(c3);  // Should be deleted by using nomal malloc
     cmsDeleteContext(c4);  // Should be deleted by using debug malloc

     return 1;
}