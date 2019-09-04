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
typedef  int /*<<< orphan*/  SDL_LogPriority ;

/* Variables and functions */
#define  AV_LOG_ERROR 132 
#define  AV_LOG_FATAL 131 
#define  AV_LOG_INFO 130 
#define  AV_LOG_PANIC 129 
#define  AV_LOG_WARNING 128 
 int /*<<< orphan*/  SDL_LOG_PRIORITY_CRITICAL ; 
 int /*<<< orphan*/  SDL_LOG_PRIORITY_ERROR ; 
 int /*<<< orphan*/  SDL_LOG_PRIORITY_INFO ; 
 int /*<<< orphan*/  SDL_LOG_PRIORITY_WARN ; 

__attribute__((used)) static SDL_LogPriority
sdl_priority_from_av_level(int level) {
    switch (level) {
        case AV_LOG_PANIC:
        case AV_LOG_FATAL:
            return SDL_LOG_PRIORITY_CRITICAL;
        case AV_LOG_ERROR:
            return SDL_LOG_PRIORITY_ERROR;
        case AV_LOG_WARNING:
            return SDL_LOG_PRIORITY_WARN;
        case AV_LOG_INFO:
            return SDL_LOG_PRIORITY_INFO;
    }
    // do not forward others, which are too verbose
    return 0;
}