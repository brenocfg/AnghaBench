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
struct file_handler_request {int /*<<< orphan*/  file; } ;

/* Variables and functions */
 int /*<<< orphan*/  SDL_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
file_handler_request_destroy(struct file_handler_request *req) {
    SDL_free(req->file);
}