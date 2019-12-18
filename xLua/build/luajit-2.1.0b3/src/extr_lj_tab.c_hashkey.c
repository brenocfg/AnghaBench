#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  gcr; } ;
typedef  TYPE_1__ cTValue ;
typedef  int /*<<< orphan*/  Node ;
typedef  int /*<<< orphan*/  GCtab ;

/* Variables and functions */
 int /*<<< orphan*/  boolV (TYPE_1__*) ; 
 int /*<<< orphan*/ * hashgcref (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * hashmask (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * hashnum (int /*<<< orphan*/  const*,TYPE_1__*) ; 
 int /*<<< orphan*/ * hashstr (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_assert (int) ; 
 int /*<<< orphan*/  strV (TYPE_1__*) ; 
 scalar_t__ tvisbool (TYPE_1__*) ; 
 int /*<<< orphan*/  tvisint (TYPE_1__*) ; 
 scalar_t__ tvisnum (TYPE_1__*) ; 
 scalar_t__ tvisstr (TYPE_1__*) ; 

__attribute__((used)) static Node *hashkey(const GCtab *t, cTValue *key)
{
  lua_assert(!tvisint(key));
  if (tvisstr(key))
    return hashstr(t, strV(key));
  else if (tvisnum(key))
    return hashnum(t, key);
  else if (tvisbool(key))
    return hashmask(t, boolV(key));
  else
    return hashgcref(t, key->gcr);
  /* Only hash 32 bits of lightuserdata on a 64 bit CPU. Good enough? */
}