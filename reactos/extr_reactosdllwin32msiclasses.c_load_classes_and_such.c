#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT ;
struct TYPE_8__ {int /*<<< orphan*/  progids; int /*<<< orphan*/  extensions; int /*<<< orphan*/  mimes; int /*<<< orphan*/  classes; } ;
typedef  TYPE_1__ MSIPACKAGE ;

/* Variables and functions */
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 scalar_t__ load_all_classes (TYPE_1__*) ; 
 scalar_t__ load_all_extensions (TYPE_1__*) ; 
 scalar_t__ load_all_mimes (TYPE_1__*) ; 
 scalar_t__ load_all_progids (TYPE_1__*) ; 
 scalar_t__ load_all_verbs (TYPE_1__*) ; 

__attribute__((used)) static UINT load_classes_and_such( MSIPACKAGE *package )
{
    UINT r;

    TRACE("Loading all the class info and related tables\n");

    /* check if already loaded */
    if (!list_empty( &package->classes ) ||
        !list_empty( &package->mimes ) ||
        !list_empty( &package->extensions ) ||
        !list_empty( &package->progids )) return ERROR_SUCCESS;

    r = load_all_classes( package );
    if (r != ERROR_SUCCESS) return r;

    r = load_all_extensions( package );
    if (r != ERROR_SUCCESS) return r;

    r = load_all_progids( package );
    if (r != ERROR_SUCCESS) return r;

    /* these loads must come after the other loads */
    r = load_all_verbs( package );
    if (r != ERROR_SUCCESS) return r;

    return load_all_mimes( package );
}