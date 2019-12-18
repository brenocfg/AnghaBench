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
typedef  scalar_t__ paddr_t ;

/* Variables and functions */
 char GetPhysByte (scalar_t__) ; 
 scalar_t__ RCV ; 
 int /*<<< orphan*/  chr (char*) ; 
 int /*<<< orphan*/  sync () ; 

inline char recv(char *serport) {
    char c;

    while( !chr(serport) ) sync();

    c = GetPhysByte((paddr_t)serport+RCV);
    sync();

    return c;
}