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
 int GetPhysByte (scalar_t__) ; 
 scalar_t__ LSR ; 
 int /*<<< orphan*/  SetPhysByte (scalar_t__,char) ; 
 scalar_t__ THR ; 
 int /*<<< orphan*/  sync () ; 

inline void send(char *serport, char c) {
	/* Wait for Clear to Send */
    while( !(GetPhysByte((paddr_t)serport+LSR) & 0x20) ) sync();

    SetPhysByte((paddr_t)serport+THR, c);
    sync();
}