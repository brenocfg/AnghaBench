#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {char* auth; } ;

/* Variables and functions */
 int /*<<< orphan*/  REDIS_CLI_AUTH_ENV ; 
 TYPE_1__ config ; 
 char* getenv (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void parseEnv() {
    /* Set auth from env, but do not overwrite CLI arguments if passed */
    char *auth = getenv(REDIS_CLI_AUTH_ENV);
    if (auth != NULL && config.auth == NULL) {
        config.auth = auth;
    }
}