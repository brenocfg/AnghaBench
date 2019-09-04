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
struct TYPE_3__ {scalar_t__ hic; int /*<<< orphan*/  fccHandler; } ;
typedef  TYPE_1__ driver_info_t ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  mmioStringToFOURCCA (char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ try_driver (TYPE_1__*) ; 

__attribute__((used)) static BOOL ICLocate_enum_handler(const char *name, const char *driver, unsigned int nr, void *param)
{
    driver_info_t *info = param;
    info->fccHandler = mmioStringToFOURCCA(name + 5, 0);
    info->hic = try_driver(info);
    return info->hic != 0;
}