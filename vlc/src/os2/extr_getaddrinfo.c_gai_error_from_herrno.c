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
 int EAI_AGAIN ; 
 int EAI_FAIL ; 
 int EAI_NODATA ; 
 int EAI_NONAME ; 
 int EAI_SYSTEM ; 
#define  HOST_NOT_FOUND 132 
#define  NO_ADDRESS 131 
#define  NO_DATA 130 
#define  NO_RECOVERY 129 
#define  TRY_AGAIN 128 
 int h_errno ; 

__attribute__((used)) static int
gai_error_from_herrno (void)
{
    switch (h_errno)
    {
        case HOST_NOT_FOUND:
            return EAI_NONAME;

        case NO_ADDRESS:
# if (NO_ADDRESS != NO_DATA)
        case NO_DATA:
# endif
            return EAI_NODATA;

        case NO_RECOVERY:
            return EAI_FAIL;

        case TRY_AGAIN:
            return EAI_AGAIN;
    }
    return EAI_SYSTEM;
}