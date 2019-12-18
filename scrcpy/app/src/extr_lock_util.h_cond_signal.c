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
typedef  int /*<<< orphan*/  SDL_cond ;

/* Variables and functions */
 int /*<<< orphan*/  LOGC (char*) ; 
 scalar_t__ SDL_CondSignal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  abort () ; 

__attribute__((used)) static inline void
cond_signal(SDL_cond *cond) {
    if (SDL_CondSignal(cond)) {
        LOGC("Could not signal a condition");
        abort();
    }
}