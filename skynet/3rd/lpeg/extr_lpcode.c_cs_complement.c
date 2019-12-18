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
struct TYPE_3__ {int /*<<< orphan*/ * cs; } ;
typedef  TYPE_1__ Charset ;

/* Variables and functions */
 size_t i ; 
 int /*<<< orphan*/  loopset (size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cs_complement (Charset *cs) {
  loopset(i, cs->cs[i] = ~cs->cs[i]);
}