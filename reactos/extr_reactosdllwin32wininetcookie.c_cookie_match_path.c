#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ len; int /*<<< orphan*/  str; } ;
typedef  TYPE_2__ substr_t ;
struct TYPE_6__ {scalar_t__ len; int /*<<< orphan*/  str; } ;
struct TYPE_8__ {TYPE_1__ path; } ;
typedef  TYPE_3__ cookie_container_t ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  strncmpiW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static BOOL cookie_match_path(cookie_container_t *container, substr_t path)
{
    return path.len >= container->path.len && !strncmpiW(container->path.str, path.str, container->path.len);
}