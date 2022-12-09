
#include <string.h>
#include <stdio.h>

#include "test-utils.h"

// Test some non-VFPU instructions that are Allegrex specific.

#define FILL_ERR(errmsg, v, ve)  \
{                                \
  errs[errcnt].msg = (errmsg);   \
  errs[errcnt].value = (v);      \
  errs[errcnt].valueex = (ve);   \
  errcnt++;                      \
}

#define _unary_op_ext_templ(apos, asiz)                          \
	uint32_t _asm_impl_ext_##apos##_##asiz(uint32_t ival) {      \
		uint32_t ret;                                            \
		asm volatile("ext %0, %1," #apos "," #asiz "\n"          \
			: "=r"(ret) : "r"(ival));                            \
		return ret;                                              \
	}

#define _unary_op_ins_templ(apos, asiz)                          \
	uint32_t _asm_impl_ins_##apos##_##asiz(                      \
	                         uint32_t base, uint32_t ival) {     \
		uint32_t ret = base;                                     \
		asm volatile("ins %0, %1," #apos "," #asiz "\n"          \
			: "+r"(ret) : "r"(ival));                            \
		return ret;                                              \
	}

#define _unary_op_templ(opn)                                     \
	uint32_t _asm_impl_##opn(uint32_t ival) {                    \
		uint32_t ret;                                            \
		asm volatile(#opn " %0, %1\n" : "=r"(ret) : "r"(ival));  \
		return ret;                                              \
	}

#define _macc_templ(opnm)                                                     \
	uint64_t _asm_impl_##opnm(uint64_t base, uint32_t ival0, uint32_t ival1) {\
		union {                                                               \
			uint32_t u32[2];                                                  \
			uint64_t u64;                                                     \
		} inp, ret;                                                           \
		inp.u64 = base;                                                       \
		asm volatile(                                                         \
			"mtlo %2\n mthi %3\n"                                             \
			#opnm " %4, %5\n"                                                 \
			"mflo %0\n mfhi %1\n"                                             \
			: "=r"(ret.u32[0]), "=r"(ret.u32[1])                              \
			: "r"(inp.u32[0]), "r"(inp.u32[1]), "r"(ival0), "r"(ival1));      \
		return ret.u64;                                                       \
	}

_unary_op_ext_templ(3, 9)
_unary_op_ins_templ(3, 9)
_unary_op_ext_templ(8, 11)
_unary_op_ins_templ(8, 11)
_unary_op_templ(wsbh)
_unary_op_templ(wsbw)
_unary_op_templ(bitrev)
_unary_op_templ(clo)
_unary_op_templ(clz)
_unary_op_templ(seb)
_unary_op_templ(seh)
_macc_templ(msub)
_macc_templ(msubu)
_macc_templ(madd)
_macc_templ(maddu)

uint32_t _asm_impl_min(uint32_t ival0, uint32_t ival1) {
	uint32_t ret;
	asm volatile("min %0, %1, %2\n" : "=r"(ret) : "r"(ival0), "r"(ival1));
	return ret;
}

uint32_t _asm_impl_max(uint32_t ival0, uint32_t ival1) {
	uint32_t ret;
	asm volatile("max %0, %1, %2\n" : "=r"(ret) : "r"(ival0), "r"(ival1));
	return ret;
}

uint32_t _asm_impl_movz(uint32_t baseval, uint32_t overval, uint32_t sel) {
	uint32_t ret;
	asm volatile(
		"move %0, %1; movz %0, %2, %3\n" : "=r"(ret) : "r"(baseval), "r"(overval), "r"(sel));
	return ret;
}

uint32_t _asm_impl_movn(uint32_t baseval, uint32_t overval, uint32_t sel) {
	uint32_t ret;
	asm volatile(
		"move %0, %1; movn %0, %2, %3\n" : "=r"(ret) : "r"(baseval), "r"(overval), "r"(sel));
	return ret;
}


