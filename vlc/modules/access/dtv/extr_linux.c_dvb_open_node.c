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
typedef  int /*<<< orphan*/  path ;
struct TYPE_3__ {int /*<<< orphan*/  dir; int /*<<< orphan*/  device; } ;
typedef  TYPE_1__ dvb_device_t ;

/* Variables and functions */
 int O_NONBLOCK ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 int vlc_openat (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int dvb_open_node (dvb_device_t *d, const char *type, int flags)
{
    char path[strlen (type) + 4];

    snprintf (path, sizeof (path), "%s%u", type, d->device);
    return vlc_openat (d->dir, path, flags | O_NONBLOCK);
}