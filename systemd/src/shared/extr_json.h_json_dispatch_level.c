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
typedef  int JsonDispatchFlags ;

/* Variables and functions */
 int JSON_DEBUG ; 
 int JSON_LOG ; 
 int JSON_PERMISSIVE ; 
 int JSON_WARNING ; 
 int LOG_DEBUG ; 
 int LOG_ERR ; 
 int LOG_WARNING ; 

__attribute__((used)) static inline int json_dispatch_level(JsonDispatchFlags flags) {

        /* Did the user request no logging? If so, then never log higher than LOG_DEBUG. Also, if this is marked as
         * debug message, then also log at debug level. */

        if (!(flags & JSON_LOG) ||
            (flags & JSON_DEBUG))
                return LOG_DEBUG;

        /* Are we invoked in permissive mode, or is this explicitly marked as warning message? Then this should be
         * printed at LOG_WARNING */
        if (flags & (JSON_PERMISSIVE|JSON_WARNING))
                return LOG_WARNING;

        /* Otherwise it's an error. */
        return LOG_ERR;
}