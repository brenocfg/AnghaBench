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
 int O_BINARY ; 
 int O_RDONLY ; 
 int /*<<< orphan*/  free (char*) ; 
 int open (char const*,int) ; 
 char* wpp_find_include (char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int open_typelib(const char *name)
{
    char *file_name;
    int fd;

    file_name = wpp_find_include(name, NULL);
    if(!file_name)
        return open(name, O_RDONLY | O_BINARY );

    fd = open(file_name, O_RDONLY | O_BINARY );
    free(file_name);
    return fd;
}