int check_allegrex_insts(struct check_error_info *errs) {
	int errcnt = 0;

	// Test PSP specific instructions: wsbw, bitrev, max, min
	{
		const uint32_t test_data[][2] = {
			{0x11223344, 0x44332211},
			{0x1F2F3F4F, 0x4F3F2F1F},
			{0x01020304, 0x04030201},
		};
		for (unsigned i = 0; i < 3; i++) {
			uint32_t v = _asm_impl_wsbw(test_data[i][0]);
			if (v != test_data[i][1])
				FILL_ERR("wsbw test mismatch!", v, test_data[i][1]);
		}
	}{
		const uint32_t test_data[][2] = {
			{0x12345678, 0x1e6a2c48},
			{0x87654321, 0x84c2a6e1},
			{0x397618fb, 0xdf186e9c},
			{0x84ea0c63, 0xc6305721},
			{0xd1d85b49, 0x92da1b8b},
			{0xeb9af324, 0x24cf59d7},
			{0x00000000, 0x00000000},
			{0xffffffff, 0xffffffff},
			{0x13570000, 0x0000eac8},
			{0x00001357, 0xeac80000},
		};
		for (unsigned i = 0; i < 10; i++) {
			uint32_t v = _asm_impl_bitrev(test_data[i][0]);
			if (v != test_data[i][1])
				FILL_ERR("bitrev test mismatch!", v, test_data[i][1]);
		}
	}{
		const uint32_t test_data[][3] = {
			{0x00000000, 0x00000001, 0x00000001},
			{0x00000000, 0xFFFFFFFF, 0x00000000},
			{0x00000000, 0x7FFFFFFF, 0x7FFFFFFF},
			{0x00000000, 0x80000000, 0x00000000},
			{0xFFFFFFFF, 0xFFFFFFFE, 0xFFFFFFFF},
			{0xFF000000, 0x80000000, 0xFF000000},
		};
		for (unsigned i = 0; i < 6; i++) {
			uint32_t v = _asm_impl_max(test_data[i][0], test_data[i][1]);
			if (v != test_data[i][2])
				FILL_ERR("max test mismatch!", v, test_data[i][2]);
		}
	}{
		const uint32_t test_data[][3] = {
			{0x00000000, 0x00000001, 0x00000000},
			{0x00000000, 0xFFFFFFFF, 0xFFFFFFFF},
			{0x00000000, 0x7FFFFFFF, 0x00000000},
			{0x00000000, 0x80000000, 0x80000000},
			{0xFFFFFFFF, 0xFFFFFFFE, 0xFFFFFFFE},
			{0xFF000000, 0x80000000, 0x80000000},
		};
		for (unsigned i = 0; i < 6; i++) {
			uint32_t v = _asm_impl_min(test_data[i][0], test_data[i][1]);
			if (v != test_data[i][2])
				FILL_ERR("min test mismatch!", v, test_data[i][2]);
		}
	}

	// Test MIPS32-like instructions with funny encodings: clo, clz, msub, msubu
	{
		const uint32_t test_data[][2] = {
			{0xFFFFFFFF, 32},
			{0xFFFFFFFE, 31},
			{0xF0000000,  4},
			{0xFFF00000, 12},
			{0x7FF00000,  0},
			{0x00000000,  0},
			{0xF0012345,  4},
			{0xF0000123,  4},
		};
		for (unsigned i = 0; i < 8; i++) {
			uint32_t v = _asm_impl_clo(test_data[i][0]);
			if (v != test_data[i][1])
				FILL_ERR("clo test mismatch!", v, test_data[i][1]);
		}
	}{
		const uint32_t test_data[][2] = {
			{0x00000000, 32},
			{0xFFFFFFFF,  0},
			{0xFFFFFFFE,  0},
			{0x7FFFFFFF,  1},
			{0x00000FFF, 20},
			{0x08003432,  4},
			{0x0F000045,  4},
			{0x00F00012,  8},
		};
		for (unsigned i = 0; i < 8; i++) {
			uint32_t v = _asm_impl_clz(test_data[i][0]);
			if (v != test_data[i][1])
				FILL_ERR("clz test mismatch!", v, test_data[i][1]);
		}
	}{
		const struct {
			uint64_t base, expected;
			uint32_t opA, opB;
		} test_data[] = {
			{0xFFFFFFFFFFFFFFFFULL, 0x0000000000000000ULL, 0x00000001, 0xFFFFFFFF},   // -1 - (1 * -1)  =  0
			{0xFFFFFFFFFFFFFFFFULL, 0xFFFFFFFFFFFFFFFEULL, 0xFFFFFFFF, 0xFFFFFFFF},   // -1 - (-1 * -1) = -2
			{0xFFFFFFFFFFFFFFFFULL, 0xFFFFFFFFFFFFFFFEULL, 0x00000001, 0x00000001},   // -1 - (1 * 1)   = -2
			{0xFFFFFF0000000000ULL, 0xFFFFFEFFFEB4A570ULL, 0x00001234, 0x00001234},
			{0xFFFFFFFFFFFFFFFFULL, 0x00000000000000EFULL, 0x0000000F, 0xFFFFFFF0},
		};
		for (unsigned i = 0; i < 5; i++) {
			uint64_t v = _asm_impl_msub(test_data[i].base, test_data[i].opA, test_data[i].opB);
			if (v != test_data[i].expected)
				FILL_ERR("msub test mismatch!", v, test_data[i].expected);
		}
	}{
		const struct {
			uint64_t base, expected;
			uint32_t opA, opB;
		} test_data[] = {
			{0xFFFFFFFFFFFFFFFFULL, 0xFFFFFFFF00000000ULL, 0x00000001, 0xFFFFFFFF},
			{0xFFFFFFFFFFFFFFFFULL, 0x00000001FFFFFFFEULL, 0xFFFFFFFF, 0xFFFFFFFF},
			{0xFFFFFFFFFFFFFFFFULL, 0xFFFFFFFFFFFFFFFEULL, 0x00000001, 0x00000001},
			{0xFFFFFF0000000000ULL, 0xFFFFFEFFFEB4A570ULL, 0x00001234, 0x00001234},
			{0xFFFFFFFFFFFFFFFFULL, 0xFFFFFFF1000000EFULL, 0x0000000F, 0xFFFFFFF0},
		};
		for (unsigned i = 0; i < 5; i++) {
			uint64_t v = _asm_impl_msubu(test_data[i].base, test_data[i].opA, test_data[i].opB);
			if (v != test_data[i].expected)
				FILL_ERR("msubu test mismatch!", v, test_data[i].expected);
		}
	}

	// Test MIPS32 instructions (with same encoding): movz, movn
	{
		const uint32_t test_data[][4] = {
			{0xdeadc0fe, 0xf15bf00d, 0x00000000, 0xf15bf00d},
			{0xdeadc0fe, 0xf15bf00d, 0x00000001, 0xdeadc0fe},
			{0xdeadc0fe, 0xf15bf00d, 0x80000000, 0xdeadc0fe},
			{0xdeadc0fe, 0xf15bf00d, 0xffffffff, 0xdeadc0fe},
		};
		for (unsigned i = 0; i < 4; i++) {
			uint32_t v = _asm_impl_movz(test_data[i][0], test_data[i][1], test_data[i][2]);
			if (v != test_data[i][3])
				FILL_ERR("movz test mismatch!", v, test_data[i][3]);
		}
	}{
		const uint32_t test_data[][4] = {
			{0xdeadc0fe, 0xf15bf00d, 0x00000000, 0xdeadc0fe},
			{0xdeadc0fe, 0xf15bf00d, 0x00000001, 0xf15bf00d},
			{0xdeadc0fe, 0xf15bf00d, 0x80000000, 0xf15bf00d},
			{0xdeadc0fe, 0xf15bf00d, 0xffffffff, 0xf15bf00d},
		};
		for (unsigned i = 0; i < 4; i++) {
			uint32_t v = _asm_impl_movn(test_data[i][0], test_data[i][1], test_data[i][2]);
			if (v != test_data[i][3])
				FILL_ERR("movn test mismatch!", v, test_data[i][3]);
		}
	}

	// Test R4010 encoded insts: madd, maddu
	{
		const struct {
			uint64_t base, expected;
			uint32_t opA, opB;
		} test_data[] = {
			{0xFFFFFFFFFFFFFFFFULL, 0xFFFFFFFFFFFFFFFEULL, 0x00000001, 0xFFFFFFFF},   // -1 + (1 * -1)  = -2
			{0xFFFFFFFFFFFFFFFFULL, 0x0000000000000000ULL, 0xFFFFFFFF, 0xFFFFFFFF},   // -1 + (-1 * -1) =  0
			{0xFFFFFFFFFFFFFFFFULL, 0x0000000000000000ULL, 0x00000001, 0x00000001},   // -1 + (1 * 1)   =  0
			{0xFFFFFF0000000000ULL, 0xFFFFFF00014B5A90ULL, 0x00001234, 0x00001234},
			{0xFFFFFFFFFFFFFFFFULL, 0xFFFFFFFFFFFFFF0FULL, 0x0000000F, 0xFFFFFFF0},
		};
		for (unsigned i = 0; i < 5; i++) {
			uint64_t v = _asm_impl_madd(test_data[i].base, test_data[i].opA, test_data[i].opB);
			if (v != test_data[i].expected)
				FILL_ERR("madd test mismatch!", v, test_data[i].expected);
		}
	}{
		const struct {
			uint64_t base, expected;
			uint32_t opA, opB;
		} test_data[] = {
			{0xFFFFFFFFFFFFFFFFULL, 0x00000000FFFFFFFEULL, 0x00000001, 0xFFFFFFFF},
			{0xFFFFFFFFFFFFFFFFULL, 0xFFFFFFFE00000000ULL, 0xFFFFFFFF, 0xFFFFFFFF},
			{0xFFFFFFFFFFFFFFFFULL, 0x0000000000000000ULL, 0x00000001, 0x00000001},
			{0xFFFFFF0000000000ULL, 0xFFFFFF00014B5A90ULL, 0x00001234, 0x00001234},
			{0xFFFFFFFFFFFFFFFFULL, 0x0000000eFFFFFF0FULL, 0x0000000F, 0xFFFFFFF0},
		};
		for (unsigned i = 0; i < 5; i++) {
			uint64_t v = _asm_impl_maddu(test_data[i].base, test_data[i].opA, test_data[i].opB);
			if (v != test_data[i].expected)
				FILL_ERR("maddu test mismatch!", v, test_data[i].expected);
		}
	}

	// Test rotation (rotr) and bit manipulation (wsbh, seb, seh, ext, ins) MIPS32r2 instructions
	{
		const uint32_t test_data[][2] = {
			{0x11223344, 0x22114433},
			{0x1F2F3F4F, 0x2F1F4F3F},
			{0x01020304, 0x02010403},
		};
		for (unsigned i = 0; i < 3; i++) {
			uint32_t v = _asm_impl_wsbh(test_data[i][0]);
			if (v != test_data[i][1])
				FILL_ERR("wsbh test mismatch!", v, test_data[i][1]);
		}
	}{
		const uint32_t test_data[][2] = {
			{0x00000000, 0x00000000},
			{0x00000001, 0x00000001},
			{0x00000040, 0x00000040},
			{0x0000007F, 0x0000007F},
			{0x00000080, 0xFFFFFF80},
			{0x01230080, 0xFFFFFF80},
			{0x00000100, 0x00000000},
			{0xF0000100, 0x00000000},
			{0xFFFFFF00, 0x00000000},
			{0xFFFFFFFF, 0xFFFFFFFF},
			{0xFFFFFFEE, 0xFFFFFFEE},
			{0xFFFFFFF0, 0xFFFFFFF0},
		};
		for (unsigned i = 0; i < 12; i++) {
			uint32_t v = _asm_impl_seb(test_data[i][0]);
			if (v != test_data[i][1])
				FILL_ERR("seb test mismatch!", v, test_data[i][1]);
		}
	}{
		const uint32_t test_data[][2] = {
			{0x00000000, 0x00000000},
			{0x00000001, 0x00000001},
			{0x00004000, 0x00004000},
			{0x00007FFF, 0x00007FFF},
			{0x00008000, 0xFFFF8000},
			{0x12308000, 0xFFFF8000},
			{0x00010000, 0x00000000},
			{0xF0010000, 0x00000000},
			{0xFFFF0000, 0x00000000},
			{0xFFFFFFFF, 0xFFFFFFFF},
			{0xFFFFEEEE, 0xFFFFEEEE},
			{0xFFFFF000, 0xFFFFF000},
		};
		for (unsigned i = 0; i < 12; i++) {
			uint32_t v = _asm_impl_seh(test_data[i][0]);
			if (v != test_data[i][1])
				FILL_ERR("seh test mismatch!", v, test_data[i][1]);
		}
	}{
		const uint32_t test_data[][2] = {
			{0x00000000, 0x00000000},
			{0xffffffff, 0x000001ff},
			{0x12345678, 0x000000cf},
			{0xabcdabcd, 0x00000179},
		};
		for (unsigned i = 0; i < 4; i++) {
			uint32_t v = _asm_impl_ext_3_9(test_data[i][0]);
			if (v != test_data[i][1])
				FILL_ERR("ext3,9 test mismatch!", v, test_data[i][1]);
		}
	}{
		const uint32_t test_data[][2] = {
			{0x00000000, 0x00000000},
			{0xffffffff, 0x000007ff},
			{0x12345678, 0x00000456},
			{0xabcdabcd, 0x000005ab},
		};
		for (unsigned i = 0; i < 4; i++) {
			uint32_t v = _asm_impl_ext_8_11(test_data[i][0]);
			if (v != test_data[i][1])
				FILL_ERR("ext8,11 test mismatch!", v, test_data[i][1]);
		}
	}{
		const uint32_t test_data[][3] = {
			{0xffffffff, 0x00000000, 0xfffff007},
			{0x00000000, 0xffffffff, 0x00000ff8},
			{0x5a5a5a5a, 0x87654321, 0x5a5a590a},
			{0x12345678, 0x0abcdef9, 0x123457c8},
		};
		for (unsigned i = 0; i < 4; i++) {
			uint32_t v = _asm_impl_ins_3_9(test_data[i][0], test_data[i][1]);
			if (v != test_data[i][2])
				FILL_ERR("ins3,9 test mismatch!", v, test_data[i][2]);
		}
	}{
		const uint32_t test_data[][3] = {
			{0xffffffff, 0x00000000, 0xfff800ff},
			{0x00000000, 0xffffffff, 0x0007ff00},
			{0x5a5a5a5a, 0x87654321, 0x5a5b215a},
			{0x12345678, 0x0abcdef9, 0x1236f978},
		};
		for (unsigned i = 0; i < 4; i++) {
			uint32_t v = _asm_impl_ins_8_11(test_data[i][0], test_data[i][1]);
			if (v != test_data[i][2])
				FILL_ERR("ins8,11 test mismatch!", v, test_data[i][2]);
		}
	}

	return errcnt;
}

