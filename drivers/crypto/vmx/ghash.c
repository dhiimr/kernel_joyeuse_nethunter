<<<<<<< HEAD
/**
 * GHASH routines supporting VMX instructions on the Power 8
 *
 * Copyright (C) 2015 International Business Machines Inc.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 2 only.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 * Author: Marcelo Henrique Cerri <mhcerri@br.ibm.com>
=======
// SPDX-License-Identifier: GPL-2.0
/**
 * GHASH routines supporting VMX instructions on the Power 8
 *
 * Copyright (C) 2015, 2019 International Business Machines Inc.
 *
 * Author: Marcelo Henrique Cerri <mhcerri@br.ibm.com>
 *
 * Extended by Daniel Axtens <dja@axtens.net> to replace the fallback
 * mechanism. The new approach is based on arm64 code, which is:
 *   Copyright (C) 2014 - 2018 Linaro Ltd. <ard.biesheuvel@linaro.org>
>>>>>>> 203e04ce76c1190acfe30f7bc11928464f2a9e7f
 */

#include <linux/types.h>
#include <linux/err.h>
#include <linux/crypto.h>
#include <linux/delay.h>
#include <linux/hardirq.h>
#include <asm/switch_to.h>
#include <crypto/aes.h>
#include <crypto/ghash.h>
#include <crypto/scatterwalk.h>
#include <crypto/internal/hash.h>
#include <crypto/b128ops.h>

#define IN_INTERRUPT in_interrupt()

void gcm_init_p8(u128 htable[16], const u64 Xi[2]);
void gcm_gmult_p8(u64 Xi[2], const u128 htable[16]);
void gcm_ghash_p8(u64 Xi[2], const u128 htable[16],
		  const u8 *in, size_t len);

struct p8_ghash_ctx {
<<<<<<< HEAD
	u128 htable[16];
	struct crypto_shash *fallback;
=======
	/* key used by vector asm */
	u128 htable[16];
	/* key used by software fallback */
	be128 key;
>>>>>>> 203e04ce76c1190acfe30f7bc11928464f2a9e7f
};

struct p8_ghash_desc_ctx {
	u64 shash[2];
	u8 buffer[GHASH_DIGEST_SIZE];
	int bytes;
<<<<<<< HEAD
	struct shash_desc fallback_desc;
};

static int p8_ghash_init_tfm(struct crypto_tfm *tfm)
{
	const char *alg = "ghash-generic";
	struct crypto_shash *fallback;
	struct crypto_shash *shash_tfm = __crypto_shash_cast(tfm);
	struct p8_ghash_ctx *ctx = crypto_tfm_ctx(tfm);

	fallback = crypto_alloc_shash(alg, 0, CRYPTO_ALG_NEED_FALLBACK);
	if (IS_ERR(fallback)) {
		printk(KERN_ERR
		       "Failed to allocate transformation for '%s': %ld\n",
		       alg, PTR_ERR(fallback));
		return PTR_ERR(fallback);
	}

	crypto_shash_set_flags(fallback,
			       crypto_shash_get_flags((struct crypto_shash
						       *) tfm));

	/* Check if the descsize defined in the algorithm is still enough. */
	if (shash_tfm->descsize < sizeof(struct p8_ghash_desc_ctx)
	    + crypto_shash_descsize(fallback)) {
		printk(KERN_ERR
		       "Desc size of the fallback implementation (%s) does not match the expected value: %lu vs %u\n",
		       alg,
		       shash_tfm->descsize - sizeof(struct p8_ghash_desc_ctx),
		       crypto_shash_descsize(fallback));
		return -EINVAL;
	}
	ctx->fallback = fallback;

	return 0;
}

static void p8_ghash_exit_tfm(struct crypto_tfm *tfm)
{
	struct p8_ghash_ctx *ctx = crypto_tfm_ctx(tfm);

	if (ctx->fallback) {
		crypto_free_shash(ctx->fallback);
		ctx->fallback = NULL;
	}
}

static int p8_ghash_init(struct shash_desc *desc)
{
	struct p8_ghash_ctx *ctx = crypto_tfm_ctx(crypto_shash_tfm(desc->tfm));
=======
};

