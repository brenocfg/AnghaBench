#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_5__ {scalar_t__ type; } ;
typedef  TYPE_1__ json_value ;
typedef  int /*<<< orphan*/  json_settings ;

/* Variables and functions */
 scalar_t__ json_object ; 
 TYPE_1__* json_parse_ex (int /*<<< orphan*/ *,char const*,char*) ; 
 int /*<<< orphan*/  json_value_free (TYPE_1__*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msg_Warn (int /*<<< orphan*/ *,char*,...) ; 

__attribute__((used)) static inline
json_value * json_parse_document(vlc_object_t *p_obj, const char *psz_buffer)
{
    json_settings settings;
    char psz_error[128];
    memset (&settings, 0, sizeof (json_settings));
    json_value *root = json_parse_ex(&settings, psz_buffer, psz_error);
    if (root == NULL)
    {
        msg_Warn(p_obj, "Can't parse json data: %s", psz_error);
        goto error;
    }
    if (root->type != json_object)
    {
        msg_Warn(p_obj, "wrong json root node");
        goto error;
    }

    return root;

error:
    if (root) json_value_free(root);
    return NULL;
}