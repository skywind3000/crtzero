//=====================================================================
//
// crtzero.h - Embedded system libc free library
//
// NOTE:
//
// The only thing required is libgcc which is a part of gcc itself.
// See: http://wiki.osdev.org/Libgcc
//
// Created by skywind on 2017/11/01
// Last change: 2017/11/01 00:31:10
//
//=====================================================================

#ifndef _CRTZERO_H_
#define _CRTZERO_H_

// optional config
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

// stddef.h and limits.h is required
#ifndef HAVE_NOT_STDDEF_H
#include <stddef.h>
#endif

#ifndef HAVE_NOT_LIMITS_H
#include <limits.h>
#endif



//=====================================================================
// 32 BITS UINT/INT DEFINITION 
//=====================================================================
#ifndef __INTEGER_32_BITS__
#define __INTEGER_32_BITS__
#if defined(__UINT32_TYPE__) && defined(__UINT32_TYPE__)
	typedef __UINT32_TYPE__ ISTDUINT32;
	typedef __INT32_TYPE__ ISTDINT32;
#elif defined(__UINT_FAST32_TYPE__) && defined(__INT_FAST32_TYPE__)
	typedef __UINT_FAST32_TYPE__ ISTDUINT32;
	typedef __INT_FAST32_TYPE__ ISTDINT32;
#elif defined(_WIN64) || defined(WIN64) || defined(__amd64__) || \
	defined(__x86_64) || defined(__x86_64__) || defined(_M_IA64) || \
	defined(_M_AMD64)
	typedef unsigned int ISTDUINT32;
	typedef int ISTDINT32;
#elif defined(_WIN32) || defined(WIN32) || defined(__i386__) || \
	defined(__i386) || defined(_M_X86)
	typedef unsigned long ISTDUINT32;
	typedef long ISTDINT32;
#elif defined(__MACOS__)
	typedef UInt32 ISTDUINT32;
	typedef SInt32 ISTDINT32;
#elif defined(__APPLE__) && defined(__MACH__)
	#include <sys/types.h>
	typedef u_int32_t ISTDUINT32;
	typedef int32_t ISTDINT32;
#elif defined(__BEOS__)
	#include <sys/inttypes.h>
	typedef u_int32_t ISTDUINT32;
	typedef int32_t ISTDINT32;
#elif (defined(_MSC_VER) || defined(__BORLANDC__)) && (!defined(__MSDOS__))
	typedef unsigned __int32 ISTDUINT32;
	typedef __int32 ISTDINT32;
#elif defined(__GNUC__) && (__GNUC__ > 3)
	#include <stdint.h>
	typedef uint32_t ISTDUINT32;
	typedef int32_t ISTDINT32;
#else 
#if UINT_MAX == 0xFFFFU
	typedef unsigned long ISTDUINT32; 
	typedef long ISTDINT32;
#else
	typedef unsigned int ISTDUINT32;
	typedef int ISTDINT32;
#endif
#endif
#endif


//---------------------------------------------------------------------
// UINT/INT DEFINITION
//---------------------------------------------------------------------
#ifndef __IUINT8_DEFINED
#define __IUINT8_DEFINED
typedef unsigned char IUINT8;
#endif

#ifndef __IINT8_DEFINED
#define __IINT8_DEFINED
typedef signed char IINT8;
#endif

#ifndef __IUINT16_DEFINED
#define __IUINT16_DEFINED
typedef unsigned short IUINT16;
#endif

#ifndef __IINT16_DEFINED
#define __IINT16_DEFINED
typedef signed short IINT16;
#endif

#ifndef __IINT32_DEFINED
#define __IINT32_DEFINED
typedef ISTDINT32 IINT32;
#endif

#ifndef __IUINT32_DEFINED
#define __IUINT32_DEFINED
typedef ISTDUINT32 IUINT32;
#endif



//---------------------------------------------------------------------
// INLINE
//---------------------------------------------------------------------
#ifndef INLINE
#if defined(__GNUC__)

#if (__GNUC__ > 3) || ((__GNUC__ == 3) && (__GNUC_MINOR__ >= 1))
#define INLINE         __inline__ __attribute__((always_inline))
#else
#define INLINE         __inline__
#endif

