/* 
 * wctype.h
 *
 * Functions for testing wide character types and converting characters.
 *
 * This file is part of the Mingw32 package.
 *
 * Contributors:
 *  Created by Mumit Khan <khan@xraylith.wisc.edu>
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
 */

#ifndef _WCTYPE_H_
#define _WCTYPE_H_

/* All the headers include this file. */
#include <_mingw.h>

#define	__need_wchar_t
#define	__need_wint_t
#ifndef RC_INVOKED
#include <stddef.h>
#endif	/* Not RC_INVOKED */

/*
 * The following flags are used to tell iswctype and _isctype what character
 * types you are looking for.
 */
#define	_UPPER		0x0001
#define	_LOWER		0x0002
#define	_DIGIT		0x0004
#define	_SPACE		0x0008
#define	_PUNCT		0x0010
#define	_CONTROL	0x0020
#define	_BLANK		0x0040
#define	_HEX		0x0080
#define	_LEADBYTE	0x8000

#define	_ALPHA		0x0103

#ifndef RC_INVOKED

__BEGIN_CSTD_NAMESPACE

#ifndef WEOF
#define	WEOF	(wchar_t)(0xFFFF)
#endif

#ifndef _WCTYPE_T_DEFINED
typedef wchar_t wctype_t;
#define _WCTYPE_T_DEFINED
#endif

/* Wide character equivalents - also in ctype.h */
_CRTIMP int __cdecl iswalnum(wint_t);
_CRTIMP int __cdecl iswalpha(wint_t);
_CRTIMP int __cdecl iswascii(wint_t);
_CRTIMP int __cdecl iswcntrl(wint_t);
_CRTIMP int __cdecl iswctype(wint_t, wctype_t);
_CRTIMP int __cdecl iswdigit(wint_t);
_CRTIMP int __cdecl iswgraph(wint_t);
_CRTIMP int __cdecl iswlower(wint_t);
_CRTIMP int __cdecl iswprint(wint_t);
_CRTIMP int __cdecl iswpunct(wint_t);
_CRTIMP int __cdecl iswspace(wint_t);
_CRTIMP int __cdecl iswupper(wint_t);
_CRTIMP int __cdecl iswxdigit(wint_t);

_CRTIMP wchar_t __cdecl towlower(wchar_t);
_CRTIMP wchar_t	__cdecl towupper(wchar_t);

_CRTIMP int __cdecl isleadbyte (int);

/* Also in ctype.h */

#ifdef __DECLSPEC_SUPPORTED
__MINGW_IMPORT unsigned short _ctype[];
# ifdef __MSVCRT__
  __MINGW_IMPORT unsigned short* _pctype;
# else	/* CRTDLL */
  __MINGW_IMPORT unsigned short* _pctype_dll;
# define  _pctype _pctype_dll
# endif

#else		/* ! __DECLSPEC_SUPPORTED */
extern unsigned short** _imp___ctype;
#define _ctype (*_imp___ctype)
# ifdef __MSVCRT__
  extern unsigned short** _imp___pctype;
# define _pctype (*_imp___pctype)
# else	/* CRTDLL */
  extern unsigned short** _imp___pctype_dll;
# define _pctype (*_imp___pctype_dll)
# endif	/* CRTDLL */
#endif		/*  __DECLSPEC_SUPPORTED */

#if !(defined (__NO_INLINE__) || defined(__NO_CTYPE_INLINES) \
      || defined(__WCTYPE_INLINES_DEFINED))
#define __WCTYPE_INLINES_DEFINED
extern __inline__ int __cdecl iswalnum(wint_t __wc) {return (iswctype(__wc,_ALPHA|_DIGIT));}
extern __inline__ int __cdecl iswalpha(wint_t __wc) {return (iswctype(__wc,_ALPHA));}
extern __inline__ int __cdecl iswascii(wint_t __wc) {return ((__wc & ~0x7F) == 0);}
extern __inline__ int __cdecl iswcntrl(wint_t __wc) {return (iswctype(__wc,_CONTROL));}
extern __inline__ int __cdecl iswdigit(wint_t __wc) {return (iswctype(__wc,_DIGIT));}
extern __inline__ int __cdecl iswgraph(wint_t __wc) {return (iswctype(__wc,_PUNCT|_ALPHA|_DIGIT));}
extern __inline__ int __cdecl iswlower(wint_t __wc) {return (iswctype(__wc,_LOWER));}
extern __inline__ int __cdecl iswprint(wint_t __wc) {return (iswctype(__wc,_BLANK|_PUNCT|_ALPHA|_DIGIT));}
extern __inline__ int __cdecl iswpunct(wint_t __wc) {return (iswctype(__wc,_PUNCT));}
extern __inline__ int __cdecl iswspace(wint_t __wc) {return (iswctype(__wc,_SPACE));}
extern __inline__ int __cdecl iswupper(wint_t __wc) {return (iswctype(__wc,_UPPER));}
extern __inline__ int __cdecl iswxdigit(wint_t __wc) {return (iswctype(__wc,_HEX));}
extern __inline__ int __cdecl isleadbyte(int __c)
  {return (_pctype[(unsigned char)(__c)] & _LEADBYTE);}
#endif /* !(defined(__NO_CTYPE_INLINES) || defined(__WCTYPE_INLINES_DEFINED)) */

typedef wchar_t wctrans_t;
_CRTIMP wint_t __cdecl towctrans(wint_t, wctrans_t);
_CRTIMP wctrans_t __cdecl wctrans(const char*);
_CRTIMP wctype_t __cdecl wctype(const char*);

__END_CSTD_NAMESPACE

#ifndef __STRICT_ANSI__
__BEGIN_CGLOBAL_NAMESPACE
_CRTIMP int __cdecl is_wctype(__CSTD wint_t, __CSTD wctype_t);	/* Obsolete! */
__END_CGLOBAL_NAMESPACE
#endif /* __STRICT_ANSI__ */

#endif	/* Not RC_INVOKED */

#endif	/* Not _WCTYPE_H_ */

