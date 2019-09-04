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
struct optioninfo {char* sopt; char* lopt; } ;

/* Variables and functions */
 int /*<<< orphan*/  usageerr (char*,char*,char*,char*,char*,char*) ; 

__attribute__((used)) static void noninvert(const struct optioninfo *oip) {
  usageerr("option %s%s%s%s%s may not be inverted",
	   oip->sopt ? "-" : "", oip->sopt ? oip->sopt : "",
	   oip->lopt && oip->sopt ? " / " : "",
	   oip->lopt ? "--" : "", oip->lopt ? oip->lopt : "");
}