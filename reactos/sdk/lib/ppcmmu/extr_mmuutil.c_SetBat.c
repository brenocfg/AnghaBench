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
 int /*<<< orphan*/  BATSET (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  d ; 
 int /*<<< orphan*/  i ; 

void SetBat( int bat, int inst, int batHi, int batLo ) {
    if( inst ) {
	switch( bat ) {
	    BATSET(0,i);
	    BATSET(1,i);
	    BATSET(2,i);
	    BATSET(3,i);
	}
    } else {
	switch( bat ) {
	    BATSET(0,d);
	    BATSET(1,d);
	    BATSET(2,d);
	    BATSET(3,d);
	}
    }
    __asm__("isync\n\tsync");
}