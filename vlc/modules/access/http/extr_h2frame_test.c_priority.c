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
struct vlc_h2_frame {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  data (int) ; 
 struct vlc_h2_frame* localize (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resize (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  retype (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static struct vlc_h2_frame *priority(void)
{
    return localize(resize(retype(data(false), 0x2), 5));
}