static int p8_ghash_init(struct shash_desc *desc)
{
>>>>>>> 203e04ce76c1190acfe30f7bc11928464f2a9e7f
	struct p8_ghash_desc_ctx *dctx = shash_desc_ctx(desc);

	dctx->bytes = 0;
	memset(dctx->shash, 0, GHASH_DIGEST_SIZE);
<<<<<<< HEAD
	dctx->fallback_desc.tfm = ctx->fallback;
	dctx->fallback_desc.flags = desc->flags;
	return crypto_shash_init(&dctx->fallback_desc);
=======
	return 0;
>>>>>>> 203e04ce76c1190acfe30f7bc11928464f2a9e7f
}

static int p8_ghash_setkey(struct crypto_shash *tfm, const u8 *key,
			   unsigned int keylen)
{
	struct p8_ghash_ctx *ctx = crypto_tfm_ctx(crypto_shash_tfm(tfm));

	if (keylen != GHASH_BLOCK_SIZE)
		return -EINVAL;

	preempt_disable();
	pagefault_disable();
	enable_kernel_vsx();
	gcm_init_p8(ctx->htable, (const u64 *) key);
	disable_kernel_vsx();
	pagefault_enable();
	preempt_enable();
<<<<<<< HEAD
	return crypto_shash_setkey(ctx->fallback, key, keylen);
=======

	memcpy(&ctx->key, key, GHASH_BLOCK_SIZE);

	return 0;
}

static inline void __ghash_block(struct p8_ghash_ctx *ctx,
				 struct p8_ghash_desc_ctx *dctx)
{
	if (!IN_INTERRUPT) {
		preempt_disable();
		pagefault_disable();
		enable_kernel_vsx();
		gcm_ghash_p8(dctx->shash, ctx->htable,
				dctx->buffer, GHASH_DIGEST_SIZE);
		disable_kernel_vsx();
		pagefault_enable();
		preempt_enable();
	} else {
		crypto_xor((u8 *)dctx->shash, dctx->buffer, GHASH_BLOCK_SIZE);
		gf128mul_lle((be128 *)dctx->shash, &ctx->key);
	}
}

static inline void __ghash_blocks(struct p8_ghash_ctx *ctx,
				  struct p8_ghash_desc_ctx *dctx,
				  const u8 *src, unsigned int srclen)
{
	if (!IN_INTERRUPT) {
		preempt_disable();
		pagefault_disable();
		enable_kernel_vsx();
		gcm_ghash_p8(dctx->shash, ctx->htable,
				src, srclen);
		disable_kernel_vsx();
		pagefault_enable();
		preempt_enable();
	} else {
		while (srclen >= GHASH_BLOCK_SIZE) {
			crypto_xor((u8 *)dctx->shash, src, GHASH_BLOCK_SIZE);
			gf128mul_lle((be128 *)dctx->shash, &ctx->key);
			srclen -= GHASH_BLOCK_SIZE;
			src += GHASH_BLOCK_SIZE;
		}
	}
>>>>>>> 203e04ce76c1190acfe30f7bc11928464f2a9e7f
}

