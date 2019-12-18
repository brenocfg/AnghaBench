#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_9__ {int /*<<< orphan*/  dht; } ;

/* Variables and functions */
 int FIRST_FLAG ; 
 int MAP_ANONYMOUS ; 
 int MAP_SHARED ; 
 int /*<<< orphan*/  MS_SYNC ; 
 int /*<<< orphan*/  Messenger_save (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int PROT_READ ; 
 int PROT_WRITE ; 
 int SECOND_FLAG ; 
 int /*<<< orphan*/  SIGKILL ; 
 scalar_t__ atexit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  c_sleep (int) ; 
 int /*<<< orphan*/  child_got_request ; 
 int /*<<< orphan*/  child_got_statuschange ; 
 int /*<<< orphan*/  child_id ; 
 int /*<<< orphan*/  child_pid ; 
 int /*<<< orphan*/  cleanup ; 
 int /*<<< orphan*/  cleanupMessenger (TYPE_1__*) ; 
 int /*<<< orphan*/  crypto_box_PUBLICKEYBYTES ; 
 int /*<<< orphan*/  do_tox (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fork () ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ ) ; 
 TYPE_1__* initMessenger () ; 
 int /*<<< orphan*/  kill (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* m ; 
 int /*<<< orphan*/  m_callback_friendmessage (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  m_callback_friendrequest (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  m_callback_statusmessage (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  m_sendmessage (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmap (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parent_confirm_message ; 
 int /*<<< orphan*/  parent_confirm_status ; 
 int parent_friend_request (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parent_id ; 
 int parent_wait_for_message (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  puts (char*) ; 
 int request_flags ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int /*<<< orphan*/  wait (int /*<<< orphan*/ *) ; 

int main(int argc, char *argv[])
{
    puts("=========== FRIENDS_TEST ===========");

    /* set up the global memory */
    parent_id = mmap(NULL, crypto_box_PUBLICKEYBYTES, PROT_READ | PROT_WRITE,
                     MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    child_id = mmap(NULL, crypto_box_PUBLICKEYBYTES, PROT_READ | PROT_WRITE,
                    MAP_SHARED | MAP_ANONYMOUS, -1, 0);

    fputs("friends_test: Starting test...\n", stdout);

    if ((child_pid = fork()) == 0) {
        /* child */
        int i = 0;
        char *message = "Y-yes Mr. Watson?";

        m = initMessenger();

        Messenger_save(m, child_id);
        msync(child_id, crypto_box_PUBLICKEYBYTES, MS_SYNC);

        m_callback_friendrequest(m, child_got_request, NULL);
        m_callback_statusmessage(m, child_got_statuschange, NULL);

        /* wait on the friend request */
        while (!(request_flags & FIRST_FLAG))
            do_tox(m->dht);

        /* wait for the status change */
        while (!(request_flags & SECOND_FLAG))
            do_tox(m->dht);

        for (i = 0; i < 6; i++) {
            /* send the message six times, just to be sure */
            m_sendmessage(m, 0, (uint8_t *)message, strlen(message));
            do_tox(m->dht);
        }

        cleanupMessenger(m);

        return 0;
    }

    /* parent */
    if (atexit(cleanup) != 0) {
        fputs("friends_test: atexit() failed!\nFailing build...\n", stderr);
        kill(child_pid, SIGKILL);
        return -1;
    }

    m = initMessenger();

    msync(parent_id, crypto_box_PUBLICKEYBYTES, MS_SYNC);
    m_callback_statusmessage(m, parent_confirm_status, NULL);
    m_callback_friendmessage(m, parent_confirm_message, NULL);

    /* hacky way to give the child time to set up */
    c_sleep(50);

    Messenger_save(m, parent_id);

    if (parent_friend_request(m->dht) == -1)
        return -1;

    if (parent_wait_for_message(m->dht) == -1)
        return -1;

    wait(NULL);
    fputs("friends_test: Build passed!\n", stdout);
    return 0;
}