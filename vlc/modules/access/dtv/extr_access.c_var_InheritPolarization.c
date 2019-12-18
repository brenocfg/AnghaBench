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
typedef  int /*<<< orphan*/  vlc_object_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  msg_Warn (int /*<<< orphan*/ *,char*,unsigned int,char) ; 
 scalar_t__ unlikely (int) ; 
 unsigned int var_InheritInteger (int /*<<< orphan*/ *,char*) ; 
 char* var_InheritString (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static char var_InheritPolarization (vlc_object_t *obj)
{
    char pol;
    char *polstr = var_InheritString (obj, "dvb-polarization");
    if (polstr != NULL)
    {
        pol = *polstr;
        free (polstr);
        if (unlikely(pol >= 'a' && pol <= 'z'))
            pol -= 'a' - 'A';
        return pol;
    }

    /* Backward compatibility with VLC for Linux < 1.2 */
    unsigned voltage = var_InheritInteger (obj, "dvb-voltage");
    switch (voltage)
    {
        case 13:  pol = 'V'; break;
        case 18:  pol = 'H'; break;
        default:  return 0;
    }

    msg_Warn (obj, "\"voltage=%u\" option is obsolete. "
                   "Use \"polarization=%c\" instead.", voltage, pol);
    return pol;
}