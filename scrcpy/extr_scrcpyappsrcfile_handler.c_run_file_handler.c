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
struct request {scalar_t__ action; int /*<<< orphan*/  file; } ;
struct file_handler {int /*<<< orphan*/  mutex; int /*<<< orphan*/  current_process; int /*<<< orphan*/  serial; int /*<<< orphan*/  queue; scalar_t__ stopped; int /*<<< orphan*/  event_cond; } ;
typedef  int /*<<< orphan*/  process_t ;

/* Variables and functions */
 scalar_t__ ACTION_INSTALL_APK ; 
 int /*<<< orphan*/  LOGE (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOGI (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PROCESS_NONE ; 
 int /*<<< orphan*/  SDL_assert (int) ; 
 int /*<<< orphan*/  cond_wait (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  install_apk (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ ) ; 
 scalar_t__ process_check_success (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  push_file (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  request_free (struct request*) ; 
 scalar_t__ request_queue_is_empty (int /*<<< orphan*/ *) ; 
 int request_queue_take (int /*<<< orphan*/ *,struct request**) ; 

__attribute__((used)) static int
run_file_handler(void *data) {
    struct file_handler *file_handler = data;

    for (;;) {
        mutex_lock(file_handler->mutex);
        file_handler->current_process = PROCESS_NONE;
        while (!file_handler->stopped
                && request_queue_is_empty(&file_handler->queue)) {
            cond_wait(file_handler->event_cond, file_handler->mutex);
        }
        if (file_handler->stopped) {
            // stop immediately, do not process further events
            mutex_unlock(file_handler->mutex);
            break;
        }
        struct request *req;
        bool non_empty = request_queue_take(&file_handler->queue, &req);
        SDL_assert(non_empty);

        process_t process;
        if (req->action == ACTION_INSTALL_APK) {
            LOGI("Installing %s...", req->file);
            process = install_apk(file_handler->serial, req->file);
        } else {
            LOGI("Pushing %s...", req->file);
            process = push_file(file_handler->serial, req->file);
        }
        file_handler->current_process = process;
        mutex_unlock(file_handler->mutex);

        if (req->action == ACTION_INSTALL_APK) {
            if (process_check_success(process, "adb install")) {
                LOGI("%s successfully installed", req->file);
            } else {
                LOGE("Failed to install %s", req->file);
            }
        } else {
            if (process_check_success(process, "adb push")) {
                LOGI("%s successfully pushed to /sdcard/", req->file);
            } else {
                LOGE("Failed to push %s to /sdcard/", req->file);
            }
        }

        request_free(req);
    }
    return 0;
}