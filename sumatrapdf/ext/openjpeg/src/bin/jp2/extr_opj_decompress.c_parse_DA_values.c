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
typedef  unsigned int OPJ_UINT32 ;

/* Variables and functions */
 int EXIT_FAILURE ; 
 int EXIT_SUCCESS ; 
 int atoi (char*) ; 
 char* strtok (char*,char*) ; 

int parse_DA_values(char* inArg, unsigned int *DA_x0, unsigned int *DA_y0,
                    unsigned int *DA_x1, unsigned int *DA_y1)
{
    int it = 0;
    int values[4];
    char delims[] = ",";
    char *result = NULL;
    result = strtok(inArg, delims);

    while ((result != NULL) && (it < 4)) {
        values[it] = atoi(result);
        result = strtok(NULL, delims);
        it++;
    }

    if (it != 4) {
        return EXIT_FAILURE;
    } else {
        *DA_x0 = (OPJ_UINT32)values[0];
        *DA_y0 = (OPJ_UINT32)values[1];
        *DA_x1 = (OPJ_UINT32)values[2];
        *DA_y1 = (OPJ_UINT32)values[3];
        return EXIT_SUCCESS;
    }
}