#elif (defined(_MSC_VER) || defined(__WATCOMC__))
#define INLINE __inline
#else
#define INLINE 
#endif
#endif

#if (!defined(__cplusplus)) && (!defined(inline))
#define inline INLINE
#endif



//---------------------------------------------------------------------
// ARCH DETECT
//---------------------------------------------------------------------
#ifndef CRTZERO_ARCH_DEFINED
#define CRTZERO_ARCH_DEFINED

#if defined(__amd64) || defined(__amd64__) || defined(_M_X86_64)
	#define CRTZERO_ARCH_X86_64		1
#elif defined(__x86_64) || defined(__x86_64__) || defined(_M_AMD64)
	#define CRTZERO_ARCH_X86_64		1
#elif defined(__i386) || defined(__i386__) || defined(_M_X86)
	#define CRTZERO_ARCH_X86		1
#elif defined(__i486__) || defined(__i586__) || defined(__i686__)
	#define CRTZERO_ARCH_X86		1
#elif defined(_M_IX86) || defined(__X86__) || defined(_X86_)
	#define CRTZERO_ARCH_X86		1
#elif defined(__arm__) || defined(_ARM) || defined(_M_ARM)
	#define CRTZERO_ARCH_ARM		1
#elif defined(__arm) || defined(__TARGET_ARCH_ARM)
	#define CRTZERO_ARCH_ARM		1
#elif defined(__thumb) || defined(_M_ARMT) || defined(__TARGET_ARCH_THUMB)
	#define CRTZERO_ARCH_ARMT		1
#elif defined(__aarch64__)
	#define CRTZERO_ARCH_ARM64		1
#elif defined(__m68k__) || defined(__MC68K__)
	#define CRTZERO_ARCH_M68K		1
#elif defined(__mips__) || defined(__mips) || defined(__MIPS__)
	#define CRTZERO_ARCH_MIPS		1
#elif defined(_R3000) || defined(_R4000) || defined(_R5900)
	#define CRTZERO_ARCH_MIPS		1
#else
	#define CRTZERO_ARCH_UNKNOW		1
#endif

#endif


//---------------------------------------------------------------------
// BITS
//---------------------------------------------------------------------
#ifndef CRTZERO_CPU_BITS
	#if CRTZERO_ARCH_X86
		#define CRTZERO_CPU_BITS	32
	#elif CRTZERO_ARCH_X86_64
		#define CRTZERO_CPU_BITS	64
	#elif CRTZERO_ARCH_ARM64
		#define CRTZERO_CPU_BITS	64
	#elif CRTZERO_ARCH_ARM
		#define CRTZERO_CPU_BITS	32
	#elif CRTZERO_ARCH_ARMT
		#define CRTZERO_CPU_BITS	16
	#else
		#define CRTZERO_CPU_BITS	32
	#endif
#endif


//---------------------------------------------------------------------
// LSB / MSB
//---------------------------------------------------------------------
#ifndef CRTZERO_CPU_MSB
    #ifdef _BIG_ENDIAN_
        #if _BIG_ENDIAN_
			#define CRTZERO_CPU_MSB		1
		#endif
	#endif
    #ifndef CRTZERO_CPU_MSB
        #if defined(__hppa__) || \
            defined(__m68k__) || defined(mc68000) || defined(_M_M68K) || \
            (defined(__MIPS__) && defined(__MISPEB__)) || \
            defined(__ppc__) || defined(__POWERPC__) || defined(_M_PPC) || \
            defined(__sparc__) || defined(__powerpc__) || \
            defined(__mc68000__) || defined(__s390x__) || defined(__s390__)
            #define CRTZERO_CPU_MSB		1
        #endif
    #endif
    #ifndef CRTZERO_CPU_MSB
        #define CRTZERO_CPU_MSB		0
    #endif
	#if CRTZERO_CPU_MSB
		#define CRTZERO_CPU_LSB		0
	#else
		#define CRTZERO_CPU_LSB		1
	#endif
#endif


//---------------------------------------------------------------------
// Compatible
//---------------------------------------------------------------------

