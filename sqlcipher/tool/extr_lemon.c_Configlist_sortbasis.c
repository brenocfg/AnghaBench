#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct config {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  bp; } ;

/* Variables and functions */
 int /*<<< orphan*/  Configcmp ; 
 struct config* basis ; 
 scalar_t__ basisend ; 
 TYPE_1__* current ; 
 scalar_t__ msort (char*,char**,int /*<<< orphan*/ ) ; 

void Configlist_sortbasis(void){
  basis = (struct config*)msort((char*)current,(char**)&(current->bp),
                                Configcmp);
  basisend = 0;
  return;
}