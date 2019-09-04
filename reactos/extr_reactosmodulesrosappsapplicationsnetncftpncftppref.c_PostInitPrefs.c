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
struct TYPE_5__ {scalar_t__ dataPortMode; } ;
struct TYPE_4__ {char* defaultAnonPassword; } ;

/* Variables and functions */
 int /*<<< orphan*/  FTPInitializeAnonPassword (TYPE_1__*) ; 
 TYPE_2__ gConn ; 
 scalar_t__ gFwDataPortMode ; 
 TYPE_1__ gLib ; 
 int /*<<< orphan*/  gPrefsDirty ; 

void
PostInitPrefs(void)
{
	if (gLib.defaultAnonPassword[0] == '\0') {
		FTPInitializeAnonPassword(&gLib);
		gPrefsDirty++;
	}
	if (gFwDataPortMode >= 0)
		gConn.dataPortMode = gFwDataPortMode;
}