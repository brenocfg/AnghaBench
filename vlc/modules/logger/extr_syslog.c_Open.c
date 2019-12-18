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
typedef  int /*<<< orphan*/  vlc_object_t ;
struct vlc_logger_operations {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_DEBUG ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  LOG_INFO ; 
 int LOG_MASK (int /*<<< orphan*/ ) ; 
 int LOG_NDELAY ; 
 int LOG_PID ; 
 int /*<<< orphan*/  LOG_WARNING ; 
 scalar_t__ default_ident ; 
 int /*<<< orphan*/  openlog (char*,int,int) ; 
 struct vlc_logger_operations const ops ; 
 int /*<<< orphan*/  setlogmask (int) ; 
 scalar_t__ var_InheritBool (int /*<<< orphan*/ *,char*) ; 
 int var_InheritFacility (int /*<<< orphan*/ *,char*) ; 
 char* var_InheritString (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static const struct vlc_logger_operations *Open(vlc_object_t *obj,
                                                void **restrict sysp)
{
    if (!var_InheritBool(obj, "syslog"))
        return NULL;

    char *ident = var_InheritString(obj, "syslog-ident");
    if (ident == NULL)
        ident = (char *)default_ident;
    *sysp = ident;

    /* Open log */
    int facility = var_InheritFacility(obj, "syslog-facility");

    openlog(ident, LOG_PID | LOG_NDELAY, facility);

    /* Set priority filter */
    int mask = LOG_MASK(LOG_ERR) | LOG_MASK(LOG_WARNING) | LOG_MASK(LOG_INFO);
    if (var_InheritBool(obj, "syslog-debug"))
        mask |= LOG_MASK(LOG_DEBUG);

    setlogmask(mask);

    return &ops;
}