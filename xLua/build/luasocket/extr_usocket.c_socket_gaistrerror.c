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
#define  EAI_AGAIN 139 
#define  EAI_BADFLAGS 138 
#define  EAI_BADHINTS 137 
#define  EAI_FAIL 136 
#define  EAI_FAMILY 135 
#define  EAI_MEMORY 134 
#define  EAI_NONAME 133 
#define  EAI_OVERFLOW 132 
#define  EAI_PROTOCOL 131 
#define  EAI_SERVICE 130 
#define  EAI_SOCKTYPE 129 
#define  EAI_SYSTEM 128 
 int /*<<< orphan*/  errno ; 
 char const* gai_strerror (int) ; 
 char const* strerror (int /*<<< orphan*/ ) ; 

const char *socket_gaistrerror(int err) {
    if (err == 0) return NULL; 
    switch (err) {
        case EAI_AGAIN: return "temporary failure in name resolution";
        case EAI_BADFLAGS: return "invalid value for ai_flags";
#ifdef EAI_BADHINTS
        case EAI_BADHINTS: return "invalid value for hints";
#endif
        case EAI_FAIL: return "non-recoverable failure in name resolution";
        case EAI_FAMILY: return "ai_family not supported";
        case EAI_MEMORY: return "memory allocation failure";
        case EAI_NONAME: 
            return "host or service not provided, or not known";
        case EAI_OVERFLOW: return "argument buffer overflow";
#ifdef EAI_PROTOCOL
        case EAI_PROTOCOL: return "resolved protocol is unknown";
#endif
        case EAI_SERVICE: return "service not supported for socket type";
        case EAI_SOCKTYPE: return "ai_socktype not supported";
        case EAI_SYSTEM: return strerror(errno); 
        default: return gai_strerror(err);
    }
}