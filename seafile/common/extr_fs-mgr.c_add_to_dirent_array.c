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
typedef  int /*<<< orphan*/  json_t ;
struct TYPE_3__ {int /*<<< orphan*/  size; int /*<<< orphan*/  modifier; int /*<<< orphan*/  mode; int /*<<< orphan*/  mtime; int /*<<< orphan*/  name; int /*<<< orphan*/  id; } ;
typedef  TYPE_1__ SeafDirent ;

/* Variables and functions */
 scalar_t__ S_ISREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  json_array_append_new (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * json_object () ; 
 int /*<<< orphan*/  json_object_set_int_member (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  json_object_set_string_member (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
add_to_dirent_array (json_t *array, SeafDirent *dirent)
{
    json_t *object;

    object = json_object ();
    json_object_set_int_member (object, "mode", dirent->mode);
    json_object_set_string_member (object, "id", dirent->id);
    json_object_set_string_member (object, "name", dirent->name);
    json_object_set_int_member (object, "mtime", dirent->mtime);
    if (S_ISREG(dirent->mode)) {
        json_object_set_string_member (object, "modifier", dirent->modifier);
        json_object_set_int_member (object, "size", dirent->size);
    }

    json_array_append_new (array, object);
}