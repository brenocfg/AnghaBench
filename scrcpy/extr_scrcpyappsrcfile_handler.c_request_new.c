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
struct request {char const* file; int /*<<< orphan*/  action; } ;
typedef  int /*<<< orphan*/  file_handler_action_t ;

/* Variables and functions */
 struct request* SDL_malloc (int) ; 

__attribute__((used)) static struct request *
request_new(file_handler_action_t action, const char *file) {
    struct request *req = SDL_malloc(sizeof(*req));
    if (!req) {
        return NULL;
    }
    req->action = action;
    req->file = file;
    return req;
}