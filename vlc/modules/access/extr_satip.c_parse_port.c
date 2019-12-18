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
typedef  int uint16_t ;

/* Variables and functions */
 int UINT16_MAX ; 
 int VLC_EBADVAR ; 
 int atoi (char*) ; 

__attribute__((used)) static int parse_port(char *str, uint16_t *port)
{
    int p = atoi(str);
    if (p < 0 || p > UINT16_MAX)
        return VLC_EBADVAR;

    *port = p;

    return 0;
}