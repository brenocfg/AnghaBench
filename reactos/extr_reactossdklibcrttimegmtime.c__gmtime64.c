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
struct TYPE_3__ {scalar_t__ time_buffer; } ;
typedef  TYPE_1__ thread_data_t ;
struct tm {int dummy; } ;
typedef  int /*<<< orphan*/  __time64_t ;

/* Variables and functions */
 struct tm* _gmtime_worker (scalar_t__,int /*<<< orphan*/  const,int /*<<< orphan*/ ) ; 
 scalar_t__ malloc (int) ; 
 TYPE_1__* msvcrt_get_thread_data () ; 

struct tm *
_gmtime64(const __time64_t * ptime)
{
    thread_data_t *data = msvcrt_get_thread_data();

    /* Validate parameters */
    if (!ptime || *ptime < 0)
    {
        return NULL;
    }

    if(!data->time_buffer)
        data->time_buffer = malloc(sizeof(struct tm));

    /* Use _gmtime_worker to do the real work */
    return _gmtime_worker(data->time_buffer, *ptime, 0);
}