#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ tv_usec; scalar_t__ tv_sec; } ;
struct TYPE_6__ {scalar_t__ tv_usec; scalar_t__ tv_sec; } ;
struct rusage {TYPE_2__ ru_stime; TYPE_1__ ru_utime; } ;
struct TYPE_8__ {scalar_t__ QuadPart; } ;
typedef  int OPJ_FLOAT64 ;
typedef  TYPE_3__ LARGE_INTEGER ;

/* Variables and functions */
 int /*<<< orphan*/  QueryPerformanceCounter (TYPE_3__*) ; 
 int /*<<< orphan*/  QueryPerformanceFrequency (TYPE_3__*) ; 
 int /*<<< orphan*/  getrusage (int /*<<< orphan*/ ,struct rusage*) ; 

OPJ_FLOAT64 opj_clock(void)
{
#ifdef _WIN32
    /* _WIN32: use QueryPerformance (very accurate) */
    LARGE_INTEGER freq, t ;
    /* freq is the clock speed of the CPU */
    QueryPerformanceFrequency(&freq) ;
    /* cout << "freq = " << ((double) freq.QuadPart) << endl; */
    /* t is the high resolution performance counter (see MSDN) */
    QueryPerformanceCounter(& t) ;
    return freq.QuadPart ? ((OPJ_FLOAT64) t.QuadPart / (OPJ_FLOAT64) freq.QuadPart)
           : 0 ;
#else
    /* Unix or Linux: use resource usage */
    struct rusage t;
    OPJ_FLOAT64 procTime;
    /* (1) Get the rusage data structure at this moment (man getrusage) */
    getrusage(0, &t);
    /* (2) What is the elapsed time ? - CPU time = User time + System time */
    /* (2a) Get the seconds */
    procTime = (OPJ_FLOAT64)(t.ru_utime.tv_sec + t.ru_stime.tv_sec);
    /* (2b) More precisely! Get the microseconds part ! */
    return (procTime + (OPJ_FLOAT64)(t.ru_utime.tv_usec + t.ru_stime.tv_usec) *
            1e-6) ;
#endif
}