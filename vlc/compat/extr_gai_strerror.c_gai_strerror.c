#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {char const* msg; int code; } ;

/* Variables and functions */
 TYPE_1__* gai_errlist ; 
 char const* gai_unknownerr ; 

const char *gai_strerror (int errnum)
{
    for (unsigned i = 0; *gai_errlist[i].msg; i++)
        if (errnum == gai_errlist[i].code)
            return gai_errlist[i].msg;

    return gai_unknownerr;
}