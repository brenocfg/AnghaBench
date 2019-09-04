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
struct request {scalar_t__ file; } ;

/* Variables and functions */
 int /*<<< orphan*/  SDL_free (void*) ; 

__attribute__((used)) static void
request_free(struct request *req) {
    if (!req) {
        return;
    }
    SDL_free((void *) req->file);
    SDL_free((void *) req);
}