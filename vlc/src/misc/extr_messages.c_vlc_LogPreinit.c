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
typedef  int /*<<< orphan*/  vlc_logger_t ;
struct vlc_logger {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/ * logger; } ;
struct TYPE_6__ {TYPE_1__ obj; } ;
typedef  TYPE_2__ libvlc_int_t ;

/* Variables and functions */
 int /*<<< orphan*/  VLC_OBJECT (TYPE_2__*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 struct vlc_logger* vlc_LogEarlyOpen (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_LogSpam (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_LogSwitch (int /*<<< orphan*/ *,struct vlc_logger*) ; 
 int /*<<< orphan*/ * vlc_LogSwitchCreate () ; 

int vlc_LogPreinit(libvlc_int_t *vlc)
{
    vlc_logger_t *logger = vlc_LogSwitchCreate();
    if (unlikely(logger == NULL))
        return -1;
    vlc->obj.logger = logger;

    struct vlc_logger *early = vlc_LogEarlyOpen(logger);
    if (early != NULL) {
        vlc_LogSwitch(logger, early);
        vlc_LogSpam(VLC_OBJECT(vlc));
    }
    return 0;
}