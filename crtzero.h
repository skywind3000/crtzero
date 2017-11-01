//=====================================================================
//
// crtzero.h - 
//
// Created by skywind on 2017/11/01
// Last change: 2017/11/01 00:31:10
//
//=====================================================================

#ifndef _CRTZERO_H_
#define _CRTZERO_H_

// only need stddef.h and limits.h
#include <stddef.h>
#include <limits.h>

// optional config
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif



/**********************************************************************
 * 32BIT INTEGER DEFINITION 
 **********************************************************************/
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
#include <limits.h>
#if UINT_MAX == 0xFFFFU
	typedef unsigned long ISTDUINT32; 
	typedef long ISTDINT32;
#else
	typedef unsigned int ISTDUINT32;
	typedef int ISTDINT32;
#endif
#endif
#endif


/**********************************************************************
 * Global Macros
 **********************************************************************/
#ifndef __IINT8_DEFINED
#define __IINT8_DEFINED
typedef char IINT8;
#endif

#ifndef __IUINT8_DEFINED
#define __IUINT8_DEFINED
typedef unsigned char IUINT8;
#endif

#ifndef __IUINT16_DEFINED
#define __IUINT16_DEFINED
typedef unsigned short IUINT16;
#endif

#ifndef __IINT16_DEFINED
#define __IINT16_DEFINED
typedef short IINT16;
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

#elif (defined(_MSC_VER) || defined(__BORLANDC__) || defined(__WATCOMC__))
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
	#else
		#define CRTZERO_CPU_BITS	32
	#endif
#endif


//---------------------------------------------------------------------
// FEATURES
//---------------------------------------------------------------------
#ifndef CRTZERO_FEATURE_INT_MUL
#define CRTZERO_FEATURE_INT_MUL		0
#endif

#ifndef CRTZERO_FEATURE_INT_DIV
#define CRTZERO_FEATURE_INT_DIV		0
#endif


//=====================================================================
// Math - Never give up old 8 bits retro CPUs
//=====================================================================

static inline IUINT8 cz_uint8_add(IUINT8 x, IUINT8 y, IUINT8 *c) {
}

// z = x << y
static inline IUINT16 cz_uint16_shl(IUINT16 x, IUINT8 y) {
#if CRTZERO_CPU_BITS > 8
	return (x << y);
#else
#endif
}

// z = x >> y
static inline IUINT16 cz_uint16_shr(IUINT16 x, IUINT8 y) {
#if CRTZERO_CPU_BITS > 8
	return (x >> y);
#else
#endif
}


//=====================================================================
// Math - CPUs may be lack of mul/div instructions (arm, RISC V std.)
//=====================================================================
extern const IUINT8 cz_mul_ltb_16[16][16];

// z = x * y
static inline IUINT16 cz_uint8_mul(IUINT8 x, IUINT8 y) {
#if CRTZERO_FEATURE_INT_MUL
	return ((IUINT16)x) * ((IUINT16)y);
#else
	IUINT8 xh = x >> 4, xl = x & 0xf;
	IUINT8 yh = y >> 4, yl = y & 0xf;
	return	(((IUINT16)cz_mul_ltb_16[xl][yl]) << 0) + 
			(((IUINT16)cz_mul_ltb_16[xh][yl]) << 4) +
			(((IUINT16)cz_mul_ltb_16[xl][yh]) << 4) + 
			(((IUINT16)cz_mul_ltb_16[xh][yh]) << 8);
#endif
}

static inline IINT16 cz_int8_mul(IINT8 x, IINT8 y) {
#if CRTZERO_FEATURE_INT_MUL
	return ((IINT16)x) * ((IINT16)y);
#else
	IUINT16 c = cz_uint8_mul(((IUINT8)x) & 0x7f, ((IUINT8)y) & 0x7f);
	if ((((IUINT8)x) & 0x80) ^ (((IUINT8)y) & 0x80)) {
		return -((IINT16)c);
	}	else {
		return (IINT16)c;
	}
#endif
}

static inline IUINT32 cz_uint16_mul(IUINT16 x, IUINT16 y) {
#if CRTZERO_FEATURE_INT_MUL
	return ((IUINT32)x) * ((IUINT32)y);
#else
	IUINT16 xh = x >> 8, xl = x & 0xff;
	IUINT16 yh = y >> 8, yl = y & 0xff;
	return	(((IUINT32)cz_uint8_mul(xl, yl)) <<  0) +
			(((IUINT32)cz_uint8_mul(xh, yl)) <<  8) + 
			(((IUINT32)cz_uint8_mul(xl, yh)) <<  8) + 
			(((IUINT32)cz_uint8_mul(xh, yh)) << 16);
#endif
}

static inline IINT32 cz_int16_mul(IINT16 x, IINT16 y) {
#if CRTZERO_FEATURE_INT_MUL
	return ((IINT32)x) * ((IINT32)y);
#else
	IUINT32 c = cz_uint16_mul(((IUINT16)x) & 0x7fff, ((IUINT16)y) & 0x7fff);
	if ((((IUINT16)x) & 0x8000) ^ (((IUINT16)y) & 0x8000)) {
		return -((IINT32)c);
	}	else {
		return (IINT32)c;
	}
#endif
}


#endif



