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
struct instance {char* hostname; scalar_t__ pidfile; int /*<<< orphan*/ * pid_filename; scalar_t__ pid; int /*<<< orphan*/  mbuf_chunk_size; int /*<<< orphan*/  stats_interval; int /*<<< orphan*/  stats_addr; int /*<<< orphan*/  stats_port; int /*<<< orphan*/  conf_filename; int /*<<< orphan*/  log_filename; int /*<<< orphan*/  log_level; int /*<<< orphan*/ * ctx; } ;
typedef  scalar_t__ pid_t ;

/* Variables and functions */
 int /*<<< orphan*/  NC_CONF_PATH ; 
 int /*<<< orphan*/  NC_LOG_DEFAULT ; 
 int /*<<< orphan*/  NC_LOG_PATH ; 
 int NC_MAXHOSTNAMELEN ; 
 int /*<<< orphan*/  NC_MBUF_SIZE ; 
 int /*<<< orphan*/  NC_STATS_ADDR ; 
 int /*<<< orphan*/  NC_STATS_INTERVAL ; 
 int /*<<< orphan*/  NC_STATS_PORT ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  log_warn (char*,int /*<<< orphan*/ ) ; 
 int nc_gethostname (char*,int) ; 
 int /*<<< orphan*/  nc_snprintf (char*,int,char*) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
nc_set_default_options(struct instance *nci)
{
    int status;

    nci->ctx = NULL;

    nci->log_level = NC_LOG_DEFAULT;
    nci->log_filename = NC_LOG_PATH;

    nci->conf_filename = NC_CONF_PATH;

    nci->stats_port = NC_STATS_PORT;
    nci->stats_addr = NC_STATS_ADDR;
    nci->stats_interval = NC_STATS_INTERVAL;

    status = nc_gethostname(nci->hostname, NC_MAXHOSTNAMELEN);
    if (status < 0) {
        log_warn("gethostname failed, ignored: %s", strerror(errno));
        nc_snprintf(nci->hostname, NC_MAXHOSTNAMELEN, "unknown");
    }
    nci->hostname[NC_MAXHOSTNAMELEN - 1] = '\0';

    nci->mbuf_chunk_size = NC_MBUF_SIZE;

    nci->pid = (pid_t)-1;
    nci->pid_filename = NULL;
    nci->pidfile = 0;
}