#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_2__* buf; } ;
struct TYPE_6__ {int /*<<< orphan*/  ml_line_count; } ;
struct TYPE_7__ {TYPE_1__ b_ml; } ;
typedef  int PyInt ;
typedef  TYPE_3__ BufferObject ;

/* Variables and functions */
 scalar_t__ CheckBuffer (TYPE_3__*) ; 

__attribute__((used)) static PyInt
BufferLength(BufferObject *self)
{
    /* HOW DO WE SIGNAL AN ERROR FROM THIS FUNCTION? */
    if (CheckBuffer(self))
	return -1; /* ??? */

    return (PyInt)(self->buf->b_ml.ml_line_count);
}