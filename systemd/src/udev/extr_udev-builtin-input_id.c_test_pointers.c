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
typedef  int /*<<< orphan*/  sd_device ;

/* Variables and functions */
 int ABS_MT_POSITION_X ; 
 int ABS_MT_POSITION_Y ; 
 int ABS_MT_SLOT ; 
 int ABS_PRESSURE ; 
 int ABS_RX ; 
 int ABS_X ; 
 int ABS_Y ; 
 int ABS_Z ; 
 int BTN_DIGI ; 
 int BTN_DPAD_RIGHT ; 
 int BTN_DPAD_UP ; 
 int BTN_JOYSTICK ; 
 int BTN_MOUSE ; 
 int BTN_STYLUS ; 
 int BTN_TOOL_FINGER ; 
 int BTN_TOOL_PEN ; 
 int BTN_TOUCH ; 
 int BTN_TRIGGER_HAPPY1 ; 
 int BTN_TRIGGER_HAPPY40 ; 
 int EV_KEY ; 
 int EV_REL ; 
 int INPUT_PROP_ACCELEROMETER ; 
 int INPUT_PROP_DIRECT ; 
 int INPUT_PROP_POINTING_STICK ; 
 int REL_X ; 
 int REL_Y ; 
 int test_bit (int,unsigned long const*) ; 
 int /*<<< orphan*/  udev_builtin_add_property (int /*<<< orphan*/ *,int,char*,char*) ; 

__attribute__((used)) static bool test_pointers(sd_device *dev,
                          const unsigned long* bitmask_ev,
                          const unsigned long* bitmask_abs,
                          const unsigned long* bitmask_key,
                          const unsigned long* bitmask_rel,
                          const unsigned long* bitmask_props,
                          bool test) {
        int button, axis;
        bool has_abs_coordinates = false;
        bool has_rel_coordinates = false;
        bool has_mt_coordinates = false;
        bool has_joystick_axes_or_buttons = false;
        bool is_direct = false;
        bool has_touch = false;
        bool has_3d_coordinates = false;
        bool has_keys = false;
        bool stylus_or_pen = false;
        bool finger_but_no_pen = false;
        bool has_mouse_button = false;
        bool is_mouse = false;
        bool is_touchpad = false;
        bool is_touchscreen = false;
        bool is_tablet = false;
        bool is_joystick = false;
        bool is_accelerometer = false;
        bool is_pointing_stick= false;

        has_keys = test_bit(EV_KEY, bitmask_ev);
        has_abs_coordinates = test_bit(ABS_X, bitmask_abs) && test_bit(ABS_Y, bitmask_abs);
        has_3d_coordinates = has_abs_coordinates && test_bit(ABS_Z, bitmask_abs);
        is_accelerometer = test_bit(INPUT_PROP_ACCELEROMETER, bitmask_props);

        if (!has_keys && has_3d_coordinates)
                is_accelerometer = true;

        if (is_accelerometer) {
                udev_builtin_add_property(dev, test, "ID_INPUT_ACCELEROMETER", "1");
                return true;
        }

        is_pointing_stick = test_bit(INPUT_PROP_POINTING_STICK, bitmask_props);
        stylus_or_pen = test_bit(BTN_STYLUS, bitmask_key) || test_bit(BTN_TOOL_PEN, bitmask_key);
        finger_but_no_pen = test_bit(BTN_TOOL_FINGER, bitmask_key) && !test_bit(BTN_TOOL_PEN, bitmask_key);
        for (button = BTN_MOUSE; button < BTN_JOYSTICK && !has_mouse_button; button++)
                has_mouse_button = test_bit(button, bitmask_key);
        has_rel_coordinates = test_bit(EV_REL, bitmask_ev) && test_bit(REL_X, bitmask_rel) && test_bit(REL_Y, bitmask_rel);
        has_mt_coordinates = test_bit(ABS_MT_POSITION_X, bitmask_abs) && test_bit(ABS_MT_POSITION_Y, bitmask_abs);

        /* unset has_mt_coordinates if devices claims to have all abs axis */
        if (has_mt_coordinates && test_bit(ABS_MT_SLOT, bitmask_abs) && test_bit(ABS_MT_SLOT - 1, bitmask_abs))
                has_mt_coordinates = false;
        is_direct = test_bit(INPUT_PROP_DIRECT, bitmask_props);
        has_touch = test_bit(BTN_TOUCH, bitmask_key);

        /* joysticks don't necessarily have buttons; e. g.
         * rudders/pedals are joystick-like, but buttonless; they have
         * other fancy axes. Others have buttons only but no axes.
         *
         * The BTN_JOYSTICK range starts after the mouse range, so a mouse
         * with more than 16 buttons runs into the joystick range (e.g. Mad
         * Catz Mad Catz M.M.O.TE). Skip those.
         */
        if (!test_bit(BTN_JOYSTICK - 1, bitmask_key)) {
                for (button = BTN_JOYSTICK; button < BTN_DIGI && !has_joystick_axes_or_buttons; button++)
                        has_joystick_axes_or_buttons = test_bit(button, bitmask_key);
                for (button = BTN_TRIGGER_HAPPY1; button <= BTN_TRIGGER_HAPPY40 && !has_joystick_axes_or_buttons; button++)
                        has_joystick_axes_or_buttons = test_bit(button, bitmask_key);
                for (button = BTN_DPAD_UP; button <= BTN_DPAD_RIGHT && !has_joystick_axes_or_buttons; button++)
                        has_joystick_axes_or_buttons = test_bit(button, bitmask_key);
        }
        for (axis = ABS_RX; axis < ABS_PRESSURE && !has_joystick_axes_or_buttons; axis++)
                has_joystick_axes_or_buttons = test_bit(axis, bitmask_abs);

        if (has_abs_coordinates) {
                if (stylus_or_pen)
                        is_tablet = true;
                else if (finger_but_no_pen && !is_direct)
                        is_touchpad = true;
                else if (has_mouse_button)
                        /* This path is taken by VMware's USB mouse, which has
                         * absolute axes, but no touch/pressure button. */
                        is_mouse = true;
                else if (has_touch || is_direct)
                        is_touchscreen = true;
                else if (has_joystick_axes_or_buttons)
                        is_joystick = true;
        } else if (has_joystick_axes_or_buttons) {
                is_joystick = true;
        }

        if (has_mt_coordinates) {
                if (stylus_or_pen)
                        is_tablet = true;
                else if (finger_but_no_pen && !is_direct)
                        is_touchpad = true;
                else if (has_touch || is_direct)
                        is_touchscreen = true;
        }

        if (!is_tablet && !is_touchpad && !is_joystick &&
            has_mouse_button &&
            (has_rel_coordinates ||
            !has_abs_coordinates)) /* mouse buttons and no axis */
                is_mouse = true;

        if (is_pointing_stick)
                udev_builtin_add_property(dev, test, "ID_INPUT_POINTINGSTICK", "1");
        if (is_mouse)
                udev_builtin_add_property(dev, test, "ID_INPUT_MOUSE", "1");
        if (is_touchpad)
                udev_builtin_add_property(dev, test, "ID_INPUT_TOUCHPAD", "1");
        if (is_touchscreen)
                udev_builtin_add_property(dev, test, "ID_INPUT_TOUCHSCREEN", "1");
        if (is_joystick)
                udev_builtin_add_property(dev, test, "ID_INPUT_JOYSTICK", "1");
        if (is_tablet)
                udev_builtin_add_property(dev, test, "ID_INPUT_TABLET", "1");

        return is_tablet || is_mouse || is_touchpad || is_touchscreen || is_joystick || is_pointing_stick;
}