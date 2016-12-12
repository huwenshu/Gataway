#ifndef _3DES_H_
#define _3DES_H_

#include "config.h"

unsigned char _MD5_code[7]= {0};

#define DES_LONG unsigned long
#define LEN_OF_KEY 24

#define ITERATIONS 16

#define c2l(c,l)        (l =((DES_LONG)(*((c)++)))    , \
			l|=((DES_LONG)(*((c)++)))<< 8L, \
			l|=((DES_LONG)(*((c)++)))<<16L, \
			l|=((DES_LONG)(*((c)++)))<<24L)


#define l2c(l,c)        (*((c)++)=(uint8_t)(((l)     )&0xff), \
			*((c)++)=(uint8_t)(((l)>> 8L)&0xff), \
			*((c)++)=(uint8_t)(((l)>>16L)&0xff), \
			*((c)++)=(uint8_t)(((l)>>24L)&0xff))

#define ROTATE(a,n)     (((a)>>(n))+((a)<<(32-(n))))

#define LOAD_DATA_tmp(a,b,c,d,e,f) LOAD_DATA(a,b,c,d,e,f,g)
#define LOAD_DATA(R,S,u,t,E0,E1,tmp) \
	u=R^s[S  ]; \
t=R^s[S+1]

#define D_ENCRYPT(LL,R,S) {\
	LOAD_DATA_tmp(R,S,u,t,E0,E1); \
	t=ROTATE(t,4); \
	LL^=\
	DES_SPtrans[0][(u>> 2L)&0x3f]^ \
	DES_SPtrans[2][(u>>10L)&0x3f]^ \
	DES_SPtrans[4][(u>>18L)&0x3f]^ \
	DES_SPtrans[6][(u>>26L)&0x3f]^ \
	DES_SPtrans[1][(t>> 2L)&0x3f]^ \
	DES_SPtrans[3][(t>>10L)&0x3f]^ \
	DES_SPtrans[5][(t>>18L)&0x3f]^ \
	DES_SPtrans[7][(t>>26L)&0x3f]; }

#define PERM_OP(a,b,t,n,m) ((t)=((((a)>>(n))^(b))&(m)),\
			(b)^=(t),\
			(a)^=((t)<<(n)))

#define IP(l,r) \
{ \
	register DES_LONG tt; \
	PERM_OP(r,l,tt, 4,0x0f0f0f0fL); \
	PERM_OP(l,r,tt,16,0x0000ffffL); \
	PERM_OP(r,l,tt, 2,0x33333333L); \
	PERM_OP(l,r,tt, 8,0x00ff00ffL); \
	PERM_OP(r,l,tt, 1,0x55555555L); \
}

#define FP(l,r) \
{ \
	register DES_LONG tt; \
	PERM_OP(l,r,tt, 1,0x55555555L); \
	PERM_OP(r,l,tt, 8,0x00ff00ffL); \
	PERM_OP(l,r,tt, 2,0x33333333L); \
	PERM_OP(r,l,tt,16,0x0000ffffL); \
	PERM_OP(l,r,tt, 4,0x0f0f0f0fL); \
}

extern const DES_LONG DES_SPtrans[8][64];

#define HPERM_OP(a,t,n,m) ((t)=((((a)<<(16-(n)))^(a))&(m)),\
			(a)=(a)^(t)^(t>>(16-(n))))

