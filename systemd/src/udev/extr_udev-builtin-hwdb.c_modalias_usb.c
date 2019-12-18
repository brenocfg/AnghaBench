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
typedef  int uint16_t ;
typedef  int /*<<< orphan*/  sd_device ;

/* Variables and functions */
 scalar_t__ safe_atoux16 (char const*,int*) ; 
 scalar_t__ sd_device_get_sysattr_value (int /*<<< orphan*/ *,char*,char const**) ; 
 int /*<<< orphan*/  snprintf (char*,size_t,char*,int,int) ; 

__attribute__((used)) static const char *modalias_usb(sd_device *dev, char *s, size_t size) {
        const char *v, *p;
        uint16_t vn, pn;

        if (sd_device_get_sysattr_value(dev, "idVendor", &v) < 0)
                return NULL;
        if (sd_device_get_sysattr_value(dev, "idProduct", &p) < 0)
                return NULL;
        if (safe_atoux16(v, &vn) < 0)
                return NULL;
        if (safe_atoux16(p, &pn) < 0)
                return NULL;
        snprintf(s, size, "usb:v%04Xp%04X*", vn, pn);
        return s;
}