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
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  exit (int) ; 

__attribute__((used)) static void crash(int errorCode){
    /* abort if AFL/libfuzzer, exit otherwise */
    #ifdef FUZZING_BUILD_MODE_UNSAFE_FOR_PRODUCTION /* could also use __AFL_COMPILER */
        abort();
    #else
        exit(errorCode);
    #endif
}