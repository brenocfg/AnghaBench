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
struct TYPE_3__ {char const* msg; int code; } ;
typedef  TYPE_1__ wsaerrmsg_t ;

/* Variables and functions */
 char const** _sys_errlist ; 
 scalar_t__ _sys_nerr ; 
 TYPE_1__* wsaerrmsg ; 

const char *vlc_strerror_c(int errnum)
{
    /* C run-time errors */
    if ((unsigned)errnum < (unsigned)_sys_nerr)
        return _sys_errlist[errnum];

    /* Windows socket errors */
    for (const wsaerrmsg_t *e = wsaerrmsg; e->msg != NULL; e++)
        if (e->code == errnum)
            return e->msg;

    return "Unknown error";
}