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
typedef  int cmsUInt32Number ;
typedef  int cmsInt32Number ;
typedef  scalar_t__ cmsFloat64Number ;

/* Variables and functions */
 int /*<<< orphan*/  Die (char*) ; 
 int _cmsQuickFloorWord (scalar_t__) ; 

__attribute__((used)) static
cmsInt32Number CheckQuickFloorWord(void)
{
    cmsUInt32Number i;

    for (i=0; i < 65535; i++) {

        if (_cmsQuickFloorWord((cmsFloat64Number) i + 0.1234) != i) {

            Die("\nOOOPPSS! _cmsQuickFloorWord() does not work as expected in your machine!\n\n"
                "Please, edit lcms2mt.h and uncomment the CMS_DONT_USE_FAST_FLOOR toggle.\n");
            return 0;
        }
    }

    return 1;
}