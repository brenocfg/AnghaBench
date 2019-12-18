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
typedef  int /*<<< orphan*/  va_list ;
typedef  scalar_t__ SDL_LogPriority ;

/* Variables and functions */
 int /*<<< orphan*/  LOGC (char*) ; 
 int /*<<< orphan*/  SDL_LOG_CATEGORY_VIDEO ; 
 int /*<<< orphan*/  SDL_LogMessageV (int /*<<< orphan*/ ,scalar_t__,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDL_free (char*) ; 
 char* SDL_malloc (scalar_t__) ; 
 scalar_t__ sdl_priority_from_av_level (int) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 scalar_t__ strlen (char const*) ; 

__attribute__((used)) static void
av_log_callback(void *avcl, int level, const char *fmt, va_list vl) {
    SDL_LogPriority priority = sdl_priority_from_av_level(level);
    if (priority == 0) {
        return;
    }
    char *local_fmt = SDL_malloc(strlen(fmt) + 10);
    if (!local_fmt) {
        LOGC("Could not allocate string");
        return;
    }
    // strcpy is safe here, the destination is large enough
    strcpy(local_fmt, "[FFmpeg] ");
    strcpy(local_fmt + 9, fmt);
    SDL_LogMessageV(SDL_LOG_CATEGORY_VIDEO, priority, local_fmt, vl);
    SDL_free(local_fmt);
}