static const DES_LONG des_skb[8][64] = {
	{
		/* for C bits (numbered as per FIPS 46) 1 2 3 4 5 6 */
		0x00000000L, 0x00000010L, 0x20000000L, 0x20000010L,
		0x00010000L, 0x00010010L, 0x20010000L, 0x20010010L,
		0x00000800L, 0x00000810L, 0x20000800L, 0x20000810L,
		0x00010800L, 0x00010810L, 0x20010800L, 0x20010810L,
		0x00000020L, 0x00000030L, 0x20000020L, 0x20000030L,
		0x00010020L, 0x00010030L, 0x20010020L, 0x20010030L,
		0x00000820L, 0x00000830L, 0x20000820L, 0x20000830L,
		0x00010820L, 0x00010830L, 0x20010820L, 0x20010830L,
		0x00080000L, 0x00080010L, 0x20080000L, 0x20080010L,
		0x00090000L, 0x00090010L, 0x20090000L, 0x20090010L,
		0x00080800L, 0x00080810L, 0x20080800L, 0x20080810L,
		0x00090800L, 0x00090810L, 0x20090800L, 0x20090810L,
		0x00080020L, 0x00080030L, 0x20080020L, 0x20080030L,
		0x00090020L, 0x00090030L, 0x20090020L, 0x20090030L,
		0x00080820L, 0x00080830L, 0x20080820L, 0x20080830L,
		0x00090820L, 0x00090830L, 0x20090820L, 0x20090830L,
	},
	{
		/* for C bits (numbered as per FIPS 46) 7 8 10 11 12 13 */
		0x00000000L, 0x02000000L, 0x00002000L, 0x02002000L,
		0x00200000L, 0x02200000L, 0x00202000L, 0x02202000L,
		0x00000004L, 0x02000004L, 0x00002004L, 0x02002004L,
		0x00200004L, 0x02200004L, 0x00202004L, 0x02202004L,
		0x00000400L, 0x02000400L, 0x00002400L, 0x02002400L,
		0x00200400L, 0x02200400L, 0x00202400L, 0x02202400L,
		0x00000404L, 0x02000404L, 0x00002404L, 0x02002404L,
		0x00200404L, 0x02200404L, 0x00202404L, 0x02202404L,
		0x10000000L, 0x12000000L, 0x10002000L, 0x12002000L,
		0x10200000L, 0x12200000L, 0x10202000L, 0x12202000L,
		0x10000004L, 0x12000004L, 0x10002004L, 0x12002004L,
		0x10200004L, 0x12200004L, 0x10202004L, 0x12202004L,
		0x10000400L, 0x12000400L, 0x10002400L, 0x12002400L,
		0x10200400L, 0x12200400L, 0x10202400L, 0x12202400L,
		0x10000404L, 0x12000404L, 0x10002404L, 0x12002404L,
		0x10200404L, 0x12200404L, 0x10202404L, 0x12202404L,
	},
	{
		/* for C bits (numbered as per FIPS 46) 14 15 16 17 19 20 */
		0x00000000L, 0x00000001L, 0x00040000L, 0x00040001L,
		0x01000000L, 0x01000001L, 0x01040000L, 0x01040001L,
		0x00000002L, 0x00000003L, 0x00040002L, 0x00040003L,
		0x01000002L, 0x01000003L, 0x01040002L, 0x01040003L,
		0x00000200L, 0x00000201L, 0x00040200L, 0x00040201L,
		0x01000200L, 0x01000201L, 0x01040200L, 0x01040201L,
		0x00000202L, 0x00000203L, 0x00040202L, 0x00040203L,
		0x01000202L, 0x01000203L, 0x01040202L, 0x01040203L,
		0x08000000L, 0x08000001L, 0x08040000L, 0x08040001L,
		0x09000000L, 0x09000001L, 0x09040000L, 0x09040001L,
		0x08000002L, 0x08000003L, 0x08040002L, 0x08040003L,
		0x09000002L, 0x09000003L, 0x09040002L, 0x09040003L,
		0x08000200L, 0x08000201L, 0x08040200L, 0x08040201L,
		0x09000200L, 0x09000201L, 0x09040200L, 0x09040201L,
		0x08000202L, 0x08000203L, 0x08040202L, 0x08040203L,
		0x09000202L, 0x09000203L, 0x09040202L, 0x09040203L,
	},
	{
		/* for C bits (numbered as per FIPS 46) 21 23 24 26 27 28 */
		0x00000000L, 0x00100000L, 0x00000100L, 0x00100100L,
		0x00000008L, 0x00100008L, 0x00000108L, 0x00100108L,
		0x00001000L, 0x00101000L, 0x00001100L, 0x00101100L,
		0x00001008L, 0x00101008L, 0x00001108L, 0x00101108L,
		0x04000000L, 0x04100000L, 0x04000100L, 0x04100100L,
		0x04000008L, 0x04100008L, 0x04000108L, 0x04100108L,
		0x04001000L, 0x04101000L, 0x04001100L, 0x04101100L,
		0x04001008L, 0x04101008L, 0x04001108L, 0x04101108L,
		0x00020000L, 0x00120000L, 0x00020100L, 0x00120100L,
		0x00020008L, 0x00120008L, 0x00020108L, 0x00120108L,
		0x00021000L, 0x00121000L, 0x00021100L, 0x00121100L,
		0x00021008L, 0x00121008L, 0x00021108L, 0x00121108L,
		0x04020000L, 0x04120000L, 0x04020100L, 0x04120100L,
		0x04020008L, 0x04120008L, 0x04020108L, 0x04120108L,
		0x04021000L, 0x04121000L, 0x04021100L, 0x04121100L,
		0x04021008L, 0x04121008L, 0x04021108L, 0x04121108L,
	},
	{
		/* for D bits (numbered as per FIPS 46) 1 2 3 4 5 6 */
		0x00000000L, 0x10000000L, 0x00010000L, 0x10010000L,
		0x00000004L, 0x10000004L, 0x00010004L, 0x10010004L,
		0x20000000L, 0x30000000L, 0x20010000L, 0x30010000L,
		0x20000004L, 0x30000004L, 0x20010004L, 0x30010004L,
		0x00100000L, 0x10100000L, 0x00110000L, 0x10110000L,
		0x00100004L, 0x10100004L, 0x00110004L, 0x10110004L,
		0x20100000L, 0x30100000L, 0x20110000L, 0x30110000L,
		0x20100004L, 0x30100004L, 0x20110004L, 0x30110004L,
		0x00001000L, 0x10001000L, 0x00011000L, 0x10011000L,
		0x00001004L, 0x10001004L, 0x00011004L, 0x10011004L,
		0x20001000L, 0x30001000L, 0x20011000L, 0x30011000L,
		0x20001004L, 0x30001004L, 0x20011004L, 0x30011004L,
		0x00101000L, 0x10101000L, 0x00111000L, 0x10111000L,
		0x00101004L, 0x10101004L, 0x00111004L, 0x10111004L,
		0x20101000L, 0x30101000L, 0x20111000L, 0x30111000L,
		0x20101004L, 0x30101004L, 0x20111004L, 0x30111004L,
	},
	{
		/* for D bits (numbered as per FIPS 46) 8 9 11 12 13 14 */
		0x00000000L, 0x08000000L, 0x00000008L, 0x08000008L,
		0x00000400L, 0x08000400L, 0x00000408L, 0x08000408L,
		0x00020000L, 0x08020000L, 0x00020008L, 0x08020008L,
		0x00020400L, 0x08020400L, 0x00020408L, 0x08020408L,
		0x00000001L, 0x08000001L, 0x00000009L, 0x08000009L,
		0x00000401L, 0x08000401L, 0x00000409L, 0x08000409L,
		0x00020001L, 0x08020001L, 0x00020009L, 0x08020009L,
		0x00020401L, 0x08020401L, 0x00020409L, 0x08020409L,
		0x02000000L, 0x0A000000L, 0x02000008L, 0x0A000008L,
		0x02000400L, 0x0A000400L, 0x02000408L, 0x0A000408L,
		0x02020000L, 0x0A020000L, 0x02020008L, 0x0A020008L,
		0x02020400L, 0x0A020400L, 0x02020408L, 0x0A020408L,
		0x02000001L, 0x0A000001L, 0x02000009L, 0x0A000009L,
		0x02000401L, 0x0A000401L, 0x02000409L, 0x0A000409L,
		0x02020001L, 0x0A020001L, 0x02020009L, 0x0A020009L,
		0x02020401L, 0x0A020401L, 0x02020409L, 0x0A020409L,
	},
	{
		/* for D bits (numbered as per FIPS 46) 16 17 18 19 20 21 */
		0x00000000L, 0x00000100L, 0x00080000L, 0x00080100L,
		0x01000000L, 0x01000100L, 0x01080000L, 0x01080100L,
		0x00000010L, 0x00000110L, 0x00080010L, 0x00080110L,
		0x01000010L, 0x01000110L, 0x01080010L, 0x01080110L,
		0x00200000L, 0x00200100L, 0x00280000L, 0x00280100L,
		0x01200000L, 0x01200100L, 0x01280000L, 0x01280100L,
		0x00200010L, 0x00200110L, 0x00280010L, 0x00280110L,
		0x01200010L, 0x01200110L, 0x01280010L, 0x01280110L,
		0x00000200L, 0x00000300L, 0x00080200L, 0x00080300L,
		0x01000200L, 0x01000300L, 0x01080200L, 0x01080300L,
		0x00000210L, 0x00000310L, 0x00080210L, 0x00080310L,
		0x01000210L, 0x01000310L, 0x01080210L, 0x01080310L,
		0x00200200L, 0x00200300L, 0x00280200L, 0x00280300L,
		0x01200200L, 0x01200300L, 0x01280200L, 0x01280300L,
		0x00200210L, 0x00200310L, 0x00280210L, 0x00280310L,
		0x01200210L, 0x01200310L, 0x01280210L, 0x01280310L,
	},
	{
		/* for D bits (numbered as per FIPS 46) 22 23 24 25 27 28 */
		0x00000000L, 0x04000000L, 0x00040000L, 0x04040000L,
		0x00000002L, 0x04000002L, 0x00040002L, 0x04040002L,
		0x00002000L, 0x04002000L, 0x00042000L, 0x04042000L,
		0x00002002L, 0x04002002L, 0x00042002L, 0x04042002L,
		0x00000020L, 0x04000020L, 0x00040020L, 0x04040020L,
		0x00000022L, 0x04000022L, 0x00040022L, 0x04040022L,
		0x00002020L, 0x04002020L, 0x00042020L, 0x04042020L,
		0x00002022L, 0x04002022L, 0x00042022L, 0x04042022L,
		0x00000800L, 0x04000800L, 0x00040800L, 0x04040800L,
		0x00000802L, 0x04000802L, 0x00040802L, 0x04040802L,
		0x00002800L, 0x04002800L, 0x00042800L, 0x04042800L,
		0x00002802L, 0x04002802L, 0x00042802L, 0x04042802L,
		0x00000820L, 0x04000820L, 0x00040820L, 0x04040820L,
		0x00000822L, 0x04000822L, 0x00040822L, 0x04040822L,
		0x00002820L, 0x04002820L, 0x00042820L, 0x04042820L,
		0x00002822L, 0x04002822L, 0x00042822L, 0x04042822L,
	}
};

