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
 int /*<<< orphan*/  run_benchmark (char*) ; 
 int /*<<< orphan*/  trace (char*) ; 

__attribute__((used)) static void run_benchmarks(void)
{
    trace("Running benchmarks...\n");

    run_benchmark("dna.js");
    run_benchmark("base64.js");
    run_benchmark("validateinput.js");
}