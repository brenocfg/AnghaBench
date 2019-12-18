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
struct TYPE_3__ {int type; int previous_exists; int /*<<< orphan*/  path; } ;
typedef  TYPE_1__ PathSpec ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  F_OK ; 
#define  PATH_CHANGED 132 
#define  PATH_DIRECTORY_NOT_EMPTY 131 
#define  PATH_EXISTS 130 
#define  PATH_EXISTS_GLOB 129 
#define  PATH_MODIFIED 128 
 int /*<<< orphan*/  access (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int dir_is_empty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glob_exists (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool path_spec_check_good(PathSpec *s, bool initial) {
        bool good = false;

        switch (s->type) {

        case PATH_EXISTS:
                good = access(s->path, F_OK) >= 0;
                break;

        case PATH_EXISTS_GLOB:
                good = glob_exists(s->path) > 0;
                break;

        case PATH_DIRECTORY_NOT_EMPTY: {
                int k;

                k = dir_is_empty(s->path);
                good = !(k == -ENOENT || k > 0);
                break;
        }

        case PATH_CHANGED:
        case PATH_MODIFIED: {
                bool b;

                b = access(s->path, F_OK) >= 0;
                good = !initial && b != s->previous_exists;
                s->previous_exists = b;
                break;
        }

        default:
                ;
        }

        return good;
}