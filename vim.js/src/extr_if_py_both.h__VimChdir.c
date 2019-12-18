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
typedef  int /*<<< orphan*/  char_u ;
typedef  int /*<<< orphan*/  PyObject ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  N_ (char*) ; 
 int /*<<< orphan*/  PyErr_SET_VIM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * PyObject_Call (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PyObject_CallFunctionObjArgs (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_DECREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_XDECREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * StringToChars (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 scalar_t__ VimTryEnd () ; 
 int /*<<< orphan*/  VimTryStart () ; 
 int /*<<< orphan*/  post_chdir (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  py_getcwd ; 
 scalar_t__ vim_chdir (int /*<<< orphan*/ *) ; 

__attribute__((used)) static PyObject *
_VimChdir(PyObject *_chdir, PyObject *args, PyObject *kwargs)
{
    PyObject	*ret;
    PyObject	*newwd;
    PyObject	*todecref;
    char_u	*new_dir;

    if (_chdir == NULL)
	return NULL;
    if (!(ret = PyObject_Call(_chdir, args, kwargs)))
	return NULL;

    if (!(newwd = PyObject_CallFunctionObjArgs(py_getcwd, NULL)))
    {
	Py_DECREF(ret);
	return NULL;
    }

    if (!(new_dir = StringToChars(newwd, &todecref)))
    {
	Py_DECREF(ret);
	Py_DECREF(newwd);
	return NULL;
    }

    VimTryStart();

    if (vim_chdir(new_dir))
    {
	Py_DECREF(ret);
	Py_DECREF(newwd);
	Py_XDECREF(todecref);

	if (VimTryEnd())
	    return NULL;

	PyErr_SET_VIM(N_("failed to change directory"));
	return NULL;
    }

    Py_DECREF(newwd);
    Py_XDECREF(todecref);

    post_chdir(FALSE);

    if (VimTryEnd())
    {
	Py_DECREF(ret);
	return NULL;
    }

    return ret;
}