#ifndef JUTIL_MD5_HPP
#define JUTIL_MD5_HPP

#include <stdint.h>

/* F, G and H are basic MD5 functions: selection, majority, parity */
#define JUTIL_MD5_F(x, y, z) (((x) & (y)) | ((~x) & (z)))
#define JUTIL_MD5_G(x, y, z) (((x) & (z)) | ((y) & (~z)))
#define JUTIL_MD5_H(x, y, z) ((x) ^ (y) ^ (z))
#define JUTIL_MD5_I(x, y, z) ((y) ^ ((x) | (~z))) 

/* ROTATE_LEFT rotates x left n bits */
#define JUTIL_MD5_ROTATE_LEFT(x, n) (((x) << (n)) | ((x) >> (32-(n))))

/* FF, GG, HH, and II transformations for rounds 1, 2, 3, and 4 */
/* Rotation is separate from addition to prevent recomputation */
#define JUTIL_MD5_FF(a, b, c, d, x, s, ac) \
	{(a) += JUTIL_MD5_F ((b), (c), (d)) + (x) + (uint32_t)(ac); \
	(a) = JUTIL_MD5_ROTATE_LEFT ((a), (s)); \
	(a) += (b); \
	}
#define JUTIL_MD5_GG(a, b, c, d, x, s, ac) \
	{(a) += JUTIL_MD5_G ((b), (c), (d)) + (x) + (uint32_t)(ac); \
	(a) = JUTIL_MD5_ROTATE_LEFT ((a), (s)); \
	(a) += (b); \
	}
#define JUTIL_MD5_HH(a, b, c, d, x, s, ac) \
	{(a) += JUTIL_MD5_H ((b), (c), (d)) + (x) + (uint32_t)(ac); \
	(a) = JUTIL_MD5_ROTATE_LEFT ((a), (s)); \
	(a) += (b); \
	}
#define JUTIL_MD5_II(a, b, c, d, x, s, ac) \
	{(a) += JUTIL_MD5_I ((b), (c), (d)) + (x) + (uint32_t)(ac); \
	(a) = JUTIL_MD5_ROTATE_LEFT ((a), (s)); \
	(a) += (b); \
	}
#define JUTIL_MD5_S11 7
#define JUTIL_MD5_S12 12
#define JUTIL_MD5_S13 17
#define JUTIL_MD5_S14 22
#define JUTIL_MD5_S21 5
#define JUTIL_MD5_S22 9
#define JUTIL_MD5_S23 14
#define JUTIL_MD5_S24 20
#define JUTIL_MD5_S31 4
#define JUTIL_MD5_S32 11
#define JUTIL_MD5_S33 16
#define JUTIL_MD5_S34 23
#define JUTIL_MD5_S41 6
#define JUTIL_MD5_S42 10
#define JUTIL_MD5_S43 15
#define JUTIL_MD5_S44 21

namespace JUTIL
{

	/*
	 * Based on MD5 reference implementaion.
	 */
	class MD5
	{

	public:

		static const unsigned int HASH_SIZE = 16;

		/* Data structure for MD5 (Message Digest) computation */
		typedef struct {
			uint32_t i[2];                /* number of _bits_ handled mod 2^64 */
			uint32_t buf[4];                                 /* scratch buffer */
			unsigned char in[64];                              /* input buffer */
			unsigned char digest[16];     /* actual digest after MD5Final call */
		} MD5_CTX;

		/* forward declaration */
		static void MD5Init ();
		static void MD5Update ();
		static void MD5Final ();
		static void Transform ();

		static void MD5Init (MD5_CTX *mdContext)
		{
			mdContext->i[0] = mdContext->i[1] = (uint32_t)0;

			/* Load magic initialization constants.
				*/
			mdContext->buf[0] = (uint32_t)0x67452301;
			mdContext->buf[1] = (uint32_t)0xefcdab89;
			mdContext->buf[2] = (uint32_t)0x98badcfe;
			mdContext->buf[3] = (uint32_t)0x10325476;
		}

