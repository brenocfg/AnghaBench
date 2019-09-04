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
struct TYPE_3__ {int uType; } ;
typedef  TYPE_1__ STRRET ;

/* Variables and functions */
#define  STRRET_CSTR 130 
#define  STRRET_OFFSET 129 
#define  STRRET_WSTR 128 

__attribute__((used)) static const char *debugstr_strret(STRRET *s)
{
    switch (s->uType)
    {
        case STRRET_WSTR:
            return "STRRET_WSTR";
        case STRRET_CSTR:
            return "STRRET_CSTR";
        case STRRET_OFFSET:
            return "STRRET_OFFSET";
        default:
            return "STRRET_???";
    }
}