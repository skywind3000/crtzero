//=====================================================================
//
// crtzero.c - Embedded system libc free library
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
#include "crtzero.h"


//=====================================================================
// CHAR TYPES
//=====================================================================
const IUINT32 cz_ctype[256] = {
    32, 65824, 131616, 197408, 263200, 328992, 394784, 460576, 526368,
    592232, 657960, 723752, 789544, 855336, 921120, 986912, 1052704,
    1118496, 1184288, 1250080, 1315872, 1381664, 1447456, 1513248, 1579040,
    1644832, 1710624, 1776416, 1842208, 1908000, 1973792, 2039584, 2105416,
    2171152, 2236944, 2302736, 2368528, 2434320, 2500112, 2565904, 2631696,
    2697488, 2763280, 2829072, 2894864, 2960656, 3026448, 3092240, 3158020,
    3223812, 3289604, 3355396, 3421188, 3486980, 3552772, 3618564, 3684356,
    3750148, 3815952, 3881744, 3947536, 4013328, 4079120, 4144912, 4210704,
    6373761, 6439553, 6505345, 6571137, 6636929, 6702721, 6768385, 6834177,
    6899969, 6965761, 7031553, 7097345, 7163137, 7228929, 7294721, 7360513,
    7426305, 7492097, 7557889, 7623681, 7689473, 7755265, 7821057, 7886849,
    7952641, 8018433, 5987088, 6052880, 6118672, 6184464, 6250256, 6316048,
    6373762, 6439554, 6505346, 6571138, 6636930, 6702722, 6768386, 6834178,
    6899970, 6965762, 7031554, 7097346, 7163138, 7228930, 7294722, 7360514,
    7426306, 7492098, 7557890, 7623682, 7689474, 7755266, 7821058, 7886850,
    7952642, 8018434, 8092432, 8158224, 8224016, 8289808, 8355616, 8421376,
    8487168, 8552960, 8618752, 8684544, 8750336, 8816128, 8881920, 8947712,
    9013504, 9079296, 9145088, 9210880, 9276672, 9342464, 9408256, 9474048,
    9539840, 9605632, 9671424, 9737216, 9803008, 9868800, 9934592, 10000384,
    10066176, 10131968, 10197760, 10263552, 10329344, 10395136, 10460928,
    10526720, 10592512, 10658304, 10724096, 10789888, 10855680, 10921472,
    10987264, 11053056, 11118848, 11184640, 11250432, 11316224, 11382016,
    11447808, 11513600, 11579392, 11645184, 11710976, 11776768, 11842560,
    11908352, 11974144, 12039936, 12105728, 12171520, 12237312, 12303104,
    12368896, 12434688, 12500480, 12566272, 12632064, 12697856, 12763648,
    12829440, 12895232, 12961024, 13026816, 13092608, 13158400, 13224192,
    13289984, 13355776, 13421568, 13487360, 13553152, 13618944, 13684736,
    13750528, 13816320, 13882112, 13947904, 14013696, 14079488, 14145280,
    14211072, 14276864, 14342656, 14408448, 14474240, 14540032, 14605824,
    14671616, 14737408, 14803200, 14868992, 14934784, 15000576, 15066368,
    15132160, 15197952, 15263744, 15329536, 15395328, 15461120, 15526912,
    15592704, 15658496, 15724288, 15790080, 15855872, 15921664, 15987456,
    16053248, 16119040, 16184832, 16250624, 16316416, 16382208, 16448000,
    16513792, 16579584, 16645376, 16711168, 16776960,
};


//=====================================================================
// MEMORY STD
//=====================================================================

// default functions
void* (*_cz_memcpy)(void *dst, const void *src, size_t size) = NULL;
void* (*_cz_memmove)(void *dst, const void *src, size_t size) = NULL;
void* (*_cz_memset)(void *dst, int ch, size_t size) = NULL;
void* (*_cz_memchr)(const void *src, int ch, size_t size) = NULL;
int (*_cz_memcmp)(const void *lhs, const void *rhs, size_t size) = NULL;
int (*_cz_memicmp)(const void *lhs, const void *rhs, size_t size) = NULL;
int (*_cz_memscmp)(const char *, size_t, const char *, size_t) = NULL;
int (*_cz_memucmp)(const char *, size_t, const char *, size_t) = NULL;

