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
typedef  int /*<<< orphan*/  process_t ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_LEN (char const* const*) ; 
 int /*<<< orphan*/  PROCESS_NONE ; 
 int /*<<< orphan*/  SDL_free (void*) ; 
 int /*<<< orphan*/  adb_execute (char const*,char const* const*,int /*<<< orphan*/ ) ; 
 char* strquote (char const*) ; 

process_t
adb_install(const char *serial, const char *local) {
#ifdef __WINDOWS__
    // Windows will parse the string, so the local name must be quoted
    // (see sys/win/command.c)
    local = strquote(local);
    if (!local) {
        return PROCESS_NONE;
    }
#endif

    const char *const adb_cmd[] = {"install", "-r", local};
    process_t proc = adb_execute(serial, adb_cmd, ARRAY_LEN(adb_cmd));

#ifdef __WINDOWS__
    SDL_free((void *) local);
#endif

    return proc;
}