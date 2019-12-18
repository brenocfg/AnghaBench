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
struct logger {char* name; scalar_t__ fd; int /*<<< orphan*/  level; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_EMERG ; 
 int /*<<< orphan*/  LOG_PVERB ; 
 int /*<<< orphan*/  MAX (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MIN (int,int /*<<< orphan*/ ) ; 
 int O_APPEND ; 
 int O_CREAT ; 
 int O_WRONLY ; 
 scalar_t__ STDERR_FILENO ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  log_stderr (char*,char*,int /*<<< orphan*/ ) ; 
 struct logger logger ; 
 scalar_t__ open (char*,int,int) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char*) ; 

int
log_init(int level, char *name)
{
    struct logger *l = &logger;

    l->level = MAX(LOG_EMERG, MIN(level, LOG_PVERB));
    l->name = name;
    if (name == NULL || !strlen(name)) {
        l->fd = STDERR_FILENO;
    } else {
        l->fd = open(name, O_WRONLY | O_APPEND | O_CREAT, 0644);
        if (l->fd < 0) {
            log_stderr("opening log file '%s' failed: %s", name,
                       strerror(errno));
            return -1;
        }
    }

    return 0;
}