const DES_LONG DES_SPtrans[8][64] = {
	{
		/* nibble 0 */
		0x02080800L, 0x00080000L, 0x02000002L, 0x02080802L,
		0x02000000L, 0x00080802L, 0x00080002L, 0x02000002L,
		0x00080802L, 0x02080800L, 0x02080000L, 0x00000802L,
		0x02000802L, 0x02000000L, 0x00000000L, 0x00080002L,
		0x00080000L, 0x00000002L, 0x02000800L, 0x00080800L,
		0x02080802L, 0x02080000L, 0x00000802L, 0x02000800L,
		0x00000002L, 0x00000800L, 0x00080800L, 0x02080002L,
		0x00000800L, 0x02000802L, 0x02080002L, 0x00000000L,
		0x00000000L, 0x02080802L, 0x02000800L, 0x00080002L,
		0x02080800L, 0x00080000L, 0x00000802L, 0x02000800L,
		0x02080002L, 0x00000800L, 0x00080800L, 0x02000002L,
		0x00080802L, 0x00000002L, 0x02000002L, 0x02080000L,
		0x02080802L, 0x00080800L, 0x02080000L, 0x02000802L,
		0x02000000L, 0x00000802L, 0x00080002L, 0x00000000L,
		0x00080000L, 0x02000000L, 0x02000802L, 0x02080800L,
		0x00000002L, 0x02080002L, 0x00000800L, 0x00080802L,
	},
	{
		/* nibble 1 */
		0x40108010L, 0x00000000L, 0x00108000L, 0x40100000L,
		0x40000010L, 0x00008010L, 0x40008000L, 0x00108000L,
		0x00008000L, 0x40100010L, 0x00000010L, 0x40008000L,
		0x00100010L, 0x40108000L, 0x40100000L, 0x00000010L,
		0x00100000L, 0x40008010L, 0x40100010L, 0x00008000L,
		0x00108010L, 0x40000000L, 0x00000000L, 0x00100010L,
		0x40008010L, 0x00108010L, 0x40108000L, 0x40000010L,
		0x40000000L, 0x00100000L, 0x00008010L, 0x40108010L,
		0x00100010L, 0x40108000L, 0x40008000L, 0x00108010L,
		0x40108010L, 0x00100010L, 0x40000010L, 0x00000000L,
		0x40000000L, 0x00008010L, 0x00100000L, 0x40100010L,
		0x00008000L, 0x40000000L, 0x00108010L, 0x40008010L,
		0x40108000L, 0x00008000L, 0x00000000L, 0x40000010L,
		0x00000010L, 0x40108010L, 0x00108000L, 0x40100000L,
		0x40100010L, 0x00100000L, 0x00008010L, 0x40008000L,
		0x40008010L, 0x00000010L, 0x40100000L, 0x00108000L,
	},
	{
		/* nibble 2 */
		0x04000001L, 0x04040100L, 0x00000100L, 0x04000101L,
		0x00040001L, 0x04000000L, 0x04000101L, 0x00040100L,
		0x04000100L, 0x00040000L, 0x04040000L, 0x00000001L,
		0x04040101L, 0x00000101L, 0x00000001L, 0x04040001L,
		0x00000000L, 0x00040001L, 0x04040100L, 0x00000100L,
		0x00000101L, 0x04040101L, 0x00040000L, 0x04000001L,
		0x04040001L, 0x04000100L, 0x00040101L, 0x04040000L,
		0x00040100L, 0x00000000L, 0x04000000L, 0x00040101L,
		0x04040100L, 0x00000100L, 0x00000001L, 0x00040000L,
		0x00000101L, 0x00040001L, 0x04040000L, 0x04000101L,
		0x00000000L, 0x04040100L, 0x00040100L, 0x04040001L,
		0x00040001L, 0x04000000L, 0x04040101L, 0x00000001L,
		0x00040101L, 0x04000001L, 0x04000000L, 0x04040101L,
		0x00040000L, 0x04000100L, 0x04000101L, 0x00040100L,
		0x04000100L, 0x00000000L, 0x04040001L, 0x00000101L,
		0x04000001L, 0x00040101L, 0x00000100L, 0x04040000L,
	},
	{
		/* nibble 3 */
		0x00401008L, 0x10001000L, 0x00000008L, 0x10401008L,
		0x00000000L, 0x10400000L, 0x10001008L, 0x00400008L,
		0x10401000L, 0x10000008L, 0x10000000L, 0x00001008L,
		0x10000008L, 0x00401008L, 0x00400000L, 0x10000000L,
		0x10400008L, 0x00401000L, 0x00001000L, 0x00000008L,
		0x00401000L, 0x10001008L, 0x10400000L, 0x00001000L,
		0x00001008L, 0x00000000L, 0x00400008L, 0x10401000L,
		0x10001000L, 0x10400008L, 0x10401008L, 0x00400000L,
		0x10400008L, 0x00001008L, 0x00400000L, 0x10000008L,
		0x00401000L, 0x10001000L, 0x00000008L, 0x10400000L,
		0x10001008L, 0x00000000L, 0x00001000L, 0x00400008L,
		0x00000000L, 0x10400008L, 0x10401000L, 0x00001000L,
		0x10000000L, 0x10401008L, 0x00401008L, 0x00400000L,
		0x10401008L, 0x00000008L, 0x10001000L, 0x00401008L,
		0x00400008L, 0x00401000L, 0x10400000L, 0x10001008L,
		0x00001008L, 0x10000000L, 0x10000008L, 0x10401000L,
	},
	{
		/* nibble 4 */
		0x08000000L, 0x00010000L, 0x00000400L, 0x08010420L,
		0x08010020L, 0x08000400L, 0x00010420L, 0x08010000L,
		0x00010000L, 0x00000020L, 0x08000020L, 0x00010400L,
		0x08000420L, 0x08010020L, 0x08010400L, 0x00000000L,
		0x00010400L, 0x08000000L, 0x00010020L, 0x00000420L,
		0x08000400L, 0x00010420L, 0x00000000L, 0x08000020L,
		0x00000020L, 0x08000420L, 0x08010420L, 0x00010020L,
		0x08010000L, 0x00000400L, 0x00000420L, 0x08010400L,
		0x08010400L, 0x08000420L, 0x00010020L, 0x08010000L,
		0x00010000L, 0x00000020L, 0x08000020L, 0x08000400L,
		0x08000000L, 0x00010400L, 0x08010420L, 0x00000000L,
		0x00010420L, 0x08000000L, 0x00000400L, 0x00010020L,
		0x08000420L, 0x00000400L, 0x00000000L, 0x08010420L,
		0x08010020L, 0x08010400L, 0x00000420L, 0x00010000L,
		0x00010400L, 0x08010020L, 0x08000400L, 0x00000420L,
		0x00000020L, 0x00010420L, 0x08010000L, 0x08000020L,
	},
	{
		/* nibble 5 */
		0x80000040L, 0x00200040L, 0x00000000L, 0x80202000L,
		0x00200040L, 0x00002000L, 0x80002040L, 0x00200000L,
		0x00002040L, 0x80202040L, 0x00202000L, 0x80000000L,
		0x80002000L, 0x80000040L, 0x80200000L, 0x00202040L,
		0x00200000L, 0x80002040L, 0x80200040L, 0x00000000L,
		0x00002000L, 0x00000040L, 0x80202000L, 0x80200040L,
		0x80202040L, 0x80200000L, 0x80000000L, 0x00002040L,
		0x00000040L, 0x00202000L, 0x00202040L, 0x80002000L,
		0x00002040L, 0x80000000L, 0x80002000L, 0x00202040L,
		0x80202000L, 0x00200040L, 0x00000000L, 0x80002000L,
		0x80000000L, 0x00002000L, 0x80200040L, 0x00200000L,
		0x00200040L, 0x80202040L, 0x00202000L, 0x00000040L,
		0x80202040L, 0x00202000L, 0x00200000L, 0x80002040L,
		0x80000040L, 0x80200000L, 0x00202040L, 0x00000000L,
		0x00002000L, 0x80000040L, 0x80002040L, 0x80202000L,
		0x80200000L, 0x00002040L, 0x00000040L, 0x80200040L,
	},
	{
		/* nibble 6 */
		0x00004000L, 0x00000200L, 0x01000200L, 0x01000004L,
		0x01004204L, 0x00004004L, 0x00004200L, 0x00000000L,
		0x01000000L, 0x01000204L, 0x00000204L, 0x01004000L,
		0x00000004L, 0x01004200L, 0x01004000L, 0x00000204L,
		0x01000204L, 0x00004000L, 0x00004004L, 0x01004204L,
		0x00000000L, 0x01000200L, 0x01000004L, 0x00004200L,
		0x01004004L, 0x00004204L, 0x01004200L, 0x00000004L,
		0x00004204L, 0x01004004L, 0x00000200L, 0x01000000L,
		0x00004204L, 0x01004000L, 0x01004004L, 0x00000204L,
		0x00004000L, 0x00000200L, 0x01000000L, 0x01004004L,
		0x01000204L, 0x00004204L, 0x00004200L, 0x00000000L,
		0x00000200L, 0x01000004L, 0x00000004L, 0x01000200L,
		0x00000000L, 0x01000204L, 0x01000200L, 0x00004200L,
		0x00000204L, 0x00004000L, 0x01004204L, 0x01000000L,
		0x01004200L, 0x00000004L, 0x00004004L, 0x01004204L,
		0x01000004L, 0x01004200L, 0x01004000L, 0x00004004L,
	},
	{
		/* nibble 7 */
		0x20800080L, 0x20820000L, 0x00020080L, 0x00000000L,
		0x20020000L, 0x00800080L, 0x20800000L, 0x20820080L,
		0x00000080L, 0x20000000L, 0x00820000L, 0x00020080L,
		0x00820080L, 0x20020080L, 0x20000080L, 0x20800000L,
		0x00020000L, 0x00820080L, 0x00800080L, 0x20020000L,
		0x20820080L, 0x20000080L, 0x00000000L, 0x00820000L,
		0x20000000L, 0x00800000L, 0x20020080L, 0x20800080L,
		0x00800000L, 0x00020000L, 0x20820000L, 0x00000080L,
		0x00800000L, 0x00020000L, 0x20000080L, 0x20820080L,
		0x00020080L, 0x20000000L, 0x00000000L, 0x00820000L,
		0x20800080L, 0x20020080L, 0x20020000L, 0x00800080L,
		0x20820000L, 0x00000080L, 0x00800080L, 0x20020000L,
		0x20820080L, 0x00800000L, 0x20800000L, 0x20000080L,
		0x00820000L, 0x00020080L, 0x20020080L, 0x20800000L,
		0x00000080L, 0x20820000L, 0x00820080L, 0x00000000L,
		0x20000000L, 0x20800080L, 0x00020000L, 0x00820080L,
	}
};


