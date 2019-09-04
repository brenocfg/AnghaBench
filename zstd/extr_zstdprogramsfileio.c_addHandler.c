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
 int /*<<< orphan*/  INThandler ; 
 int /*<<< orphan*/  SIGINT ; 
 scalar_t__ UTIL_isRegularFile (char const*) ; 
 char const* g_artefact ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void addHandler(char const* dstFileName)
{
    if (UTIL_isRegularFile(dstFileName)) {
        g_artefact = dstFileName;
        signal(SIGINT, INThandler);
    } else {
        g_artefact = NULL;
    }
}