void* cz_memcpy(void *dst, const void *src, size_t size)
{
	const char *ss = (const char*)src;
	char *dd = (char*)dst;
	if (_cz_memcpy) {
		return _cz_memcpy(dst, src, size);
	}
	// no need to unroll, modern CPUs is capable to predict small loops
	for (; size >= 4; dd += 4, ss += 4, size -= 4) {
		*((IUINT32*)dd) = *((const IUINT32*)ss);
	}
	switch (size) {
	case 3: dd[2] = ss[2];
	case 2: *((IUINT16*)dd) = *((const IUINT16*)ss); break;
	case 1: dd[0] = ss[0]; break;
	}
	return dst;
}


void* cz_memmove(void *dst, const void *src, size_t size)
{
	const char *ss = (const char*)src;
	char *dd = (char*)dst;
	if (_cz_memmove) {
		return _cz_memmove(dst, src, size);
	}
	if (dd == ss) { return dst; }
	if (dd < ss || dd >= ss + size) {
		return cz_memcpy(dst, src, size);
	}	else {
		dd += size;
		ss += size;
		for (; size >= 4; dd -= 4, ss -= 4, size -= 4) {
			*((IUINT32*)(dd - 4)) = *((const IUINT32*)(ss - 4));
		}
		switch (size) {
		case 3: 
			*((IUINT16*)(dd - 2)) = *((const IUINT16*)(ss - 2)); 
			dd[-3] = ss[-3];
			break;
		case 2: *((IUINT16*)(dd - 2)) = *((const IUINT16*)(ss - 2)); break;
		case 1: dd[-1] = ss[-1]; break;
		}
	}
	return dst;
}


void* cz_memset(void *dst, int ch, size_t size)
{
	IUINT32 cc = (IUINT32)(ch & 0xff);
	unsigned char *dd = (unsigned char*)dst;
	if (_cz_memset) {
		return _cz_memset(dst, ch, size);
	}
	cc = (cc << 24) | (cc << 16) | (cc << 8) | cc;
	for (; size >= 4; dd += 4, size -= 4) {
		*((IUINT32*)dd) = cc;
	}
	switch (size) {
	case 3: dd[2] = (IUINT8)(cc & 0xff);
	case 2: *((IUINT16*)dd) = (IUINT16)(cc & 0xffff); break;
	case 1: dd[0] = (IUINT8)(cc & 0xff);
	}
	return dst;
}


void* cz_memchr(const void *ptr, int ch, size_t size)
{
	if (_cz_memchr) {
		return _cz_memchr(ptr, ch, size);
	}
	while ( size && (*(unsigned char *)ptr != (unsigned char)ch) ) {
		ptr = (unsigned char *)ptr + 1;
		size--;
	}
	return (size ? (void *)ptr : NULL);
}


int cz_memcmp(const void *lhs, const void *rhs, size_t size)
{
	const unsigned char *ll = (const unsigned char*)lhs;
	const unsigned char *rr = (const unsigned char*)rhs;
	if (ll == rr || size == 0) return 0;
	if (_cz_memcmp) {
		return _cz_memcmp(lhs, rhs, size);
	}
	for (; size >= 4; ll += 4, rr += 4, size -= 4) {
		if (*((const IUINT32*)ll) != *((const IUINT32*)rr)) break;
	}
	for (; size > 0; ll++, rr++, size--) {
		if (ll[0] != rr[0]) break;
	}
	if (size > 0) {
		return (ll[0] <= rr[0])? -1 : 1;
	}
	return 0;
}

int cz_memicmp(const void *lhs, const void *rhs, size_t size)
{
	const unsigned char *ll = (const unsigned char*)lhs;
	const unsigned char *rr = (const unsigned char*)rhs;
	if (ll == rr || size == 0) return 0;
	if (_cz_memicmp) {
		return _cz_memicmp(lhs, rhs, size);
	}
	for (; size > 0; ll++, rr++, size--) {
		if (cz_tolower(ll[0]) != cz_tolower(rr[0])) break;
	}
	if (size > 0) {
		return (cz_tolower(ll[0]) <= cz_tolower(rr[0]))? -1 : 1;
	}
	return 0;
}

