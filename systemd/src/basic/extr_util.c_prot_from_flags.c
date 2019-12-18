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
 int EINVAL ; 
 int O_ACCMODE ; 
#define  O_RDONLY 130 
#define  O_RDWR 129 
#define  O_WRONLY 128 
 int PROT_READ ; 
 int PROT_WRITE ; 

int prot_from_flags(int flags) {

        switch (flags & O_ACCMODE) {

        case O_RDONLY:
                return PROT_READ;

        case O_WRONLY:
                return PROT_WRITE;

        case O_RDWR:
                return PROT_READ|PROT_WRITE;

        default:
                return -EINVAL;
        }
}