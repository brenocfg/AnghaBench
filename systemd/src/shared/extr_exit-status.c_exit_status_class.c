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
struct TYPE_3__ {int class; } ;

/* Variables and functions */
 size_t ELEMENTSOF (TYPE_1__*) ; 
#define  EXIT_STATUS_BSD 131 
#define  EXIT_STATUS_LIBC 130 
#define  EXIT_STATUS_LSB 129 
#define  EXIT_STATUS_SYSTEMD 128 
 TYPE_1__* exit_status_mappings ; 

const char* exit_status_class(int code) {
        if (code < 0 || (size_t) code >= ELEMENTSOF(exit_status_mappings))
                return NULL;

        switch (exit_status_mappings[code].class) {
        case EXIT_STATUS_LIBC:
                return "libc";
        case EXIT_STATUS_SYSTEMD:
                return "systemd";
        case EXIT_STATUS_LSB:
                return "LSB";
        case EXIT_STATUS_BSD:
                return "BSD";
        default: return NULL;
        }
}