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
typedef  int /*<<< orphan*/  PyObject ;
typedef  int /*<<< orphan*/  PyInt ;
typedef  int /*<<< orphan*/  BufferObject ;

/* Variables and functions */
 int /*<<< orphan*/  RBAsSlice (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static PyInt
BufferAssSlice(PyObject *self, PyInt lo, PyInt hi, PyObject *val)
{
    return RBAsSlice((BufferObject *)(self), lo, hi, val, 1, -1, NULL);
}