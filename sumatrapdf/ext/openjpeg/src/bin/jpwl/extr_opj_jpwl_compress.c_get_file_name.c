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
 int OPJ_PATH_LEN ; 
 scalar_t__ malloc (int) ; 
 char* strtok (char*,char*) ; 

__attribute__((used)) static char * get_file_name(char *name)
{
    char *fname;
    fname = (char*)malloc(OPJ_PATH_LEN * sizeof(char));
    fname = strtok(name, ".");
    return fname;
}