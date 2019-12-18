#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ answer; } ;
typedef  TYPE_1__ Uploader ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  log_debug (char*,size_t,int,char*) ; 
 int /*<<< orphan*/  log_warning (char*,size_t) ; 
 scalar_t__ strndup (char*,size_t) ; 

__attribute__((used)) static size_t output_callback(char *buf,
                              size_t size,
                              size_t nmemb,
                              void *userp) {
        Uploader *u = userp;

        assert(u);

        log_debug("The server answers (%zu bytes): %.*s",
                  size*nmemb, (int)(size*nmemb), buf);

        if (nmemb && !u->answer) {
                u->answer = strndup(buf, size*nmemb);
                if (!u->answer)
                        log_warning("Failed to store server answer (%zu bytes): out of memory", size*nmemb);
        }

        return size * nmemb;
}