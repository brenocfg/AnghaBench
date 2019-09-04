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
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static void usage() {
    printf("Usage: wrk <options> <url>                            \n"
           "  Options:                                            \n"
           "    -c, --connections <N>  Connections to keep open   \n"
           "    -d, --duration    <T>  Duration of test           \n"
           "    -t, --threads     <N>  Number of threads to use   \n"
           "                                                      \n"
           "    -s, --script      <S>  Load Lua script file       \n"
           "    -H, --header      <H>  Add header to request      \n"
           "        --latency          Print latency statistics   \n"
           "        --timeout     <T>  Socket/request timeout     \n"
           "    -v, --version          Print version details      \n"
           "                                                      \n"
           "  Numeric arguments may include a SI unit (1k, 1M, 1G)\n"
           "  Time arguments may include a time unit (2s, 2m, 2h)\n");
}