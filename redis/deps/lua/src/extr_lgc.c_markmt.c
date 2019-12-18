#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__* mt; } ;
typedef  TYPE_1__ global_State ;

/* Variables and functions */
 int NUM_TAGS ; 
 int /*<<< orphan*/  markobject (TYPE_1__*,scalar_t__) ; 

__attribute__((used)) static void markmt (global_State *g) {
  int i;
  for (i=0; i<NUM_TAGS; i++)
    if (g->mt[i]) markobject(g, g->mt[i]);
}