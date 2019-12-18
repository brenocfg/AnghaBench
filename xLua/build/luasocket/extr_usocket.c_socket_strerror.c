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
#define  EACCES 134 
#define  EADDRINUSE 133 
#define  ECONNABORTED 132 
#define  ECONNREFUSED 131 
#define  ECONNRESET 130 
#define  EISCONN 129 
#define  ETIMEDOUT 128 
 char const* io_strerror (int) ; 
 char const* strerror (int) ; 

const char *socket_strerror(int err) {
    if (err <= 0) return io_strerror(err);
    switch (err) {
        case EADDRINUSE: return "address already in use";
        case EISCONN: return "already connected";
        case EACCES: return "permission denied";
        case ECONNREFUSED: return "connection refused";
        case ECONNABORTED: return "closed";
        case ECONNRESET: return "closed";
        case ETIMEDOUT: return "timeout";
        default: return strerror(err);
    }
}