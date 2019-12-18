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

/* Variables and functions */
 int /*<<< orphan*/  EMSG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PYTHON3_HOME ; 
 int /*<<< orphan*/  Py3Init_vim ; 
 int /*<<< orphan*/  PyEval_InitThreads () ; 
 int /*<<< orphan*/  PyEval_SaveThread () ; 
 int /*<<< orphan*/  PyImport_AddModule (char*) ; 
 int /*<<< orphan*/  PyImport_AppendInittab (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PyMac_Initialize () ; 
 int /*<<< orphan*/  PyModule_GetDict (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PyRun_SimpleString (char*) ; 
 int /*<<< orphan*/  Py_Initialize () ; 
 int /*<<< orphan*/  Py_SetPythonHome (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PythonIO_Flush () ; 
 scalar_t__ PythonIO_Init_io () ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  get_py3_exceptions () ; 
 int /*<<< orphan*/  globals ; 
 int /*<<< orphan*/  init_structs () ; 
 int py3initialised ; 
 int /*<<< orphan*/  python3_enabled (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
Python3_Init(void)
{
    if (!py3initialised)
    {
#ifdef DYNAMIC_PYTHON3
	if (!python3_enabled(TRUE))
	{
	    EMSG(_("E263: Sorry, this command is disabled, the Python library could not be loaded."));
	    goto fail;
	}
#endif

	init_structs();


#ifdef PYTHON3_HOME
	Py_SetPythonHome(PYTHON3_HOME);
#endif

	PyImport_AppendInittab("vim", Py3Init_vim);

#if !defined(MACOS) || defined(MACOS_X_UNIX)
	Py_Initialize();
#else
	PyMac_Initialize();
#endif
	/* Initialise threads, and below save the state using
	 * PyEval_SaveThread.  Without the call to PyEval_SaveThread, thread
	 * specific state (such as the system trace hook), will be lost
	 * between invocations of Python code. */
	PyEval_InitThreads();
#ifdef DYNAMIC_PYTHON3
	get_py3_exceptions();
#endif

	if (PythonIO_Init_io())
	    goto fail;

	globals = PyModule_GetDict(PyImport_AddModule("__main__"));

	/* Remove the element from sys.path that was added because of our
	 * argv[0] value in Py3Init_vim().  Previously we used an empty
	 * string, but depending on the OS we then get an empty entry or
	 * the current directory in sys.path.
	 * Only after vim has been imported, the element does exist in
	 * sys.path.
	 */
	PyRun_SimpleString("import vim; import sys; sys.path = list(filter(lambda x: not x.endswith('must>not&exist'), sys.path))");

	/* lock is created and acquired in PyEval_InitThreads() and thread
	 * state is created in Py_Initialize()
	 * there _PyGILState_NoteThreadState() also sets gilcounter to 1
	 * (python must have threads enabled!)
	 * so the following does both: unlock GIL and save thread state in TLS
	 * without deleting thread state
	 */
	PyEval_SaveThread();

	py3initialised = 1;
    }

    return 0;

fail:
    /* We call PythonIO_Flush() here to print any Python errors.
     * This is OK, as it is possible to call this function even
     * if PythonIO_Init_io() has not completed successfully (it will
     * not do anything in this case).
     */
    PythonIO_Flush();
    return -1;
}