static int p8_ghash_update(struct shash_desc *desc,
			   const u8 *src, unsigned int srclen)
{
	unsigned int len;
	struct p8_ghash_ctx *ctx = crypto_tfm_ctx(crypto_shash_tfm(desc->tfm));
	struct p8_ghash_desc_ctx *dctx = shash_desc_ctx(desc);

<<<<<<< HEAD
	if (IN_INTERRUPT) {
		return crypto_shash_update(&dctx->fallback_desc, src,
					   srclen);
	} else {
		if (dctx->bytes) {
			if (dctx->bytes + srclen < GHASH_DIGEST_SIZE) {
				memcpy(dctx->buffer + dctx->bytes, src,
				       srclen);
				dctx->bytes += srclen;
				return 0;
			}
			memcpy(dctx->buffer + dctx->bytes, src,
			       GHASH_DIGEST_SIZE - dctx->bytes);
			preempt_disable();
			pagefault_disable();
			enable_kernel_vsx();
			gcm_ghash_p8(dctx->shash, ctx->htable,
				     dctx->buffer, GHASH_DIGEST_SIZE);
			disable_kernel_vsx();
			pagefault_enable();
			preempt_enable();
			src += GHASH_DIGEST_SIZE - dctx->bytes;
			srclen -= GHASH_DIGEST_SIZE - dctx->bytes;
			dctx->bytes = 0;
		}
		len = srclen & ~(GHASH_DIGEST_SIZE - 1);
		if (len) {
			preempt_disable();
			pagefault_disable();
			enable_kernel_vsx();
			gcm_ghash_p8(dctx->shash, ctx->htable, src, len);
			disable_kernel_vsx();
			pagefault_enable();
			preempt_enable();
			src += len;
			srclen -= len;
		}
		if (srclen) {
			memcpy(dctx->buffer, src, srclen);
			dctx->bytes = srclen;
		}
		return 0;
	}
=======
	if (dctx->bytes) {
		if (dctx->bytes + srclen < GHASH_DIGEST_SIZE) {
			memcpy(dctx->buffer + dctx->bytes, src,
				srclen);
			dctx->bytes += srclen;
			return 0;
		}
		memcpy(dctx->buffer + dctx->bytes, src,
			GHASH_DIGEST_SIZE - dctx->bytes);

		__ghash_block(ctx, dctx);

		src += GHASH_DIGEST_SIZE - dctx->bytes;
		srclen -= GHASH_DIGEST_SIZE - dctx->bytes;
		dctx->bytes = 0;
	}
	len = srclen & ~(GHASH_DIGEST_SIZE - 1);
	if (len) {
		__ghash_blocks(ctx, dctx, src, len);
		src += len;
		srclen -= len;
	}
	if (srclen) {
		memcpy(dctx->buffer, src, srclen);
		dctx->bytes = srclen;
	}
	return 0;
>>>>>>> 203e04ce76c1190acfe30f7bc11928464f2a9e7f
}

static int p8_ghash_final(struct shash_desc *desc, u8 *out)
{
	int i;
	struct p8_ghash_ctx *ctx = crypto_tfm_ctx(crypto_shash_tfm(desc->tfm));
	struct p8_ghash_desc_ctx *dctx = shash_desc_ctx(desc);

<<<<<<< HEAD
	if (IN_INTERRUPT) {
		return crypto_shash_final(&dctx->fallback_desc, out);
	} else {
		if (dctx->bytes) {
			for (i = dctx->bytes; i < GHASH_DIGEST_SIZE; i++)
				dctx->buffer[i] = 0;
			preempt_disable();
			pagefault_disable();
			enable_kernel_vsx();
			gcm_ghash_p8(dctx->shash, ctx->htable,
				     dctx->buffer, GHASH_DIGEST_SIZE);
			disable_kernel_vsx();
			pagefault_enable();
			preempt_enable();
			dctx->bytes = 0;
		}
		memcpy(out, dctx->shash, GHASH_DIGEST_SIZE);
		return 0;
	}
=======
	if (dctx->bytes) {
		for (i = dctx->bytes; i < GHASH_DIGEST_SIZE; i++)
			dctx->buffer[i] = 0;
		__ghash_block(ctx, dctx);
		dctx->bytes = 0;
	}
	memcpy(out, dctx->shash, GHASH_DIGEST_SIZE);
	return 0;
>>>>>>> 203e04ce76c1190acfe30f7bc11928464f2a9e7f
}

struct shash_alg p8_ghash_alg = {
	.digestsize = GHASH_DIGEST_SIZE,
	.init = p8_ghash_init,
	.update = p8_ghash_update,
	.final = p8_ghash_final,
	.setkey = p8_ghash_setkey,
	.descsize = sizeof(struct p8_ghash_desc_ctx)
		+ sizeof(struct ghash_desc_ctx),
	.base = {
		 .cra_name = "ghash",
		 .cra_driver_name = "p8_ghash",
		 .cra_priority = 1000,
<<<<<<< HEAD
		 .cra_flags = CRYPTO_ALG_TYPE_SHASH | CRYPTO_ALG_NEED_FALLBACK,
		 .cra_blocksize = GHASH_BLOCK_SIZE,
		 .cra_ctxsize = sizeof(struct p8_ghash_ctx),
		 .cra_module = THIS_MODULE,
		 .cra_init = p8_ghash_init_tfm,
		 .cra_exit = p8_ghash_exit_tfm,
=======
		 .cra_flags = CRYPTO_ALG_TYPE_SHASH,
		 .cra_blocksize = GHASH_BLOCK_SIZE,
		 .cra_ctxsize = sizeof(struct p8_ghash_ctx),
		 .cra_module = THIS_MODULE,
>>>>>>> 203e04ce76c1190acfe30f7bc11928464f2a9e7f
	},
};
