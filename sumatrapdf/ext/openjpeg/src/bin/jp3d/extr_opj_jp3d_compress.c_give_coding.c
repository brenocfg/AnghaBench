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
typedef  int /*<<< orphan*/  OPJ_ENTROPY_CODING ;

/* Variables and functions */
 int /*<<< orphan*/  ENCOD_2EB ; 
 int /*<<< orphan*/  ENCOD_3EB ; 
 int /*<<< orphan*/  ENCOD_UNKNOWN ; 
 scalar_t__ strncmp (char*,char*,int) ; 

OPJ_ENTROPY_CODING give_coding(char coding[3])
{

    if (strncmp(coding, "2EB", 3) == 0) {
        return ENCOD_2EB;
    }
    if (strncmp(coding, "3EB", 3) == 0) {
        return ENCOD_3EB;
    }
    /*if(strncmp(coding, "2GR", 3) == 0) {
        return ENCOD_2GR;
    }
    if(strncmp(coding, "3GR", 3) == 0) {
        return ENCOD_3GR;
    }*/

    return ENCOD_UNKNOWN;
}