// be ware of the macro risk
#define cz_max(x, y)     (((x) > (y))? (x) : (y))
#define cz_min(x, y)     (((x) < (y))? (x) : (y))
#define cz_abs(x)        (((x) >= 0)? (x) : (-(x)))
#define cz_mid(x, min, max)  \
	( ((x) < (min))? (min) : (((x) > (max))? (max) : (x)) )

#define cz_cast(type, ptr) ((type)(ptr))
#define cz_offset(type, member) ((size_t) (&((type*)0)->member))


// if we have "typeof", macro risk can be prevented.
#if defined(__GCC__) 
#if (__GNUC__ > 4) || ((__GNUC__ == 4) && (__GNUC_MINOR__ >= 3))
#undef cz_abs
#undef cz_mid
#undef cz_max
#undef cz_min

#define cz_min(x, y) ({ typeof(x) __a = (x); typeof(y) __b = (y); \
		__a <= __b ? __a : __b; })

#define cz_max(x, y) ({ typeof(x) __a = (x); typeof(y) __b = (y); \
		__a >= __b ? __a : __b; })

#define cz_abs(x) ({ typeof(x) __a = (x); (__a >= 0)? __a : (-__a); })

#define cz_mid(x, min, max) ({ typeof(x) __x = (x); \
		typeof(min) __min = (min); typeof(max) __max = (max); \
		( (__x < __min)? __min : ((__x > __max)? __max : __x) ); })

#endif
#endif

#ifndef CZ_ASSERT
#define CZ_ASSERT(x) ((void)0)
#endif

#ifndef CZ_STATIC_ASSERT
#define CZ_STATIC_ASSERT(name, x) \
	typedef int _cz_static_assert_ ## name[(x) ? 1 : -1 ]
#endif


CZ_STATIC_ASSERT(SIZE_INT32_IS_4, sizeof(IINT32) == 4);
CZ_STATIC_ASSERT(SIZE_UINT32_IS_4, sizeof(IUINT32) == 4);


#define CZ_INT32_MAX    0x7fffffffl
#define CZ_INT32_MIN    ((-CZ_INT32_MAX) - 1)