		//static void MD5Update (MD5_CTX *mdContext, unsigned char *inBuf, unsigned int inLen)
		static void MD5Update (MD5_CTX *mdContext, const unsigned char *inBuf, unsigned int inLen)
		{
			uint32_t in[16];
			int mdi;
			unsigned int i, ii;

			/* compute number of bytes mod 64 */
			mdi = (int)((mdContext->i[0] >> 3) & 0x3F);

			/* update number of bits */
			if ((mdContext->i[0] + ((uint32_t)inLen << 3)) < mdContext->i[0])
				mdContext->i[1]++;
			mdContext->i[0] += ((uint32_t)inLen << 3);
			mdContext->i[1] += ((uint32_t)inLen >> 29);

			while (inLen--) {
				/* add new character to buffer, increment mdi */
				mdContext->in[mdi++] = *inBuf++;

				/* transform if necessary */
				if (mdi == 0x40) {
					for (i = 0, ii = 0; i < 16; i++, ii += 4)
						in[i] = (((uint32_t)mdContext->in[ii+3]) << 24) |
										(((uint32_t)mdContext->in[ii+2]) << 16) |
										(((uint32_t)mdContext->in[ii+1]) << 8) |
										((uint32_t)mdContext->in[ii]);
					Transform (mdContext->buf, in);
					mdi = 0;
				}
			}
		}

		static void MD5Final (MD5_CTX *mdContext)
		{
			uint32_t in[16];
			int mdi;
			unsigned int i, ii;
			unsigned int padLen;

			/* save number of bits */
			in[14] = mdContext->i[0];
			in[15] = mdContext->i[1];

			/* compute number of bytes mod 64 */
			mdi = (int)((mdContext->i[0] >> 3) & 0x3F);

			/* pad out to 56 mod 64 */
			static const unsigned char PADDING[64] = {
				0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
				0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
				0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
				0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
				0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
				0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
				0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
				0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
			};
			padLen = (mdi < 56) ? (56 - mdi) : (120 - mdi);
			MD5Update (mdContext, PADDING, padLen);

			/* append length in bits and transform */
			for (i = 0, ii = 0; i < 14; i++, ii += 4)
				in[i] = (((uint32_t)mdContext->in[ii+3]) << 24) |
								(((uint32_t)mdContext->in[ii+2]) << 16) |
								(((uint32_t)mdContext->in[ii+1]) << 8) |
								((uint32_t)mdContext->in[ii]);
			Transform (mdContext->buf, in);

			/* store buffer in digest */
			for (i = 0, ii = 0; i < 4; i++, ii += 4) {
				mdContext->digest[ii] = (unsigned char)(mdContext->buf[i] & 0xFF);
				mdContext->digest[ii+1] =
					(unsigned char)((mdContext->buf[i] >> 8) & 0xFF);
				mdContext->digest[ii+2] =
					(unsigned char)((mdContext->buf[i] >> 16) & 0xFF);
				mdContext->digest[ii+3] =
					(unsigned char)((mdContext->buf[i] >> 24) & 0xFF);
			}
		}

