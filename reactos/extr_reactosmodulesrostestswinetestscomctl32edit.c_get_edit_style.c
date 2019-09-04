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
typedef  int LONG ;
typedef  int /*<<< orphan*/  HWND ;

/* Variables and functions */
 int ES_AUTOHSCROLL ; 
 int ES_AUTOVSCROLL ; 
 int ES_COMBO ; 
 int ES_LEFT ; 
 int ES_LOWERCASE ; 
 int ES_MULTILINE ; 
 int ES_NOHIDESEL ; 
 int ES_NUMBER ; 
 int ES_PASSWORD ; 
 int ES_READONLY ; 
 int ES_UPPERCASE ; 
 int ES_WANTRETURN ; 
 int /*<<< orphan*/  GWL_STYLE ; 
 int GetWindowLongA (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static LONG get_edit_style (HWND hwnd)
{
    return GetWindowLongA( hwnd, GWL_STYLE ) & (
	ES_LEFT |
/* FIXME: not implemented
	ES_CENTER |
	ES_RIGHT |
	ES_OEMCONVERT |
*/
	ES_MULTILINE |
	ES_UPPERCASE |
	ES_LOWERCASE |
	ES_PASSWORD |
	ES_AUTOVSCROLL |
	ES_AUTOHSCROLL |
	ES_NOHIDESEL |
	ES_COMBO |
	ES_READONLY |
	ES_WANTRETURN |
	ES_NUMBER
	);
}