#ifdef __cplusplus
extern "C" {
#endif

	
//=====================================================================
// CHAR TYPES
//=====================================================================
extern const IUINT32 cz_ctype[];

#define CZ_UPPER	0x0001
#define CZ_LOWER	0x0002
#define CZ_DIGIT	0x0004
#define CZ_SPACE	0x0008		// HT LF VT FF CR SP
#define CZ_PUNCT	0x0010
#define CZ_CONTROL	0x0020
#define CZ_BLANK	0x0040
#define CZ_HEX		0x0080

#define cz_isalpha(c)  (cz_ctype[(c)] & (CZ_UPPER | CZ_LOWER))
#define cz_isupper(c)  (cz_ctype[(c)] & CZ_UPPER)
#define cz_islower(c)  (cz_ctype[(c)] & CZ_LOWER)
#define cz_isdigit(c)  (cz_ctype[(c)] & CZ_DIGIT)
#define cz_isalnum(c)  (cz_ctype[(c)] & (CZ_DIGIT | CZ_UPPER | CZ_LOWER))
#define cz_ispunct(c)  (cz_ctype[(c)] & CZ_PUNCT)
#define cz_isspace(c)  (cz_ctype[(c)] & CZ_SPACE)
#define cz_isblank(c)  (cz_ctype[(c)] & CZ_BLANK)
#define cz_iscntrl(c)  (cz_ctype[(c)] & CZ_CONTROL)
#define cz_isascii(c)  (((unsigned)(c)) < 128)
#define cz_isgraph(c)  ((c) >= 0x21 && (c) <= 0x7e)
#define cz_isprint(c)  ((c) >= 0x20 && (c) <= 0x7e)
#define cz_isxdigit(c) (cz_ctype[(c)] & (CZ_HEX | CZ_DIGIT))

#define cz_toupper(c)  ((int)((cz_ctype[(c)] >> 8) & 0xff))
#define cz_tolower(c)  ((int)((cz_ctype[(c)] >> 16) & 0xff))



//=====================================================================
// MEMORY STD
//=====================================================================

void* cz_memcpy(void *dst, const void *src, size_t size);
void* cz_memmove(void *dst, const void *src, size_t size);
void* cz_memset(void *dst, int ch, size_t size);
void* cz_memchr(const void *ptr, int ch, size_t size);
int cz_memcmp(const void *lhs, const void *rhs, size_t size);
int cz_memicmp(const void *lhs, const void *rhs, size_t size);
int cz_memscmp(const char *s1, size_t len1, const char *s2, size_t len2);
int cz_memucmp(const char *s1, size_t len1, const char *s2, size_t len2);

extern void* (*_cz_memcpy)(void *dst, const void *src, size_t size);
extern void* (*_cz_memmove)(void *dst, const void *src, size_t size);
extern void* (*_cz_memset)(void *dst, int ch, size_t size);
extern void* (*_cz_memchr)(const void *src, int ch, size_t size);
extern int (*_cz_memcmp)(const void *lhs, const void *rhs, size_t size);
extern int (*_cz_memicmp)(const void *lhs, const void *rhs, size_t size);
extern int (*_cz_memscmp)(const char *, size_t, const char *, size_t);
extern int (*_cz_memucmp)(const char *, size_t, const char *, size_t);


//=====================================================================
// STRING STD
//=====================================================================

size_t cz_strlen(const char *str);
size_t cz_strnlen(const char *str, size_t count);
char* cz_strncpy(char *dst, const char *src, size_t count);
char* cz_strncat(char *dst, const char *src, size_t count);
char* cz_strcpy(char *dst, const char *src);
char* cz_strcat(char *dst, const char *src);

char* cz_strchr(const char *str, int ch);
char* cz_strrchr(const char *str, int ch);
char* cz_strstr(const char *s1, const char *s2);
char* cz_stristr(const char *s1, const char *s2);
char* cz_strsep(char **stringp, const char *delim);

int cz_strcmp(const char *lhs, const char *rhs);
int cz_stricmp(const char *lhs, const char *rhs);
int cz_strncmp(const char *lhs, const char *rhs, size_t count);
int cz_strnicmp(const char *lhs, const char *rhs, size_t count);

size_t cz_strspn(const char *string, const char *control);
size_t cz_strcspn(const char *string, const char *control);
char* cz_strpbrk(const char *string, const char *control);
char* cz_strrev(char *string);


extern size_t (*_cz_strlen)(const char*);
extern size_t (*_cz_strnlen)(const char*, size_t);
extern char* (*_cz_strncpy)(char*, const char*, size_t count);
extern char* (*_cz_strncat)(char*, const char*, size_t count);
extern char* (*_cz_strcpy)(char*, const char*);
extern char* (*_cz_strcat)(char*, const char*);


//=====================================================================
// MUL/DIV - in case that we don't get a libgcc.a 
// Don't use it unless CPU is lack of mul/div instructions and libgcc
// can't really be linked, if so, crtzero will not compromise
//=====================================================================

IUINT16 cz_uint8_mul(IUINT8 x, IUINT8 y);
IUINT32 cz_uint16_mul(IUINT16 x, IUINT16 y);
IUINT32 cz_uint32_mul(IUINT32 x, IUINT32 y);
IUINT32 cz_uint32_mul2(IUINT32 x, IUINT32 y, IUINT32 *high);

// returns (x / y), *rem = x % y
IUINT32 cz_uint32_div(IUINT32 x, IUINT32 y, IUINT32 *rem);


//=====================================================================
// STDLIB
//=====================================================================

IINT32 cz_strtol(const char *nptr, const char **endptr, int ibase);
IUINT32 cz_strtoul(const char *nptr, const char **endptr, int ibase);

char* cz_ltoa(IINT32 val, char *buf, int radix);
char* cz_ultoa(IUINT32 val, char *buf, int radix);

IINT32 cz_atoi(const char *s);

// random without a global seed
IUINT32 cz_crand(IUINT32 *seed);
IUINT32 cz_crandom(IUINT32 num, IUINT32 *seed);

// random with global seed
void cz_srand(int seed);
int cz_rand(void);
int cz_random(int num);

// binary search
void *cz_bsearch(const void *key, const void *base, size_t num, size_t size,
		int (*compare)(const void*, const void*));



#ifdef __cplusplus
}
#endif

#endif



