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
struct TYPE_3__ {int capacity; void* tablespaces; scalar_t__ num_tablespaces; } ;
typedef  TYPE_1__ Tablespaces ;
typedef  int /*<<< orphan*/  Tablespace ;

/* Variables and functions */
 void* palloc (int) ; 

__attribute__((used)) static Tablespaces *
tablespaces_alloc(int capacity)
{
	Tablespaces *tspcs;

	tspcs = palloc(sizeof(Tablespaces));
	tspcs->capacity = capacity;
	tspcs->num_tablespaces = 0;
	tspcs->tablespaces = palloc(sizeof(Tablespace) * tspcs->capacity);

	return tspcs;
}