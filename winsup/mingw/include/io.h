/* 
 * io.h
 *
 * System level I/O functions and types.
 *
 * This file is part of the Mingw32 package.
 *
 * Contributors:
 *  Created by Colin Peters <colin@bird.fu.is.saga-u.ac.jp>
 *
 *  THIS SOFTWARE IS NOT COPYRIGHTED
 *
 *  This source code is offered for use in the public domain. You may
 *  use, modify or distribute it freely.
 *
 *  This code is distributed in the hope that it will be useful but
 *  WITHOUT ANY WARRANTY. ALL WARRANTIES, EXPRESS OR IMPLIED ARE HEREBY
 *  DISCLAIMED. This includes but is not limited to warranties of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 * $Revision$
 * $Author$
 * $Date$
 *
 */

#ifndef	__STRICT_ANSI__

#ifndef	_IO_H_
#define	_IO_H_

/* All the headers include this file. */
#include <_mingw.h>
#define __need_wchar_t
#ifndef RC_INVOKED
#include <stddef.h>
#endif /* Not RC_INVOKED */

/*
 * Attributes of files as returned by _findfirst et al.
 */
#define	_A_NORMAL	0x00000000
#define	_A_RDONLY	0x00000001
#define	_A_HIDDEN	0x00000002
#define	_A_SYSTEM	0x00000004
#define	_A_VOLID	0x00000008
#define	_A_SUBDIR	0x00000010
#define	_A_ARCH		0x00000020

/* TODO: Maximum number of open handles has not been tested, I just set
 * it the same as FOPEN_MAX. */
#define	HANDLE_MAX	20


/* Some defines for _access nAccessMode (MS doesn't define them, but
 * it doesn't seem to hurt to add them). */
#define	F_OK	0	/* Check for file existence */
#define	X_OK	1	/* Check for execute permission. */
#define	W_OK	2	/* Check for write permission */
#define	R_OK	4	/* Check for read permission */


#ifndef RC_INVOKED

#ifndef _TIME_T_DEFINED
__BEGIN_CSTD_NAMESPACE
typedef long time_t;
__END_CSTD_NAMESPACE
#define _TIME_T_DEFINED
#endif

__BEGIN_CGLOBAL_NAMESPACE

#ifndef	_FSIZE_T_DEFINED
typedef	unsigned long	_fsize_t;
#define _FSIZE_T_DEFINED
#endif

/*
 * The following structure is filled in by _findfirst or _findnext when
 * they succeed in finding a match.
 */
struct _finddata_t
{
	unsigned	attrib;		/* Attributes, see constants above. */
	__CSTD time_t	time_create;
	__CSTD time_t	time_access;	/* always midnight local time */
	__CSTD time_t	time_write;
	_fsize_t	size;
	char		name[260];	/* may include spaces. */
};

struct _finddatai64_t {
    unsigned		attrib;
    __CSTD time_t	time_create;
    __CSTD time_t	time_access;
    __CSTD time_t	time_write;
    __int64		size;
    char        name[260];
};

#ifndef _WFINDDATA_T_DEFINED
struct _wfinddata_t {
    	unsigned	attrib;
    	__CSTD time_t	time_create;	/* -1 for FAT file systems */
    	__CSTD time_t	time_access;	/* -1 for FAT file systems */
    	__CSTD time_t	time_write;
    	_fsize_t	size;
    	wchar_t		name[260];	/* may include spaces. */
};
struct _wfinddatai64_t {
    unsigned		attrib;
    __CSTD time_t	time_create;
    __CSTD time_t	time_access;
    __CSTD time_t	time_write;
    __int64		size;
    wchar_t		name[260];
};

#define _WFINDDATA_T_DEFINED
#endif

/*
 * Functions for searching for files. _findfirst returns -1 if no match
 * is found. Otherwise it returns a handle to be used in _findnext and
 * _findclose calls. _findnext also returns -1 if no match could be found,
 * and 0 if a match was found. Call _findclose when you are finished.
 */
_CRTIMP int __cdecl _findfirst (const char*, struct _finddata_t*);
_CRTIMP int __cdecl _findnext (int, struct _finddata_t*);
_CRTIMP int __cdecl _findclose (int);

_CRTIMP int __cdecl _chdir (const char*);
_CRTIMP char* __cdecl _getcwd (char*, int);
_CRTIMP int __cdecl _mkdir (const char*);
_CRTIMP char* __cdecl _mktemp (char*);
_CRTIMP int __cdecl _rmdir (const char*);
_CRTIMP int __cdecl _chmod (const char*, int);

#ifdef __MSVCRT__
_CRTIMP __int64 __cdecl _filelengthi64(int);
_CRTIMP long __cdecl _findfirsti64(const char*, struct _finddatai64_t*);
_CRTIMP int __cdecl _findnexti64(long, struct _finddatai64_t*);
_CRTIMP __int64 __cdecl _lseeki64(int, __int64, int);
_CRTIMP __int64 __cdecl _telli64(int);
#endif /* __MSVCRT__ */

#ifndef _NO_OLDNAMES

#ifndef _UWIN
_CRTIMP int __cdecl chdir (const char*);
_CRTIMP char* __cdecl getcwd (char*, int);
_CRTIMP int __cdecl mkdir (const char*);
_CRTIMP char* __cdecl mktemp (char*);
_CRTIMP int __cdecl rmdir (const char*);
_CRTIMP int __cdecl chmod (const char*, int);
#endif /* _UWIN */

#endif /* Not _NO_OLDNAMES */

_CRTIMP int __cdecl 	_access (const char*, int);
_CRTIMP int __cdecl 	_chsize (int, long);
_CRTIMP int __cdecl 	_close (int);
_CRTIMP int __cdecl 	_commit(int);

