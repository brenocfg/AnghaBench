#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  key; } ;
typedef  TYPE_1__ symdir_t ;
struct stat {int /*<<< orphan*/  st_ino; int /*<<< orphan*/  st_dev; } ;
struct TYPE_10__ {int /*<<< orphan*/  ino; int /*<<< orphan*/  dev; } ;
typedef  TYPE_2__ dirkey_t ;

/* Variables and functions */
 int /*<<< orphan*/  HASH_ADD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,TYPE_1__*) ; 
 int /*<<< orphan*/  HASH_FIND (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*,int,TYPE_1__*) ; 
 int SYMLOOP_ERROR ; 
 int SYMLOOP_LOOP ; 
 int SYMLOOP_OK ; 
 scalar_t__ ag_malloc (int) ; 
 int /*<<< orphan*/  hh ; 
 int /*<<< orphan*/  key ; 
 int /*<<< orphan*/  log_err (char*,char const*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,TYPE_2__*,int) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int stat (char const*,struct stat*) ; 
 int /*<<< orphan*/  symhash ; 

__attribute__((used)) static int check_symloop_enter(const char *path, dirkey_t *outkey) {
#ifdef _WIN32
    return SYMLOOP_OK;
#else
    struct stat buf;
    symdir_t *item_found = NULL;
    symdir_t *new_item = NULL;

    memset(outkey, 0, sizeof(dirkey_t));
    outkey->dev = 0;
    outkey->ino = 0;

    int res = stat(path, &buf);
    if (res != 0) {
        log_err("Error stat()ing: %s", path);
        return SYMLOOP_ERROR;
    }

    outkey->dev = buf.st_dev;
    outkey->ino = buf.st_ino;

    HASH_FIND(hh, symhash, outkey, sizeof(dirkey_t), item_found);
    if (item_found) {
        return SYMLOOP_LOOP;
    }

    new_item = (symdir_t *)ag_malloc(sizeof(symdir_t));
    memcpy(&new_item->key, outkey, sizeof(dirkey_t));
    HASH_ADD(hh, symhash, key, sizeof(dirkey_t), new_item);
    return SYMLOOP_OK;
#endif
}