#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  checkfun ;
struct TYPE_5__ {int /*<<< orphan*/  b_vars; int /*<<< orphan*/  b_fnum; int /*<<< orphan*/ * b_ffname; } ;
struct TYPE_4__ {TYPE_2__* buf; } ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  TYPE_1__ BufferObject ;

/* Variables and functions */
 int /*<<< orphan*/  BufferAttrs ; 
 scalar_t__ CheckBuffer ; 
 int /*<<< orphan*/ * NEW_DICTIONARY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ObjectDir (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * OptionsNew (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PyString_FromString (char*) ; 
 int /*<<< orphan*/ * Py_BuildValue (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Py_ssize_t_fmt ; 
 int /*<<< orphan*/  SREQ_BUF ; 
 scalar_t__ strcmp (char*,char*) ; 

__attribute__((used)) static PyObject *
BufferAttr(BufferObject *self, char *name)
{
    if (strcmp(name, "name") == 0)
	return PyString_FromString((self->buf->b_ffname == NULL
				    ? "" : (char *)self->buf->b_ffname));
    else if (strcmp(name, "number") == 0)
	return Py_BuildValue(Py_ssize_t_fmt, self->buf->b_fnum);
    else if (strcmp(name, "vars") == 0)
	return NEW_DICTIONARY(self->buf->b_vars);
    else if (strcmp(name, "options") == 0)
	return OptionsNew(SREQ_BUF, self->buf, (checkfun) CheckBuffer,
			(PyObject *) self);
    else if (strcmp(name, "__members__") == 0)
	return ObjectDir(NULL, BufferAttrs);
    else
	return NULL;
}