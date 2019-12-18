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
typedef  int /*<<< orphan*/  strm_string ;
typedef  TYPE_1__* node_string ;
struct TYPE_3__ {int /*<<< orphan*/  len; int /*<<< orphan*/  buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  strm_str_intern (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static strm_string
node_to_sym(node_string s)
{
  return strm_str_intern(s->buf, s->len);
}