		/* Basic MD5 step. Transform buf based on in.
			*/
		static void Transform (uint32_t *buf, uint32_t *in)
		{
			uint32_t a = buf[0], b = buf[1], c = buf[2], d = buf[3];

			/* Round 1 */
			JUTIL_MD5_FF ( a, b, c, d, in[ 0], JUTIL_MD5_S11, 3614090360); /* 1 */
			JUTIL_MD5_FF ( d, a, b, c, in[ 1], JUTIL_MD5_S12, 3905402710); /* 2 */
			JUTIL_MD5_FF ( c, d, a, b, in[ 2], JUTIL_MD5_S13,  606105819); /* 3 */
			JUTIL_MD5_FF ( b, c, d, a, in[ 3], JUTIL_MD5_S14, 3250441966); /* 4 */
			JUTIL_MD5_FF ( a, b, c, d, in[ 4], JUTIL_MD5_S11, 4118548399); /* 5 */
			JUTIL_MD5_FF ( d, a, b, c, in[ 5], JUTIL_MD5_S12, 1200080426); /* 6 */
			JUTIL_MD5_FF ( c, d, a, b, in[ 6], JUTIL_MD5_S13, 2821735955); /* 7 */
			JUTIL_MD5_FF ( b, c, d, a, in[ 7], JUTIL_MD5_S14, 4249261313); /* 8 */
			JUTIL_MD5_FF ( a, b, c, d, in[ 8], JUTIL_MD5_S11, 1770035416); /* 9 */
			JUTIL_MD5_FF ( d, a, b, c, in[ 9], JUTIL_MD5_S12, 2336552879); /* 10 */
			JUTIL_MD5_FF ( c, d, a, b, in[10], JUTIL_MD5_S13, 4294925233); /* 11 */
			JUTIL_MD5_FF ( b, c, d, a, in[11], JUTIL_MD5_S14, 2304563134); /* 12 */
			JUTIL_MD5_FF ( a, b, c, d, in[12], JUTIL_MD5_S11, 1804603682); /* 13 */
			JUTIL_MD5_FF ( d, a, b, c, in[13], JUTIL_MD5_S12, 4254626195); /* 14 */
			JUTIL_MD5_FF ( c, d, a, b, in[14], JUTIL_MD5_S13, 2792965006); /* 15 */
			JUTIL_MD5_FF ( b, c, d, a, in[15], JUTIL_MD5_S14, 1236535329); /* 16 */

			/* Round 2 */
			JUTIL_MD5_GG ( a, b, c, d, in[ 1], JUTIL_MD5_S21, 4129170786); /* 17 */
			JUTIL_MD5_GG ( d, a, b, c, in[ 6], JUTIL_MD5_S22, 3225465664); /* 18 */
			JUTIL_MD5_GG ( c, d, a, b, in[11], JUTIL_MD5_S23,  643717713); /* 19 */
			JUTIL_MD5_GG ( b, c, d, a, in[ 0], JUTIL_MD5_S24, 3921069994); /* 20 */
			JUTIL_MD5_GG ( a, b, c, d, in[ 5], JUTIL_MD5_S21, 3593408605); /* 21 */
			JUTIL_MD5_GG ( d, a, b, c, in[10], JUTIL_MD5_S22,   38016083); /* 22 */
			JUTIL_MD5_GG ( c, d, a, b, in[15], JUTIL_MD5_S23, 3634488961); /* 23 */
			JUTIL_MD5_GG ( b, c, d, a, in[ 4], JUTIL_MD5_S24, 3889429448); /* 24 */
			JUTIL_MD5_GG ( a, b, c, d, in[ 9], JUTIL_MD5_S21,  568446438); /* 25 */
			JUTIL_MD5_GG ( d, a, b, c, in[14], JUTIL_MD5_S22, 3275163606); /* 26 */
			JUTIL_MD5_GG ( c, d, a, b, in[ 3], JUTIL_MD5_S23, 4107603335); /* 27 */
			JUTIL_MD5_GG ( b, c, d, a, in[ 8], JUTIL_MD5_S24, 1163531501); /* 28 */
			JUTIL_MD5_GG ( a, b, c, d, in[13], JUTIL_MD5_S21, 2850285829); /* 29 */
			JUTIL_MD5_GG ( d, a, b, c, in[ 2], JUTIL_MD5_S22, 4243563512); /* 30 */
			JUTIL_MD5_GG ( c, d, a, b, in[ 7], JUTIL_MD5_S23, 1735328473); /* 31 */
			JUTIL_MD5_GG ( b, c, d, a, in[12], JUTIL_MD5_S24, 2368359562); /* 32 */

			/* Round 3 */
			JUTIL_MD5_HH ( a, b, c, d, in[ 5], JUTIL_MD5_S31, 4294588738); /* 33 */
			JUTIL_MD5_HH ( d, a, b, c, in[ 8], JUTIL_MD5_S32, 2272392833); /* 34 */
			JUTIL_MD5_HH ( c, d, a, b, in[11], JUTIL_MD5_S33, 1839030562); /* 35 */
			JUTIL_MD5_HH ( b, c, d, a, in[14], JUTIL_MD5_S34, 4259657740); /* 36 */
			JUTIL_MD5_HH ( a, b, c, d, in[ 1], JUTIL_MD5_S31, 2763975236); /* 37 */
			JUTIL_MD5_HH ( d, a, b, c, in[ 4], JUTIL_MD5_S32, 1272893353); /* 38 */
			JUTIL_MD5_HH ( c, d, a, b, in[ 7], JUTIL_MD5_S33, 4139469664); /* 39 */
			JUTIL_MD5_HH ( b, c, d, a, in[10], JUTIL_MD5_S34, 3200236656); /* 40 */
			JUTIL_MD5_HH ( a, b, c, d, in[13], JUTIL_MD5_S31,  681279174); /* 41 */
			JUTIL_MD5_HH ( d, a, b, c, in[ 0], JUTIL_MD5_S32, 3936430074); /* 42 */
			JUTIL_MD5_HH ( c, d, a, b, in[ 3], JUTIL_MD5_S33, 3572445317); /* 43 */
			JUTIL_MD5_HH ( b, c, d, a, in[ 6], JUTIL_MD5_S34,   76029189); /* 44 */
			JUTIL_MD5_HH ( a, b, c, d, in[ 9], JUTIL_MD5_S31, 3654602809); /* 45 */
			JUTIL_MD5_HH ( d, a, b, c, in[12], JUTIL_MD5_S32, 3873151461); /* 46 */
			JUTIL_MD5_HH ( c, d, a, b, in[15], JUTIL_MD5_S33,  530742520); /* 47 */
			JUTIL_MD5_HH ( b, c, d, a, in[ 2], JUTIL_MD5_S34, 3299628645); /* 48 */

			/* Round 4 */
			JUTIL_MD5_II ( a, b, c, d, in[ 0], JUTIL_MD5_S41, 4096336452); /* 49 */
			JUTIL_MD5_II ( d, a, b, c, in[ 7], JUTIL_MD5_S42, 1126891415); /* 50 */
			JUTIL_MD5_II ( c, d, a, b, in[14], JUTIL_MD5_S43, 2878612391); /* 51 */
			JUTIL_MD5_II ( b, c, d, a, in[ 5], JUTIL_MD5_S44, 4237533241); /* 52 */
			JUTIL_MD5_II ( a, b, c, d, in[12], JUTIL_MD5_S41, 1700485571); /* 53 */
			JUTIL_MD5_II ( d, a, b, c, in[ 3], JUTIL_MD5_S42, 2399980690); /* 54 */
			JUTIL_MD5_II ( c, d, a, b, in[10], JUTIL_MD5_S43, 4293915773); /* 55 */
			JUTIL_MD5_II ( b, c, d, a, in[ 1], JUTIL_MD5_S44, 2240044497); /* 56 */
			JUTIL_MD5_II ( a, b, c, d, in[ 8], JUTIL_MD5_S41, 1873313359); /* 57 */
			JUTIL_MD5_II ( d, a, b, c, in[15], JUTIL_MD5_S42, 4264355552); /* 58 */
			JUTIL_MD5_II ( c, d, a, b, in[ 6], JUTIL_MD5_S43, 2734768916); /* 59 */
			JUTIL_MD5_II ( b, c, d, a, in[13], JUTIL_MD5_S44, 1309151649); /* 60 */
			JUTIL_MD5_II ( a, b, c, d, in[ 4], JUTIL_MD5_S41, 4149444226); /* 61 */
			JUTIL_MD5_II ( d, a, b, c, in[11], JUTIL_MD5_S42, 3174756917); /* 62 */
			JUTIL_MD5_II ( c, d, a, b, in[ 2], JUTIL_MD5_S43,  718787259); /* 63 */
			JUTIL_MD5_II ( b, c, d, a, in[ 9], JUTIL_MD5_S44, 3951481745); /* 64 */

			buf[0] += a;
			buf[1] += b;
			buf[2] += c;
			buf[3] += d;
		}

	};

}

#endif // JUTIL_MD5_HPP