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

/* Variables and functions */
#define  EACCES 167 
#define  EADDRINUSE 166 
#define  EADDRNOTAVAIL 165 
#define  EAFNOSUPPORT 164 
#define  EALREADY 163 
#define  EBADF 162 
#define  ECONNABORTED 161 
#define  ECONNREFUSED 160 
#define  ECONNRESET 159 
#define  EDESTADDRREQ 158 
#define  EFAULT 157 
#define  EHOSTDOWN 156 
#define  EHOSTUNREACH 155 
#define  EINPROGRESS 154 
#define  EINTR 153 
#define  EINVAL 152 
#define  EISCONN 151 
#define  ELOOP 150 
#define  EMFILE 149 
#define  EMSGSIZE 148 
#define  ENAMETOOLONG 147 
#define  ENETDOWN 146 
#define  ENETRESET 145 
#define  ENETUNREACH 144 
#define  ENOBUFS 143 
#define  ENOPROTOOPT 142 
#define  ENOTCONN 141 
#define  ENOTEMPTY 140 
#define  ENOTSOCK 139 
#define  EOPNOTSUPP 138 
#define  EPERM 137 
#define  EPFNOSUPPORT 136 
#define  EPIPE 135 
#define  EPROTONOSUPPORT 134 
#define  EPROTOTYPE 133 
#define  ESHUTDOWN 132 
#define  ESOCKTNOSUPPORT 131 
#define  ETIMEDOUT 130 
#define  ETOOMANYREFS 129 
#define  EWOULDBLOCK 128 
 int WSAEACCES ; 
 int WSAEADDRINUSE ; 
 int WSAEADDRNOTAVAIL ; 
 int WSAEAFNOSUPPORT ; 
 int WSAEALREADY ; 
 int WSAEBADF ; 
 int WSAECONNABORTED ; 
 int WSAECONNREFUSED ; 
 int WSAECONNRESET ; 
 int WSAEDESTADDRREQ ; 
 int WSAEFAULT ; 
 int WSAEHOSTDOWN ; 
 int WSAEHOSTUNREACH ; 
 int WSAEINPROGRESS ; 
 int WSAEINTR ; 
 int WSAEINVAL ; 
 int WSAEISCONN ; 
 int WSAELOOP ; 
 int WSAEMFILE ; 
 int WSAEMSGSIZE ; 
 int WSAENAMETOOLONG ; 
 int WSAENETDOWN ; 
 int WSAENETRESET ; 
 int WSAENETUNREACH ; 
 int WSAENOBUFS ; 
 int WSAENOPROTOOPT ; 
 int WSAENOTCONN ; 
 int WSAENOTEMPTY ; 
 int WSAENOTSOCK ; 
 int WSAEOPNOTSUPP ; 
 int WSAEPFNOSUPPORT ; 
 int WSAEPROTONOSUPPORT ; 
 int WSAEPROTOTYPE ; 
 int WSAESHUTDOWN ; 
 int WSAESOCKTNOSUPPORT ; 
 int WSAETIMEDOUT ; 
 int WSAETOOMANYREFS ; 
 int WSAEWOULDBLOCK ; 
 int errno ; 
 int /*<<< orphan*/  perror (char*) ; 

__attribute__((used)) static int sock_get_error( int err )
{
#if !defined(__MINGW32__) && !defined (_MSC_VER)
    switch (err)
    {
        case EINTR:             return WSAEINTR;
        case EBADF:             return WSAEBADF;
        case EPERM:
        case EACCES:            return WSAEACCES;
        case EFAULT:            return WSAEFAULT;
        case EINVAL:            return WSAEINVAL;
        case EMFILE:            return WSAEMFILE;
        case EWOULDBLOCK:       return WSAEWOULDBLOCK;
        case EINPROGRESS:       return WSAEINPROGRESS;
        case EALREADY:          return WSAEALREADY;
        case ENOTSOCK:          return WSAENOTSOCK;
        case EDESTADDRREQ:      return WSAEDESTADDRREQ;
        case EMSGSIZE:          return WSAEMSGSIZE;
        case EPROTOTYPE:        return WSAEPROTOTYPE;
        case ENOPROTOOPT:       return WSAENOPROTOOPT;
        case EPROTONOSUPPORT:   return WSAEPROTONOSUPPORT;
        case ESOCKTNOSUPPORT:   return WSAESOCKTNOSUPPORT;
        case EOPNOTSUPP:        return WSAEOPNOTSUPP;
        case EPFNOSUPPORT:      return WSAEPFNOSUPPORT;
        case EAFNOSUPPORT:      return WSAEAFNOSUPPORT;
        case EADDRINUSE:        return WSAEADDRINUSE;
        case EADDRNOTAVAIL:     return WSAEADDRNOTAVAIL;
        case ENETDOWN:          return WSAENETDOWN;
        case ENETUNREACH:       return WSAENETUNREACH;
        case ENETRESET:         return WSAENETRESET;
        case ECONNABORTED:      return WSAECONNABORTED;
        case EPIPE:
        case ECONNRESET:        return WSAECONNRESET;
        case ENOBUFS:           return WSAENOBUFS;
        case EISCONN:           return WSAEISCONN;
        case ENOTCONN:          return WSAENOTCONN;
        case ESHUTDOWN:         return WSAESHUTDOWN;
        case ETOOMANYREFS:      return WSAETOOMANYREFS;
        case ETIMEDOUT:         return WSAETIMEDOUT;
        case ECONNREFUSED:      return WSAECONNREFUSED;
        case ELOOP:             return WSAELOOP;
        case ENAMETOOLONG:      return WSAENAMETOOLONG;
        case EHOSTDOWN:         return WSAEHOSTDOWN;
        case EHOSTUNREACH:      return WSAEHOSTUNREACH;
        case ENOTEMPTY:         return WSAENOTEMPTY;
#ifdef EPROCLIM
        case EPROCLIM:          return WSAEPROCLIM;
#endif
#ifdef EUSERS
        case EUSERS:            return WSAEUSERS;
#endif
#ifdef EDQUOT
        case EDQUOT:            return WSAEDQUOT;
#endif
#ifdef ESTALE
        case ESTALE:            return WSAESTALE;
#endif
#ifdef EREMOTE
        case EREMOTE:           return WSAEREMOTE;
#endif
    default: errno = err; perror( "sock_set_error" ); return WSAEFAULT;
    }
#endif
    return err;
}