/* NOTE: The only significant bit in unPermissions appears to be bit 7 (0x80),
 *       the "owner write permission" bit (on FAT). */
_CRTIMP int __cdecl 	_creat (const char*, int);

_CRTIMP int __cdecl 	_dup (int);
_CRTIMP int __cdecl 	_dup2 (int, int);
_CRTIMP long _cdecl 	_filelength (int);
_CRTIMP long _cdecl 	_get_osfhandle (int);
_CRTIMP int __cdecl 	_isatty (int);

/* In a very odd turn of events this function is excluded from those
 * files which define _STREAM_COMPAT. This is required in order to
 * build GNU libio because of a conflict with _eof in streambuf.h
 * line 107. Actually I might just be able to change the name of
 * the enum member in streambuf.h... we'll see. TODO */
#ifndef	_STREAM_COMPAT
_CRTIMP int __cdecl 	_eof (int);
#endif

/* LK_... locking commands defined in sys/locking.h. */
_CRTIMP int __cdecl 	_locking (int, int, long);

_CRTIMP long _cdecl 	_lseek (int, long, int);

/* Optional third argument is unsigned unPermissions. */
_CRTIMP int __cdecl 	_open (const char*, int, ...);

_CRTIMP int __cdecl 	_open_osfhandle (long, int);
_CRTIMP int __cdecl 	_pipe (int *, unsigned int, int);
_CRTIMP int __cdecl 	_read (int, void*, unsigned int);
_CRTIMP int __cdecl 	_setmode (int, int);

/* SH_... flags for nShFlags defined in share.h
 * Optional fourth argument is unsigned unPermissions */
_CRTIMP int __cdecl 	_sopen (const char*, int, int, ...);

_CRTIMP long _cdecl 	_tell (int);
/* Should umask be in sys/stat.h and/or sys/types.h instead? */
_CRTIMP int __cdecl 	_umask (int);
_CRTIMP int __cdecl 	_unlink (const char*);
_CRTIMP int __cdecl 	_write (int, const void*, unsigned int);

#ifndef	_NO_OLDNAMES
/*
 * Non-underscored versions of non-ANSI functions to improve portability.
 * These functions live in libmoldname.a.
 */

#ifndef _UWIN
_CRTIMP int __cdecl 	access (const char*, int);
_CRTIMP int __cdecl 	chsize (int, long );
_CRTIMP int __cdecl 	close (int);
_CRTIMP int __cdecl 	creat (const char*, int);
_CRTIMP int __cdecl 	dup (int);
_CRTIMP int __cdecl 	dup2 (int, int);
_CRTIMP int __cdecl 	eof (int);
_CRTIMP long _cdecl 	filelength (int);
_CRTIMP int __cdecl 	isatty (int);
_CRTIMP long _cdecl 	lseek (int, long, int);
_CRTIMP int __cdecl 	open (const char*, int, ...);
_CRTIMP int __cdecl 	read (int, void*, unsigned int);
_CRTIMP int __cdecl 	setmode (int, int);
_CRTIMP int __cdecl 	sopen (const char*, int, int, ...);
_CRTIMP long _cdecl 	tell (int);
_CRTIMP int __cdecl 	umask (int);
_CRTIMP int __cdecl 	unlink (const char*);
_CRTIMP int __cdecl 	write (int, const void*, unsigned int);
#endif /* _UWIN */
#endif	/* Not _NO_OLDNAMES */

/* Wide character versions. Also declared in wchar.h. */
/* Not in crtdll.dll */
#if !defined (_WIO_DEFINED)
#if defined (__MSVCRT__)
_CRTIMP int __cdecl	_waccess(const wchar_t*, int);
_CRTIMP int __cdecl 	_wchmod(const wchar_t*, int);
_CRTIMP int __cdecl	_wcreat(const wchar_t*, int);
_CRTIMP long _cdecl	_wfindfirst(const wchar_t*, struct _wfinddata_t*);
_CRTIMP int __cdecl 	_wfindnext(long, struct _wfinddata_t *);
_CRTIMP int __cdecl	_wunlink(const wchar_t*);
_CRTIMP int __cdecl	_wopen(const wchar_t*, int, ...);
_CRTIMP int __cdecl	_wsopen(const wchar_t*, int, int, ...);
_CRTIMP wchar_t * __cdecl _wmktemp(wchar_t*);
_CRTIMP long __cdecl _wfindfirsti64(const wchar_t*, struct _wfinddatai64_t*);
_CRTIMP int __cdecl _wfindnexti64(long, struct _wfinddatai64_t*);

#ifndef __NO_OLDNAMES
/* Where do these live? Not in libmoldname.a nor in libmsvcrt.a */
#if 0
int 		waccess(const wchar_t *, int);
int 		wchmod(const wchar_t *, int);
int 		wcreat(const wchar_t *, int);
long 		wfindfirst(wchar_t *, struct _wfinddata_t *);
int 		wfindnext(long, struct _wfinddata_t *);
int 		wunlink(const wchar_t *);
int 		wrename(const wchar_t *, const wchar_t *);
int 		wopen(const wchar_t *, int, ...);
int 		wsopen(const wchar_t *, int, int, ...);
wchar_t * 	wmktemp(wchar_t *);
#endif
#endif
#endif /* defined (__MSVCRT__) */

#define _WIO_DEFINED
#endif /* _WIO_DEFINED */

__END_CGLOBAL_NAMESPACE

#endif	/* Not RC_INVOKED */

#endif	/* _IO_H_ not defined */

#endif	/* Not strict ANSI */

