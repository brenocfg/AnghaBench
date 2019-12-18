#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {size_t* allowed_commands; } ;
typedef  TYPE_1__ user ;
typedef  size_t uint64_t ;

/* Variables and functions */
 scalar_t__ ACLGetCommandBitCoordinates (unsigned long,size_t*,size_t*) ; 
 scalar_t__ C_ERR ; 

int ACLGetUserCommandBit(user *u, unsigned long id) {
    uint64_t word, bit;
    if (ACLGetCommandBitCoordinates(id,&word,&bit) == C_ERR) return 0;
    return (u->allowed_commands[word] & bit) != 0;
}