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

/* Variables and functions */
#define  WSAHOST_NOT_FOUND 128 
 char const* io_strerror (int) ; 
 char const* wstrerror (int) ; 

const char *socket_hoststrerror(int err) {
    if (err <= 0) return io_strerror(err);
    switch (err) {
        case WSAHOST_NOT_FOUND: return "host not found";
        default: return wstrerror(err); 
    }
}