int cz_memscmp(const char *s1, size_t len1, const char *s2, size_t len2)
{
	size_t minsize;
	int hr;
	if (_cz_memscmp) {
		return _cz_memscmp(s1, len1, s2, len2);
	}
	minsize = cz_min(len1, len2);
	hr = cz_memcmp(s1, s2, minsize);
	if (hr != 0) return hr;
	return (len1 < len2)? -1 : 1;
}

int cz_memucmp(const char *s1, size_t len1, const char *s2, size_t len2)
{
	size_t minsize;
	int hr;
	if (_cz_memucmp) {
		return _cz_memucmp(s1, len1, s2, len2);
	}
	minsize = cz_min(len1, len2);
	hr = _cz_memicmp(s1, s2, minsize);
	if (hr != 0) return hr;
	return (len1 < len2)? -1 : 1;
}






//=====================================================================
// STRING STD
//=====================================================================
size_t (*_cz_strlen)(const char*) = NULL;
size_t (*_cz_strnlen)(const char*, size_t) = NULL;
char* (*_cz_strncpy)(char*, const char*, size_t count) = NULL;
char* (*_cz_strncat)(char*, const char*, size_t count) = NULL;
char* (*_cz_strcpy)(char*, const char*) = NULL;
char* (*_cz_strcat)(char*, const char*) = NULL;


size_t cz_strlen(const char *str)
{
	const char *eos = str;
	if (_cz_strlen) {
		return _cz_strlen(str);
	}
	while (*eos++) ;
	return (int)(eos - str - 1);
}

size_t cz_strnlen(const char *str, size_t count)
{
	int n;
	if (_cz_strnlen) {
		return _cz_strnlen(str, count);
	}
	for (n = 0; count > 0 && *str != '\0'; str++, count--) n++;
	return n;
}


char* cz_strncpy(char *dst, const char *src, size_t count)
{
	char *start = dst;
	if (_cz_strncpy) {
		return _cz_strncpy(dst, src, count);
	}
	while (count && (*dst++ = *src++)) count--;
	if (count) {
		while (--count) *dst++ = '\0';
	}
	return start;
}

char* cz_strcpy(char *dst, const char *src)
{
	char *start = dst;
	if (_cz_strcpy) {
		return _cz_strcpy(dst, src);
	}
	for (; src[0]; src++, dst++) dst[0] = src[0];
	dst[0] = '\0';
	return start;
}

char* cz_strncat(char *dst, const char *src, size_t count)
{
	char *start = dst;
	if (_cz_strncat) {
		return _cz_strncat(dst, src, count);
	}
	while (dst[0]) dst++;
	while (count--) {
		if (!(*dst++ = *src++))
			return start;
	}
	*dst = '\0';
	return start;
}

char* cz_strcat(char *dst, const char *src)
{
	char *start = dst;
	if (_cz_strcat) {
		return _cz_strcat(dst, src);
	}
	while (dst[0]) dst++;
	for (; src[0]; src++, dst++) dst[0] = src[0];
	*dst = '\0';
	return start;
}

char* cz_strchr(const char *str, int ch)
{
	while (*str && *str != (char)ch) str++;
	if (*str == (char)ch) return (char*)str;
	return NULL;
}

char* cz_strrchr(const char *str, int ch)
{
	char *start = (char *)str;
	while (*str++);
	while (--str != start && *str != (char)ch);
	if (*str == (char)ch)
		return (char*)str;
	return NULL;
}

char* cz_strstr(const char *s1, const char *s2)
{  
	const char* ptr = s1;
	if (!s1 || !s2 || !*s2) return (char*)s1;
	while (*ptr) {
		if (*ptr == *s2) {
			const char* cur1 = ptr + 1;
			const char* cur2 = s2 + 1;
			while (*cur1 && *cur2 && *cur1 == *cur2) {
				cur1++;
				cur2++;
			}
			if (!*cur2) return (char*)ptr;
		}
		ptr++;
	}
	return NULL;
}

