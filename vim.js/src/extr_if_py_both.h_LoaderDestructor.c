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
struct TYPE_4__ {int /*<<< orphan*/  module; } ;
typedef  TYPE_1__ LoaderObject ;

/* Variables and functions */
 int /*<<< orphan*/  DESTRUCTOR_FINISH (TYPE_1__*) ; 
 int /*<<< orphan*/  Py_DECREF (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
LoaderDestructor(LoaderObject *self)
{
    Py_DECREF(self->module);
    DESTRUCTOR_FINISH(self);
}