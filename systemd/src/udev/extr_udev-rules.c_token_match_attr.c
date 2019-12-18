#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vbuf ;
struct TYPE_11__ {int attr_subst_type; scalar_t__ attr_match_remove_trailing_whitespace; scalar_t__ data; } ;
typedef  TYPE_1__ sd_device ;
typedef  int /*<<< orphan*/  nbuf ;
typedef  TYPE_1__ UdevRuleToken ;
typedef  TYPE_1__ UdevEvent ;

/* Variables and functions */
#define  SUBST_TYPE_FORMAT 130 
#define  SUBST_TYPE_PLAIN 129 
#define  SUBST_TYPE_SUBSYS 128 
 int UTIL_NAME_SIZE ; 
 int /*<<< orphan*/  _fallthrough_ ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  assert_not_reached (char*) ; 
 int /*<<< orphan*/  delete_trailing_chars (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sd_device_get_sysattr_value (TYPE_1__*,char const*,char const**) ; 
 int /*<<< orphan*/  strscpy (char*,int,char const*) ; 
 int token_match_string (TYPE_1__*,char const*) ; 
 int /*<<< orphan*/  udev_event_apply_format (TYPE_1__*,char const*,char*,int,int) ; 
 int /*<<< orphan*/  util_resolve_subsys_kernel (char const*,char*,int,int) ; 

__attribute__((used)) static bool token_match_attr(UdevRuleToken *token, sd_device *dev, UdevEvent *event) {
        char nbuf[UTIL_NAME_SIZE], vbuf[UTIL_NAME_SIZE];
        const char *name, *value;

        assert(token);
        assert(dev);
        assert(event);

        name = (const char*) token->data;

        switch (token->attr_subst_type) {
        case SUBST_TYPE_FORMAT:
                (void) udev_event_apply_format(event, name, nbuf, sizeof(nbuf), false);
                name = nbuf;
                _fallthrough_;
        case SUBST_TYPE_PLAIN:
                if (sd_device_get_sysattr_value(dev, name, &value) < 0)
                        return false;
                break;
        case SUBST_TYPE_SUBSYS:
                if (util_resolve_subsys_kernel(name, vbuf, sizeof(vbuf), true) < 0)
                        return false;
                value = vbuf;
                break;
        default:
                assert_not_reached("Invalid attribute substitution type");
        }

        /* remove trailing whitespace, if not asked to match for it */
        if (token->attr_match_remove_trailing_whitespace) {
                if (value != vbuf) {
                        strscpy(vbuf, sizeof(vbuf), value);
                        value = vbuf;
                }

                delete_trailing_chars(vbuf, NULL);
        }

        return token_match_string(token, value);
}