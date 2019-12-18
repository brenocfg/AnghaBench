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
struct test_request {int dummy; } ;
struct info {int /*<<< orphan*/  wait; } ;
typedef  char WCHAR ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CreateEventW (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SetEvent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  close_request (struct test_request*,struct info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  open_async_request (int,struct test_request*,struct info*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  open_socket_request (int,struct test_request*,struct info*) ; 
 int /*<<< orphan*/  read_request_data (struct test_request*,struct info*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  server_read_data (char*) ; 
 int /*<<< orphan*/  server_send_reply (struct test_request*,struct info*,char*) ; 
 int /*<<< orphan*/  server_socket_done ; 
 int /*<<< orphan*/  trace (char*) ; 

__attribute__((used)) static void test_persistent_connection(int port)
{
    struct test_request req;
    struct info info;

    static const WCHAR testW[] = {'/','t','e','s','t',0};

    trace("Testing persistent connection...\n");

    info.wait = CreateEventW( NULL, FALSE, FALSE, NULL );

    open_socket_request( port, &req, &info );
    server_send_reply( &req, &info,
                       "HTTP/1.1 200 OK\r\n"
                       "Server: winetest\r\n"
                       "Connection: keep-alive\r\n"
                       "Content-Length: 1\r\n"
                       "\r\n"
                       "X" );
    read_request_data( &req, &info, "X", FALSE );
    close_request( &req, &info, FALSE );

    /* chunked connection test */
    open_async_request( port, &req, &info, testW, TRUE );
    server_read_data( "GET /test HTTP/1.1\r\n" );
    server_send_reply( &req, &info,
                       "HTTP/1.1 200 OK\r\n"
                       "Server: winetest\r\n"
                       "Transfer-Encoding: chunked\r\n"
                       "Connection: keep-alive\r\n"
                       "\r\n"
                       "9\r\n123456789\r\n"
                       "0\r\n\r\n" );
    read_request_data( &req, &info, "123456789", FALSE );
    close_request( &req, &info, FALSE );

    /* HTTP/1.1 connections are persistent by default, no additional header is needed */
    open_async_request( port, &req, &info, testW, TRUE );
    server_read_data( "GET /test HTTP/1.1\r\n" );
    server_send_reply( &req, &info,
                       "HTTP/1.1 200 OK\r\n"
                       "Server: winetest\r\n"
                       "Content-Length: 2\r\n"
                       "\r\n"
                       "xx" );
    read_request_data( &req, &info, "xx", FALSE );
    close_request( &req, &info, FALSE );

    open_async_request( port, &req, &info, testW, TRUE );
    server_read_data( "GET /test HTTP/1.1\r\n" );
    server_send_reply( &req, &info,
                       "HTTP/1.1 200 OK\r\n"
                       "Server: winetest\r\n"
                       "Content-Length: 2\r\n"
                       "Connection: close\r\n"
                       "\r\n"
                       "yy" );
    close_request( &req, &info, TRUE );

    SetEvent( server_socket_done );
    CloseHandle( info.wait );
}