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
typedef  size_t u_int ;
typedef  int /*<<< orphan*/  processorid_t ;
struct TYPE_3__ {scalar_t__ pi_state; } ;
typedef  TYPE_1__ processor_info_t ;
typedef  int /*<<< orphan*/  cpu_set_t ;
typedef  int /*<<< orphan*/  cpu ;

/* Variables and functions */
 int CPU_COUNT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CPU_ZERO (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PS_MYID ; 
 scalar_t__ P_ONLINE ; 
 int /*<<< orphan*/  _SC_NPROCESSORS_CONF ; 
 int /*<<< orphan*/  _SC_NPROCESSORS_MAX ; 
 int /*<<< orphan*/  _SC_NPROCESSORS_ONLN ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 scalar_t__ processor_info (int /*<<< orphan*/ ,TYPE_1__*) ; 
 scalar_t__ pset_info (int /*<<< orphan*/ ,int*,size_t*,int /*<<< orphan*/ *) ; 
 scalar_t__ sched_getaffinity (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int sysconf (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * vlc_alloc (int,int) ; 

unsigned vlc_GetCPUCount(void)
{
#if defined(HAVE_SCHED_GETAFFINITY)
    cpu_set_t cpu;

    CPU_ZERO(&cpu);
    if (sched_getaffinity (0, sizeof (cpu), &cpu) < 0)
        return 1;

    return CPU_COUNT (&cpu);

#elif defined(__SunOS)
    unsigned count = 0;
    int type;
    u_int numcpus;
    processor_info_t cpuinfo;

    processorid_t *cpulist = vlc_alloc (sysconf(_SC_NPROCESSORS_MAX), sizeof (*cpulist));
    if (unlikely(cpulist == NULL))
        return 1;

    if (pset_info(PS_MYID, &type, &numcpus, cpulist) == 0)
    {
        for (u_int i = 0; i < numcpus; i++)
            if (processor_info (cpulist[i], &cpuinfo) == 0)
                count += (cpuinfo.pi_state == P_ONLINE);
    }
    else
        count = sysconf (_SC_NPROCESSORS_ONLN);
    free (cpulist);
    return count ? count : 1;
#elif defined(_SC_NPROCESSORS_CONF)
    return sysconf(_SC_NPROCESSORS_CONF);
#else
#   warning "vlc_GetCPUCount is not implemented for your platform"
    return 1;
#endif
}