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
struct strm_genfunc {int /*<<< orphan*/  id; int /*<<< orphan*/ * state; int /*<<< orphan*/  type; } ;
typedef  int /*<<< orphan*/  strm_string ;
typedef  int /*<<< orphan*/  strm_state ;

/* Variables and functions */
 int /*<<< orphan*/  STRM_PTR_GENFUNC ; 
 struct strm_genfunc* malloc (int) ; 

__attribute__((used)) static struct strm_genfunc*
genfunc_new(strm_state* state, strm_string id)
{
  struct strm_genfunc *gf = malloc(sizeof(struct strm_genfunc));

  if (!gf) return NULL;
  gf->type = STRM_PTR_GENFUNC;
  gf->state = state;
  gf->id = id;
  return gf;
}