#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char const* text; } ;
typedef  TYPE_1__ getline_ctx ;
typedef  int /*<<< orphan*/  adns_state ;

/* Variables and functions */
 int /*<<< orphan*/  gl_text ; 
 int /*<<< orphan*/  readconfiggeneric (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,TYPE_1__) ; 

__attribute__((used)) static void readconfigtext(adns_state ads, const char *text, const char *showname) {
  getline_ctx gl_ctx;

  gl_ctx.text= text;
  readconfiggeneric(ads,showname,gl_text,gl_ctx);
}