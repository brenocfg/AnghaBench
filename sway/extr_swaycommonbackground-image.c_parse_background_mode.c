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
typedef  enum background_mode { ____Placeholder_background_mode } background_mode ;

/* Variables and functions */
 int BACKGROUND_MODE_CENTER ; 
 int BACKGROUND_MODE_FILL ; 
 int BACKGROUND_MODE_FIT ; 
 int BACKGROUND_MODE_INVALID ; 
 int BACKGROUND_MODE_SOLID_COLOR ; 
 int BACKGROUND_MODE_STRETCH ; 
 int BACKGROUND_MODE_TILE ; 
 int /*<<< orphan*/  SWAY_ERROR ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int /*<<< orphan*/  sway_log (int /*<<< orphan*/ ,char*,char const*) ; 

enum background_mode parse_background_mode(const char *mode) {
	if (strcmp(mode, "stretch") == 0) {
		return BACKGROUND_MODE_STRETCH;
	} else if (strcmp(mode, "fill") == 0) {
		return BACKGROUND_MODE_FILL;
	} else if (strcmp(mode, "fit") == 0) {
		return BACKGROUND_MODE_FIT;
	} else if (strcmp(mode, "center") == 0) {
		return BACKGROUND_MODE_CENTER;
	} else if (strcmp(mode, "tile") == 0) {
		return BACKGROUND_MODE_TILE;
	} else if (strcmp(mode, "solid_color") == 0) {
		return BACKGROUND_MODE_SOLID_COLOR;
	}
	sway_log(SWAY_ERROR, "Unsupported background mode: %s", mode);
	return BACKGROUND_MODE_INVALID;
}