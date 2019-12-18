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

/* Variables and functions */
 int /*<<< orphan*/  VALID_DEPLOYMENT_CHARS ; 
 int /*<<< orphan*/  assert (char const*) ; 
 int in_charset (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool valid_deployment(const char *deployment) {
        assert(deployment);

        return in_charset(deployment, VALID_DEPLOYMENT_CHARS);
}