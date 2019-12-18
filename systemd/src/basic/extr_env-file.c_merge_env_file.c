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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  merge_env_file_push ; 
 int parse_env_file_internal (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,char***,int /*<<< orphan*/ *) ; 

int merge_env_file(
                char ***env,
                FILE *f,
                const char *fname) {

        /* NOTE: this function supports braceful and braceless variable expansions,
         * plus "extended" substitutions, unlike other exported parsing functions.
         */

        return parse_env_file_internal(f, fname, merge_env_file_push, env, NULL);
}