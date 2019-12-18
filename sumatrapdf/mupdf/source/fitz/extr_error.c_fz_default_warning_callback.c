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
 int /*<<< orphan*/  ANDROID_LOG_WARN ; 
 int /*<<< orphan*/  OutputDebugStringA (char const*) ; 
 int /*<<< orphan*/  __android_log_print (int /*<<< orphan*/ ,char*,char*,char const*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  stderr ; 

void fz_default_warning_callback(void *user, const char *message)
{
	fprintf(stderr, "warning: %s\n", message);
#ifdef USE_OUTPUT_DEBUG_STRING
	OutputDebugStringA("warning: ");
	OutputDebugStringA(message);
	OutputDebugStringA("\n");
#endif
#ifdef USE_ANDROID_LOG
	__android_log_print(ANDROID_LOG_WARN, "libmupdf", "%s", message);
#endif
}