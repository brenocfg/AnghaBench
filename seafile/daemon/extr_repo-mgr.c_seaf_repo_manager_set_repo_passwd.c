#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  enc_iv; int /*<<< orphan*/  enc_key; int /*<<< orphan*/  salt; int /*<<< orphan*/  random_key; int /*<<< orphan*/  enc_version; } ;
struct TYPE_9__ {TYPE_1__* priv; } ;
struct TYPE_8__ {int /*<<< orphan*/  db_lock; } ;
typedef  TYPE_2__ SeafRepoManager ;
typedef  TYPE_3__ SeafRepo ;

/* Variables and functions */
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int save_repo_enc_info (TYPE_2__*,TYPE_3__*) ; 
 scalar_t__ seafile_decrypt_repo_enc_key (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int 
seaf_repo_manager_set_repo_passwd (SeafRepoManager *manager,
                                   SeafRepo *repo,
                                   const char *passwd)
{
    int ret;

    if (seafile_decrypt_repo_enc_key (repo->enc_version, passwd, repo->random_key,
                                      repo->salt,
                                      repo->enc_key, repo->enc_iv) < 0)
        return -1;

    pthread_mutex_lock (&manager->priv->db_lock);

    ret = save_repo_enc_info (manager, repo);

    pthread_mutex_unlock (&manager->priv->db_lock);

    return ret;
}