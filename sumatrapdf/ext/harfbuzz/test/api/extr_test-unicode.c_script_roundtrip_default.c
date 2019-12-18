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
typedef  int /*<<< orphan*/  hb_script_t ;

/* Variables and functions */
 int /*<<< orphan*/  hb_script_from_iso15924_tag (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hb_script_to_iso15924_tag (int /*<<< orphan*/ ) ; 

__attribute__((used)) static hb_script_t
script_roundtrip_default (hb_script_t script)
{
  return hb_script_from_iso15924_tag (hb_script_to_iso15924_tag (script));
}