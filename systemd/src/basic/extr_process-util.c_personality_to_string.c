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
 unsigned long PER_LINUX ; 
 unsigned long PER_LINUX32 ; 
 int SECONDARY_ARCHITECTURE ; 
 int _ARCHITECTURE_INVALID ; 
 char const* architecture_to_string (int) ; 
 int native_architecture () ; 

const char* personality_to_string(unsigned long p) {
        int architecture = _ARCHITECTURE_INVALID;

        if (p == PER_LINUX)
                architecture = native_architecture();
#ifdef SECONDARY_ARCHITECTURE
        else if (p == PER_LINUX32)
                architecture = SECONDARY_ARCHITECTURE;
#endif

        if (architecture < 0)
                return NULL;

        return architecture_to_string(architecture);
}