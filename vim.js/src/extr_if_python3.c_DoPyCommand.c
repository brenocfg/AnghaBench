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
typedef  int /*<<< orphan*/  (* runner ) (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ;
typedef  int /*<<< orphan*/  (* rangeinitializer ) (void*) ;
typedef  int /*<<< orphan*/  char_u ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  int /*<<< orphan*/  PyGILState_STATE ;
typedef  scalar_t__ Ptr ;
typedef  int /*<<< orphan*/  GrafPtr ;

/* Variables and functions */
 int /*<<< orphan*/  CODEC_ERROR_HANDLER ; 
 scalar_t__ ENC_OPT ; 
 int /*<<< orphan*/  GetPort (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LC_NUMERIC ; 
 int /*<<< orphan*/  PyBytes_AsString (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyGILState_Ensure () ; 
 int /*<<< orphan*/  PyGILState_Release (int /*<<< orphan*/ ) ; 
 scalar_t__ PyMac_Initialize ; 
 int /*<<< orphan*/ * PyUnicode_AsEncodedString (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * PyUnicode_Decode (char const*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Py_XDECREF (int /*<<< orphan*/ *) ; 
 scalar_t__ Python3_Init () ; 
 int /*<<< orphan*/  PythonIO_Flush () ; 
 int /*<<< orphan*/  Python_Lock_Vim () ; 
 int /*<<< orphan*/  Python_Release_Vim () ; 
 scalar_t__ STRCMP (char*,char*) ; 
 int /*<<< orphan*/  SetPort (int /*<<< orphan*/ ) ; 
 scalar_t__ kUnresolvedCFragSymbolAddress ; 
 char* setlocale (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 int /*<<< orphan*/  vim_free (char*) ; 
 scalar_t__ vim_strsave (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
DoPyCommand(const char *cmd, rangeinitializer init_range, runner run, void *arg)
{
#if defined(MACOS) && !defined(MACOS_X_UNIX)
    GrafPtr		oldPort;
#endif
#if defined(HAVE_LOCALE_H) || defined(X_LOCALE)
    char		*saved_locale;
#endif
    PyObject		*cmdstr;
    PyObject		*cmdbytes;
    PyGILState_STATE	pygilstate;

#if defined(MACOS) && !defined(MACOS_X_UNIX)
    GetPort(&oldPort);
    /* Check if the Python library is available */
    if ((Ptr)PyMac_Initialize == (Ptr)kUnresolvedCFragSymbolAddress)
	goto theend;
#endif
    if (Python3_Init())
	goto theend;

    init_range(arg);

    Python_Release_Vim();	    /* leave vim */

#if defined(HAVE_LOCALE_H) || defined(X_LOCALE)
    /* Python only works properly when the LC_NUMERIC locale is "C". */
    saved_locale = setlocale(LC_NUMERIC, NULL);
    if (saved_locale == NULL || STRCMP(saved_locale, "C") == 0)
	saved_locale = NULL;
    else
    {
	/* Need to make a copy, value may change when setting new locale. */
	saved_locale = (char *)vim_strsave((char_u *)saved_locale);
	(void)setlocale(LC_NUMERIC, "C");
    }
#endif

    pygilstate = PyGILState_Ensure();

    /* PyRun_SimpleString expects a UTF-8 string. Wrong encoding may cause
     * SyntaxError (unicode error). */
    cmdstr = PyUnicode_Decode(cmd, strlen(cmd),
					(char *)ENC_OPT, CODEC_ERROR_HANDLER);
    cmdbytes = PyUnicode_AsEncodedString(cmdstr, "utf-8", CODEC_ERROR_HANDLER);
    Py_XDECREF(cmdstr);

    run(PyBytes_AsString(cmdbytes), arg, &pygilstate);
    Py_XDECREF(cmdbytes);

    PyGILState_Release(pygilstate);

#if defined(HAVE_LOCALE_H) || defined(X_LOCALE)
    if (saved_locale != NULL)
    {
	(void)setlocale(LC_NUMERIC, saved_locale);
	vim_free(saved_locale);
    }
#endif

    Python_Lock_Vim();		    /* enter vim */
    PythonIO_Flush();
#if defined(MACOS) && !defined(MACOS_X_UNIX)
    SetPort(oldPort);
#endif

theend:
    return;	    /* keeps lint happy */
}