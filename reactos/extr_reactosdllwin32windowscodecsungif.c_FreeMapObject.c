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
struct TYPE_4__ {struct TYPE_4__* Colors; } ;
typedef  TYPE_1__ ColorMapObject ;

/* Variables and functions */
 int /*<<< orphan*/  ungif_free (TYPE_1__*) ; 

__attribute__((used)) static void
FreeMapObject(ColorMapObject * Object) {

    if (Object != NULL) {
        ungif_free(Object->Colors);
        ungif_free(Object);
        /*** FIXME:
         * When we are willing to break API we need to make this function
         * FreeMapObject(ColorMapObject **Object)
         * and do this assignment to NULL here:
         * *Object = NULL;
         */
    }
}