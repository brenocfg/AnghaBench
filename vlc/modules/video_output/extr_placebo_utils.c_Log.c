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
struct vlc_object_t {int dummy; } ;
typedef  enum pl_log_level { ____Placeholder_pl_log_level } pl_log_level ;

/* Variables and functions */
#define  PL_LOG_DEBUG 132 
#define  PL_LOG_ERR 131 
#define  PL_LOG_FATAL 130 
#define  PL_LOG_INFO 129 
#define  PL_LOG_WARN 128 
 int /*<<< orphan*/  msg_Dbg (struct vlc_object_t*,char*,char const*) ; 
 int /*<<< orphan*/  msg_Err (struct vlc_object_t*,char*,char const*) ; 
 int /*<<< orphan*/  msg_Info (struct vlc_object_t*,char*,char const*) ; 
 int /*<<< orphan*/  msg_Warn (struct vlc_object_t*,char*,char const*) ; 

__attribute__((used)) static void Log(void *priv, enum pl_log_level level, const char *msg)
{
    struct vlc_object_t *obj = priv;

    switch (level) {
    case PL_LOG_FATAL: // fall through
    case PL_LOG_ERR:   msg_Err(obj,  "%s", msg); break;
    case PL_LOG_WARN:  msg_Warn(obj, "%s", msg); break;
    case PL_LOG_INFO:  msg_Info(obj, "%s", msg); break;
    case PL_LOG_DEBUG: msg_Dbg(obj,  "%s", msg); break;
    default: break;
    }
}