#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8 ;
typedef  int /*<<< orphan*/  uint16 ;
struct TYPE_8__ {int /*<<< orphan*/  modifiers; int /*<<< orphan*/  scancode; } ;
typedef  TYPE_2__ key_translation ;
struct TYPE_7__ {TYPE_2__** keymap; } ;
struct TYPE_9__ {TYPE_1__ xkeymap; } ;
typedef  TYPE_3__ RDPCLIENT ;
typedef  size_t KeySym ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_KBD (char*) ; 
 size_t KEYMAP_MASK ; 
 size_t NoSymbol ; 
 size_t XStringToKeysym (char*) ; 
 int /*<<< orphan*/  free_key_translation (TYPE_2__*) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ xmalloc (int) ; 

__attribute__((used)) static void
add_to_keymap(RDPCLIENT * This, char *keyname, uint8 scancode, uint16 modifiers, char *mapname)
{
	KeySym keysym;
	key_translation *tr;

	keysym = XStringToKeysym(keyname);
	if (keysym == NoSymbol)
	{
		DEBUG_KBD(("Bad keysym \"%s\" in keymap %s (ignoring)\n", keyname, mapname));
		return;
	}

	DEBUG_KBD(("Adding translation, keysym=0x%x, scancode=0x%x, "
		   "modifiers=0x%x\n", (unsigned int) keysym, scancode, modifiers));

	tr = (key_translation *) xmalloc(sizeof(key_translation));
	memset(tr, 0, sizeof(key_translation));
	tr->scancode = scancode;
	tr->modifiers = modifiers;
	free_key_translation(This->xkeymap.keymap[keysym & KEYMAP_MASK]);
	This->xkeymap.keymap[keysym & KEYMAP_MASK] = tr;

	return;
}