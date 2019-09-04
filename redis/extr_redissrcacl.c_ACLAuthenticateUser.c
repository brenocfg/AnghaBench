#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  ptr; } ;
typedef  TYPE_1__ robj ;
struct TYPE_9__ {int authenticated; int /*<<< orphan*/  user; } ;
typedef  TYPE_2__ client ;

/* Variables and functions */
 scalar_t__ ACLCheckUserCredentials (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  ACLGetUserByName (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int C_ERR ; 
 scalar_t__ C_OK ; 
 int /*<<< orphan*/  sdslen (int /*<<< orphan*/ ) ; 

int ACLAuthenticateUser(client *c, robj *username, robj *password) {
    if (ACLCheckUserCredentials(username,password) == C_OK) {
        c->authenticated = 1;
        c->user = ACLGetUserByName(username->ptr,sdslen(username->ptr));
        return C_OK;
    } else {
        return C_ERR;
    }
}