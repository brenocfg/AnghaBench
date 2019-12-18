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
typedef  int /*<<< orphan*/  vlc_object_t ;
struct vlc_logger_operations {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  STDERR_FILENO ; 
 int VLC_MSG_DBG ; 
 scalar_t__ VLC_MSG_ERR ; 
 int atoi (char const*) ; 
 struct vlc_logger_operations const color_ops ; 
 char* getenv (char*) ; 
 struct vlc_logger_operations const gray_ops ; 
 scalar_t__ isatty (int /*<<< orphan*/ ) ; 
 scalar_t__ var_InheritBool (int /*<<< orphan*/ *,char*) ; 
 int var_InheritInteger (int /*<<< orphan*/ *,char*) ; 
 void* verbosities ; 

__attribute__((used)) static const struct vlc_logger_operations *Open(vlc_object_t *obj,
                                                void **restrict sysp)
{
    int verbosity = -1;

    if (!var_InheritBool(obj, "quiet"))
    {
        const char *str = getenv("VLC_VERBOSE");
        if (str != NULL)
           verbosity = atoi(str);
        else
           verbosity = var_InheritInteger(obj, "verbose");
    }

    if (verbosity < 0)
        return NULL;

    verbosity += VLC_MSG_ERR;
    if (verbosity > VLC_MSG_DBG)
        verbosity = VLC_MSG_DBG;

    *sysp = verbosities + verbosity;

#if defined (HAVE_ISATTY) && !defined (_WIN32)
    if (isatty(STDERR_FILENO) && var_InheritBool(obj, "color"))
        return &color_ops;
#endif
    return &gray_ops;
}