char* cz_stristr(const char *s1, const char *s2)
{
	const char* ptr = s1;
	if (!s1 || !s2 || !*s2) return (char*)s1;
	while (*ptr) {
		if (cz_tolower((unsigned char)ptr[0]) == 
			cz_tolower((unsigned char)s2[0])) {
			const char* cur1 = ptr + 1;
			const char* cur2 = s2 + 1;
			while (*cur1 && *cur2 && 
					cz_tolower((unsigned char)cur1[0]) == 
					cz_tolower((unsigned char)cur2[0])) {
				cur1++;
				cur2++;
			}
			if (!*cur2) return (char*)ptr;
		}
		ptr++;
	}
	return NULL;
}

char* cz_strsep(char **stringp, const char *delim)
{
	char *s, *tok;
	const char *spanp;
	int c, sc;
	if ((s = *stringp) == NULL) return NULL;
	for (tok = s;;) {
		c = *s++;
		spanp = delim;
		do {
			if ((sc = *spanp++) == c) {
				if (c == 0) s = NULL;
				else s[-1] = 0;
				*stringp = s;
				return tok;
			}
		}	while (sc != 0);
	}
}

int cz_strcmp(const char *lhs, const char *rhs)
{
	size_t ls = cz_strlen(lhs);
	size_t rs = cz_strlen(rhs);
	return cz_memscmp(lhs, ls, rhs, rs);
}

int cz_stricmp(const char *lhs, const char *rhs)
{
	size_t ls = cz_strlen(lhs);
	size_t rs = cz_strlen(rhs);
	return cz_memucmp(lhs, ls, rhs, rs);
}

int cz_strncmp(const char *lhs, const char *rhs, size_t count)
{
	size_t ls = cz_strlen(lhs);
	size_t rs = cz_strlen(rhs);
	ls = cz_max(ls, count);
	rs = cz_max(rs, count);
	return cz_memscmp(lhs, ls, rhs, rs);
}

int cz_strnicmp(const char *lhs, const char *rhs, size_t count)
{
	size_t ls = cz_strlen(lhs);
	size_t rs = cz_strlen(rhs);
	ls = cz_max(ls, count);
	rs = cz_max(rs, count);
	return cz_memucmp(lhs, ls, rhs, rs);
}

size_t cz_strspn(const char *string, const char *control)
{
	const unsigned char *str = (const unsigned char*)string;
	const unsigned char *ctrl = (const unsigned char*)control;
	unsigned char map[32];
	int count;
	cz_memset(map, 0, 32);
	while (*ctrl) {
		map[*ctrl >> 3] |= (1 << (*ctrl & 7));
		ctrl++;
	}
	if (*str) {
		count = 0;
		while (map[*str >> 3] & (1 << (*str & 7))) {
			count++;
			str++;
		}
		return count;
	}
	return 0;
}

size_t cz_strcspn(const char *string, const char *control)
{
	const unsigned char *str = (const unsigned char*)string;
	const unsigned char *ctrl = (const unsigned char*)control;
	unsigned char map[32];
	int count;
	cz_memset(map, 0, 32);
	while (*ctrl) {
		map[*ctrl >> 3] |= (1 << (*ctrl & 7));
		ctrl++;
	}
	count = 0;
	map[0] |= 1;
	while (!(map[*str >> 3] & (1 << (*str & 7)))) {
		count++;
		str++;
	}
	return count;
}

char* cz_strpbrk(const char *string, const char *control)
{
	const unsigned char *str = (const unsigned char*)string;
	const unsigned char *ctrl = (const unsigned char*)control;
	unsigned char map[32];
	cz_memset(map, 0, 32);
	while (*ctrl) {
		map[*ctrl >> 3] |= (1 << (*ctrl & 7));
		ctrl++;
	}
	for (; *str; str++) {
		if (map[*str >> 3] & (1 << (*str & 7)))
			return (char*)str;
	}
	return NULL;
}


char* cz_strrev(char *string)
{
	char *start = string;
	char *left = string;
	char ch;
	if (string[0]) {
		for (; string[1]; string++);
		for (; left < string; ) {
			ch = *left; *left++ = *string; *string-- = ch;
		}
	}
	return start;	
}