typedef unsigned char DES_cblock[8];
typedef /* const */ uint8_t const_DES_cblock[8];


typedef struct DES_ks {
	union {
		DES_cblock cblock;
		/*
		 * make sure things are correct size on machines with 8 byte longs
		 */
		DES_LONG deslong[2];
	} ks[16];
} DES_key_schedule;



#define DES_ENCRYPT     1
#define DES_DECRYPT     0

void add_secret(uint8_t *buf, uint8_t *encryption_buff);

void DES_ecb3_encrypt(const_DES_cblock *input, DES_cblock *output,
                      DES_key_schedule *ks1, DES_key_schedule *ks2,
                      DES_key_schedule *ks3, int enc);

void Decryption(uint8_t* buf, uint8_t* decryption_buff);

void DES_encrypt1(DES_LONG *data, DES_key_schedule *ks, int enc);

void DES_encrypt2(DES_LONG *data, DES_key_schedule *ks, int enc);

void DES_encrypt3(DES_LONG *data, DES_key_schedule *ks1,
                  DES_key_schedule *ks2, DES_key_schedule *ks3);
void DES_decrypt3(DES_LONG *data, DES_key_schedule *ks1,
                  DES_key_schedule *ks2, DES_key_schedule *ks3);

void DES_set_key_unchecked(const_DES_cblock *key, DES_key_schedule *schedule);

extern int setTime(uint8_t* buf);

#endif
