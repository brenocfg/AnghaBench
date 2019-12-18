#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_5__ {char** ppsz_keys; int /*<<< orphan*/ * global_map; int /*<<< orphan*/ * map; } ;
typedef  TYPE_1__ vlc_actions_t ;
typedef  int /*<<< orphan*/  name ;
typedef  int /*<<< orphan*/  libvlc_int_t ;
struct TYPE_7__ {TYPE_1__* actions; } ;
struct TYPE_6__ {char* psz; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int ACTIONS_COUNT ; 
 int /*<<< orphan*/  KEY_MOUSEWHEELDOWN ; 
 int /*<<< orphan*/  KEY_MOUSEWHEELLEFT ; 
 int /*<<< orphan*/  KEY_MOUSEWHEELRIGHT ; 
 int /*<<< orphan*/  KEY_MOUSEWHEELUP ; 
 int /*<<< orphan*/  MAXACTION ; 
 int VLC_ENOMEM ; 
 int /*<<< orphan*/ * VLC_OBJECT (int /*<<< orphan*/ *) ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  VLC_VAR_INTEGER ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  add_wheel_mapping (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_action (int /*<<< orphan*/ *,int /*<<< orphan*/ **,char*,int /*<<< orphan*/ ) ; 
 TYPE_4__* libvlc_priv (int /*<<< orphan*/ *) ; 
 TYPE_1__* malloc (int) ; 
 int /*<<< orphan*/  msg_Err (int /*<<< orphan*/ *,char*,char*,char*) ; 
 TYPE_2__* s_names2actions ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 
 scalar_t__ strcmp (char*,char*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  var_AddCallback (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  var_Create (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  var_InheritInteger (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  vlc_key_to_action ; 

int libvlc_InternalActionsInit (libvlc_int_t *libvlc)
{
    assert(libvlc != NULL);

    vlc_object_t *obj = VLC_OBJECT(libvlc);
    vlc_actions_t *as = malloc (sizeof (*as) + (1 + ACTIONS_COUNT)
                      * sizeof (*as->ppsz_keys));

    if (unlikely(as == NULL))
        return VLC_ENOMEM;
    as->map = NULL;
    as->global_map = NULL;

    var_Create (obj, "key-pressed", VLC_VAR_INTEGER);
    var_Create (obj, "global-key-pressed", VLC_VAR_INTEGER);
    var_Create (obj, "key-action", VLC_VAR_INTEGER);

    /* Initialize from configuration */
    for (size_t i = 0; i < ACTIONS_COUNT; i++)
    {
#ifndef NDEBUG
        if (i > 0
         && strcmp (s_names2actions[i-1].psz, s_names2actions[i].psz) >= 0)
        {
            msg_Err (libvlc, "key-%s and key-%s are not ordered properly",
                     s_names2actions[i-1].psz, s_names2actions[i].psz);
            abort ();
        }
#endif
        as->ppsz_keys[i] = s_names2actions[i].psz;

        char name[12 + MAXACTION];

        snprintf (name, sizeof (name), "global-key-%s", s_names2actions[i].psz);
        init_action (obj, &as->map, name + 7, s_names2actions[i].id);
        init_action (obj, &as->global_map, name, s_names2actions[i].id);
    }
    as->ppsz_keys[ACTIONS_COUNT] = NULL;

    /* Initialize mouse wheel events */
    add_wheel_mapping (&as->map, KEY_MOUSEWHEELRIGHT, KEY_MOUSEWHEELLEFT,
                         var_InheritInteger (obj, "hotkeys-x-wheel-mode"));
    add_wheel_mapping (&as->map, KEY_MOUSEWHEELUP, KEY_MOUSEWHEELDOWN,
                         var_InheritInteger (obj, "hotkeys-y-wheel-mode"));

    libvlc_priv(libvlc)->actions = as;
    var_AddCallback (obj, "key-pressed", vlc_key_to_action, &as->map);
    var_AddCallback (obj, "global-key-pressed", vlc_key_to_action,
                     &as->global_map);
    return VLC_SUCCESS;
}