//=====================================================================
// MUL/DIV - in case that we don't get a libgcc.a 
// Do not use it unless CPU is lack of mul/div instructions and 
// libgcc.a can't really be linked, if so, crtzero'll take care.
//=====================================================================
static const IUINT8 cz_mul_ltb_16[16][16] = {
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15},
  { 0, 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30},
  { 0, 3, 6, 9, 12, 15, 18, 21, 24, 27, 30, 33, 36, 39, 42, 45},
  { 0, 4, 8, 12, 16, 20, 24, 28, 32, 36, 40, 44, 48, 52, 56, 60},
  { 0, 5, 10, 15, 20, 25, 30, 35, 40, 45, 50, 55, 60, 65, 70, 75},
  { 0, 6, 12, 18, 24, 30, 36, 42, 48, 54, 60, 66, 72, 78, 84, 90},
  { 0, 7, 14, 21, 28, 35, 42, 49, 56, 63, 70, 77, 84, 91, 98, 105},
  { 0, 8, 16, 24, 32, 40, 48, 56, 64, 72, 80, 88, 96, 104, 112, 120},
  { 0, 9, 18, 27, 36, 45, 54, 63, 72, 81, 90, 99, 108, 117, 126, 135},
  { 0, 10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110, 120, 130, 140, 150},
  { 0, 11, 22, 33, 44, 55, 66, 77, 88, 99, 110, 121, 132, 143, 154, 165},
  { 0, 12, 24, 36, 48, 60, 72, 84, 96, 108, 120, 132, 144, 156, 168, 180},
  { 0, 13, 26, 39, 52, 65, 78, 91, 104, 117, 130, 143, 156, 169, 182, 195},
  { 0, 14, 28, 42, 56, 70, 84, 98, 112, 126, 140, 154, 168, 182, 196, 210},
  { 0, 15, 30, 45, 60, 75, 90, 105, 120, 135, 150, 165, 180, 195, 210, 225},
};


static inline IUINT16 _cz_uint8_mul(IUINT8 x, IUINT8 y) 
{
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

static inline IUINT32 _cz_uint16_mul(IUINT16 x, IUINT16 y)
{
#if CRTZERO_FEATURE_INT_MUL
	return ((IUINT32)x) * ((IUINT32)y);
#else
	IUINT16 xh = x >> 8, xl = x & 0xff;
	IUINT16 yh = y >> 8, yl = y & 0xff;
	return	(((IUINT32)_cz_uint8_mul(xl, yl)) <<  0) +
			(((IUINT32)_cz_uint8_mul(xh, yl)) <<  8) + 
			(((IUINT32)_cz_uint8_mul(xl, yh)) <<  8) + 
			(((IUINT32)_cz_uint8_mul(xh, yh)) << 16);
#endif
}

IUINT32 cz_uint32_mul2(IUINT32 x, IUINT32 y, IUINT32 *high)
{
	IUINT32 z0, z1, z2, z3, m;
	IUINT16 xl = (IUINT16)(x & 0xffff);
	IUINT16 xh = (IUINT16)(x >> 16);
	IUINT16 yl = (IUINT16)(y & 0xffff);
	IUINT16 yh = (IUINT16)(y >> 16);

	z0 = z1 = z2 = z3 = 0;

	m = _cz_uint16_mul(xl, yl);
	z0 = (m & 0xffff);
	z1 = (m >> 16);

	m = _cz_uint16_mul(xh, yl) + z1;
	z1 = m & 0xffff;
	z2 += (m >> 16);

	m = _cz_uint16_mul(xl, yh) + z1;
	z1 = m & 0xffff;
	z2 += (m >> 16);

	m = _cz_uint16_mul(xh, yh) + z2;
	z2 = m & 0xffff;
	z3 += (m >> 16);
	
	m = z0 | (z1 << 16);
	high[0] = z2 | (z3 << 16);

	return m;
}

IUINT32 cz_uint32_mul(IUINT32 x, IUINT32 y) {
#if CRTZERO_FEATURE_INT_MUL
	return (x * y);
#else
	IUINT32 z0 = 0, z1 = 0, m;
	IUINT16 xl = (IUINT16)(x & 0xffff);
	IUINT16 xh = (IUINT16)(x >> 16);
	IUINT16 yl = (IUINT16)(y & 0xffff);
	IUINT16 yh = (IUINT16)(y >> 16);

	m = _cz_uint16_mul(xl, yl);
	z0 = (m & 0xffff);
	z1 = (m >> 16);

	m = _cz_uint16_mul(xh, yl) + z1;
	z1 = m & 0xffff;

	m = _cz_uint16_mul(xl, yh) + z1;
	z1 = m & 0xffff;

	return z0 | (z1 << 16);
#endif
}


IUINT16 cz_uint8_mul(IUINT8 x, IUINT8 y) { return _cz_uint8_mul(x, y); }
IUINT32 cz_uint16_mul(IUINT16 x, IUINT16 y) { return _cz_uint16_mul(x, y); }

IUINT32 cz_uint32_div(IUINT32 x, IUINT32 y, IUINT32 *rem) {
#if CRTZERO_FEATURE_INT_DIV
	IUINT32 m = x / y;
	if (rem) {
		rem[0] = x % y;
	}
	return m;
#else
	IUINT32 count, z, m;
	if (y == 0) {
		CZ_ASSERT(y != 0);
		if (rem) rem[0] = 0;
		return 0;
	}
	else if (x == 0) {
		if (rem) rem[0] = 0;
		return 0;
	}
	else if (x == y) {
		if (rem) rem[0] = 0;
		return 1;
	}
	else if (x < y) {
		if (rem) rem[0] = x;
		return 0;
	}

	for (count = 0; y < x; count++) {
		if (y & (((IUINT32)1) << 31)) break;
		y <<= 1;
	}

	for (z = 0, m = x; m; ) {
		if (m >= y) {
			m -= y;
			z |= ((IUINT32)1) << count;
		}
		if (count == 0) {
			break;
		}
		y >>= 1;
		count--;
	}
	if (rem) rem[0] = m;
	return z;
#endif
}



//=====================================================================
// STDLIB
//=====================================================================

/* _cz_strtoxl macro */
#define IFL_NEG			1
#define IFL_READDIGIT	2
#define IFL_OVERFLOW	4
#define IFL_UNSIGNED	8

/* istrtoxl */
static IUINT32 _cz_strtoxl(const char *nptr, const char **endptr,
	int ibase, int flags)
{
	const char *p;
	char c;
	IUINT32 number;
	IUINT32 digval;
	IUINT32 maxval;
	IUINT32 limit;
	IUINT32 maxu32;

	if (endptr != NULL) *endptr = nptr;
	CZ_ASSERT(ibase == 0 || (ibase >= 2 && ibase <= 36));

	p = nptr;
	number = 0;

	c = *p++;
	while (cz_isspace((int)(IUINT8)c)) c = *p++;

	if (c == '+') c = *p++;
	if (c == '-') {
		flags |= IFL_NEG;
		c = *p++;
	}

	if (c == '+') c = *p++;

	if (ibase < 0 || ibase == 1 || ibase > 36) {
		if (endptr) *endptr = nptr;
		return 0;
	}

	if (ibase == 0) {
		if (c != '0') ibase = 10;
		else if (*p == 'x' || *p == 'X') ibase = 16;
		else if (*p == 'b' || *p == 'B') ibase = 2;
		else ibase = 8;
	}

	if (ibase == 16) {
		if (c == '0' && (*p == 'x' || *p == 'X')) {
			p++;
			c = *p++;
		}
	}
	else if (ibase == 2) {
		if (c == '0' && (*p == 'b' || *p == 'B')) {
			p++;
			c = *p++;
		}
	}

	maxu32 = ~((IUINT32)0);
	maxval = cz_uint32_div(maxu32, ibase, NULL);

	for (; ; ) {
		if (cz_isdigit((int)(IUINT8)c)) digval = c - '0';
		else if (cz_isalpha((int)(IUINT8)c)) 
			digval = (char)cz_toupper((IUINT8)c) - 'A' + 10;
		else break;

		if (digval >= (IUINT32)ibase) break;

		flags |= IFL_READDIGIT;
	
		if (number < maxval || (number == maxval && 
			(IUINT32)digval <= maxval)) {
			number = cz_uint32_mul(number, ibase) + digval;
		}	else {
			flags |= IFL_OVERFLOW;
			if (endptr == NULL) {
				break;
			}
		}

		c = *p++;
	}

	--p;

	limit = ((IUINT32)CZ_INT32_MAX) + 1;

	if (!(flags & IFL_READDIGIT)) {
		if (endptr) *endptr = nptr;
		number = 0;
	}
	else if ((flags & IFL_UNSIGNED) && (flags & IFL_NEG)) {
		number = 0;
	}
	else if ((flags & IFL_OVERFLOW) || 
		(!(flags & IFL_UNSIGNED) &&
		(((flags & IFL_NEG) && (number > limit)) || 
		(!(flags & IFL_NEG) && (number > limit - 1))))) {
		if (flags & IFL_UNSIGNED) number = maxu32;
		else if (flags & IFL_NEG) number = (IUINT32)CZ_INT32_MIN;
		else number = (IUINT32)CZ_INT32_MAX;
	}

	if (endptr) *endptr = p;

	if (flags & IFL_NEG)
		number = (IUINT32)(-(IINT32)number);

	return number;
}


static int _cz_xtoa(IUINT32 val, char *buf, unsigned radix, int is_neg)
{
	IUINT32 digval = 0;
	char *firstdig, *p;
	char temp;
	int size = 0;

	p = buf;
	if (is_neg) {
		if (buf) *p++ = '-';
		size++;
		val = (IUINT32)(-(IINT32)val);
	}

	firstdig = p;

	do {
	#if 1
		val = cz_uint32_div(val, radix, &digval);
	#else
		digval = (IUINT64)(val % (int)radix);
		val /= (int)radix;
	#endif
		if (digval > 9 && buf) *p++ = (char)(digval - 10 + 'a');
		else if (digval <= 9 && buf) *p++ = (char)(digval + '0');
		size++;
	}	while (val > 0);

	if (buf == NULL) {
		return size;
	}

	*p-- = '\0';
	do { 
		temp = *p;
		*p = *firstdig;
		*firstdig = temp;
		--p;
		++firstdig;
	}	while (firstdig < p);

	return 0;
}


IINT32 cz_strtol(const char *nptr, const char **endptr, int ibase)
{
	return (IINT32)_cz_strtoxl(nptr, endptr, ibase, 0);
}

IUINT32 cz_strtoul(const char *nptr, const char **endptr, int ibase)
{
	return _cz_strtoxl(nptr, endptr, ibase, IFL_UNSIGNED);
}


char* cz_ltoa(IINT32 val, char *buf, int radix)
{
	IINT32 mval = val;
	_cz_xtoa((IUINT32)mval, buf, (unsigned)radix, (val < 0)? 1 : 0);
	return buf;
}

char* cz_ultoa(IUINT32 val, char *buf, int radix)
{
	IUINT32 mval = (IUINT32)val;
	_cz_xtoa(mval, buf, (unsigned)radix, 0);
	return buf;
}


IINT32 cz_atoi(const char *s)
{
	return cz_strtol(s, NULL, 0);
}


IUINT32 cz_crand(IUINT32 *seed)
{
	IUINT32 xseed = *seed;
#if 1
	xseed = (cz_uint32_mul(xseed, 1103515245U) + 12345U) & CZ_INT32_MAX;
	seed[0] = xseed;
#else
	xseed = (cz_uint32_mul(xseed, 12345U) + 2531011L) & CZ_INT32_MAX;
	seed[0] = xseed;
#endif
	return xseed >> 16;
}

IUINT32 cz_crandom(IUINT32 num, IUINT32 *seed) 
{
	IUINT32 x = cz_crand(seed);
	IUINT32 y = cz_crand(seed);
	IUINT32 z = ((x << 16) & 0xffff0000ul) | (y & 0xfffful);
	IUINT32 rem;
	cz_uint32_div(z, num, &rem);
	return rem;
}


static IUINT32 cz_random_seed = 0x11223344;

void cz_srand(int seed)
{
	cz_random_seed = (IUINT32)seed;
}

int cz_rand(void)
{
	IUINT32 x = cz_crand(&cz_random_seed);
	IUINT32 y = cz_crand(&cz_random_seed);
	IUINT32 z = ((x << 16) & 0xffff0000ul) | (y & 0xfffful);
	return (int)z;
}


int cz_random(int num)
{
	return (int)cz_crandom((IUINT32)num, &cz_random_seed);
}



