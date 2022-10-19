#include "func-def.h"
#include "prefix-func.h"
#include "test-utils.h"
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
int run_vc2i_s(struct test_error_info *errlist,
               struct prefix_usage_info *pfxinfo) {
  int errcnt = 0;
  // Tests for instruction vc2i.s (Unpack char to integer)
  for (unsigned i = 0; i < 128; i++) {
    unsigned int rs_ref[1];
    gen_inputs_u32(i >> 0, &rs_ref[0], 1);
    pfxinfo->inst_name = "vc2i.s";
    pfxinfo->rs_tested = 1;
    pfxinfo->rd_tested = 1;
    {
      unsigned int rs[1];
      pfx_src((uint32_t *)&rs[0], (uint32_t *)&rs_ref[0], 0xdc0000e4, 1);
      unsigned int rd[4] = {0}, rd_out[4] = {0};
      asm volatile("mtvc $0, $131;vmzero.q M400");
      asm volatile("lv.s S000, 0*4(%0)" ::"r"(&rs_ref[0]));
      rd[0] = (rs[0] >> (8 * (0 % 4))) << 24;
      rd[1] = (rs[0] >> (8 * (1 % 4))) << 24;
      rd[2] = (rs[0] >> (8 * (2 % 4))) << 24;
      rd[3] = (rs[0] >> (8 * (3 % 4))) << 24;
      ;
      unsigned int *rd_final = &rd[0]; // No dst prefix
      asm volatile(".word 0xdc0000e4" ::: "memory");
      asm volatile(".word 0xd0390010" ::: "memory");
      asm volatile("sv.s S400, 0*4(%0)" ::"r"(&rd_out[0]));
      asm volatile("sv.s S401, 1*4(%0)" ::"r"(&rd_out[0]));
      asm volatile("sv.s S402, 2*4(%0)" ::"r"(&rd_out[0]));
      asm volatile("sv.s S403, 3*4(%0)" ::"r"(&rd_out[0]));
      int mm = (memcmp(&rd_final[0], &rd_out[0], 4 * sizeof(uint32_t)));
      if (mm) {
        struct test_error_info *rep = &pfxinfo->rs_swz_err;
        static const struct test_decl_info iinfo = {
            .inst = "vc2i.s",
            .instw = 0xd0390010,
            .pfxw = 0xdc0000e4,
            .rdoutsz = 4,
            .inputs = {
                {.inpname = "rs", .size = 1},
            }};
        fill_errinfo(rep, &iinfo, rd_final, rd_out);
        fill_reg(rep->inputs[0], rs_ref);
        pfxinfo->rs_errors |= (1 << enum_swz);
      }
    }
    {
      unsigned int rs[1];
      pfx_src((uint32_t *)&rs[0], (uint32_t *)&rs_ref[0], 0xdc0500e4, 1);
      unsigned int rd[4] = {0}, rd_out[4] = {0};
      asm volatile("mtvc $0, $131;vmzero.q M400");
      asm volatile("lv.s S000, 0*4(%0)" ::"r"(&rs_ref[0]));
      rd[0] = (rs[0] >> (8 * (0 % 4))) << 24;
      rd[1] = (rs[0] >> (8 * (1 % 4))) << 24;
      rd[2] = (rs[0] >> (8 * (2 % 4))) << 24;
      rd[3] = (rs[0] >> (8 * (3 % 4))) << 24;
      ;
      unsigned int *rd_final = &rd[0]; // No dst prefix
      asm volatile(".word 0xdc0500e4" ::: "memory");
      asm volatile(".word 0xd0390010" ::: "memory");
      asm volatile("sv.s S400, 0*4(%0)" ::"r"(&rd_out[0]));
      asm volatile("sv.s S401, 1*4(%0)" ::"r"(&rd_out[0]));
      asm volatile("sv.s S402, 2*4(%0)" ::"r"(&rd_out[0]));
      asm volatile("sv.s S403, 3*4(%0)" ::"r"(&rd_out[0]));
      int mm = (memcmp(&rd_final[0], &rd_out[0], 4 * sizeof(uint32_t)));
      if (mm) {
        struct test_error_info *rep = &pfxinfo->rs_neg_err;
        static const struct test_decl_info iinfo = {
            .inst = "vc2i.s",
            .instw = 0xd0390010,
            .pfxw = 0xdc0500e4,
            .rdoutsz = 4,
            .inputs = {
                {.inpname = "rs", .size = 1},
            }};
        fill_errinfo(rep, &iinfo, rd_final, rd_out);
        fill_reg(rep->inputs[0], rs_ref);
        pfxinfo->rs_errors |= (1 << enum_neg);
      }
    }
    {
      unsigned int rs[1];
      pfx_src((uint32_t *)&rs[0], (uint32_t *)&rs_ref[0], 0xdc0a00e4, 1);
      unsigned int rd[4] = {0}, rd_out[4] = {0};
      asm volatile("mtvc $0, $131;vmzero.q M400");
      asm volatile("lv.s S000, 0*4(%0)" ::"r"(&rs_ref[0]));
      rd[0] = (rs[0] >> (8 * (0 % 4))) << 24;
      rd[1] = (rs[0] >> (8 * (1 % 4))) << 24;
      rd[2] = (rs[0] >> (8 * (2 % 4))) << 24;
      rd[3] = (rs[0] >> (8 * (3 % 4))) << 24;
      ;
      unsigned int *rd_final = &rd[0]; // No dst prefix
      asm volatile(".word 0xdc0a00e4" ::: "memory");
      asm volatile(".word 0xd0390010" ::: "memory");
      asm volatile("sv.s S400, 0*4(%0)" ::"r"(&rd_out[0]));
      asm volatile("sv.s S401, 1*4(%0)" ::"r"(&rd_out[0]));
      asm volatile("sv.s S402, 2*4(%0)" ::"r"(&rd_out[0]));
      asm volatile("sv.s S403, 3*4(%0)" ::"r"(&rd_out[0]));
      int mm = (memcmp(&rd_final[0], &rd_out[0], 4 * sizeof(uint32_t)));
      if (mm) {
        struct test_error_info *rep = &pfxinfo->rs_neg_err;
        static const struct test_decl_info iinfo = {
            .inst = "vc2i.s",
            .instw = 0xd0390010,
            .pfxw = 0xdc0a00e4,
            .rdoutsz = 4,
            .inputs = {
                {.inpname = "rs", .size = 1},
            }};
        fill_errinfo(rep, &iinfo, rd_final, rd_out);
        fill_reg(rep->inputs[0], rs_ref);
        pfxinfo->rs_errors |= (1 << enum_neg);
      }
    }
    {
      unsigned int rs[1];
      pfx_src((uint32_t *)&rs[0], (uint32_t *)&rs_ref[0], 0xdc0f00e4, 1);
      unsigned int rd[4] = {0}, rd_out[4] = {0};
      asm volatile("mtvc $0, $131;vmzero.q M400");
      asm volatile("lv.s S000, 0*4(%0)" ::"r"(&rs_ref[0]));
      rd[0] = (rs[0] >> (8 * (0 % 4))) << 24;
      rd[1] = (rs[0] >> (8 * (1 % 4))) << 24;
      rd[2] = (rs[0] >> (8 * (2 % 4))) << 24;
      rd[3] = (rs[0] >> (8 * (3 % 4))) << 24;
      ;
      unsigned int *rd_final = &rd[0]; // No dst prefix
      asm volatile(".word 0xdc0f00e4" ::: "memory");
      asm volatile(".word 0xd0390010" ::: "memory");
      asm volatile("sv.s S400, 0*4(%0)" ::"r"(&rd_out[0]));
      asm volatile("sv.s S401, 1*4(%0)" ::"r"(&rd_out[0]));
      asm volatile("sv.s S402, 2*4(%0)" ::"r"(&rd_out[0]));
      asm volatile("sv.s S403, 3*4(%0)" ::"r"(&rd_out[0]));
      int mm = (memcmp(&rd_final[0], &rd_out[0], 4 * sizeof(uint32_t)));
      if (mm) {
        struct test_error_info *rep = &pfxinfo->rs_neg_err;
        static const struct test_decl_info iinfo = {
            .inst = "vc2i.s",
            .instw = 0xd0390010,
            .pfxw = 0xdc0f00e4,
            .rdoutsz = 4,
            .inputs = {
                {.inpname = "rs", .size = 1},
            }};
        fill_errinfo(rep, &iinfo, rd_final, rd_out);
        fill_reg(rep->inputs[0], rs_ref);
        pfxinfo->rs_errors |= (1 << enum_neg);
      }
    }
    {
      unsigned int rs[1];
      pfx_src((uint32_t *)&rs[0], (uint32_t *)&rs_ref[0], 0xdc0005e4, 1);
      unsigned int rd[4] = {0}, rd_out[4] = {0};
      asm volatile("mtvc $0, $131;vmzero.q M400");
      asm volatile("lv.s S000, 0*4(%0)" ::"r"(&rs_ref[0]));
      rd[0] = (rs[0] >> (8 * (0 % 4))) << 24;
      rd[1] = (rs[0] >> (8 * (1 % 4))) << 24;
      rd[2] = (rs[0] >> (8 * (2 % 4))) << 24;
      rd[3] = (rs[0] >> (8 * (3 % 4))) << 24;
      ;
      unsigned int *rd_final = &rd[0]; // No dst prefix
      asm volatile(".word 0xdc0005e4" ::: "memory");
      asm volatile(".word 0xd0390010" ::: "memory");
      asm volatile("sv.s S400, 0*4(%0)" ::"r"(&rd_out[0]));
      asm volatile("sv.s S401, 1*4(%0)" ::"r"(&rd_out[0]));
      asm volatile("sv.s S402, 2*4(%0)" ::"r"(&rd_out[0]));
      asm volatile("sv.s S403, 3*4(%0)" ::"r"(&rd_out[0]));
      int mm = (memcmp(&rd_final[0], &rd_out[0], 4 * sizeof(uint32_t)));
      if (mm) {
        struct test_error_info *rep = &pfxinfo->rs_abs_err;
        static const struct test_decl_info iinfo = {
            .inst = "vc2i.s",
            .instw = 0xd0390010,
            .pfxw = 0xdc0005e4,
            .rdoutsz = 4,
            .inputs = {
                {.inpname = "rs", .size = 1},
            }};
        fill_errinfo(rep, &iinfo, rd_final, rd_out);
        fill_reg(rep->inputs[0], rs_ref);
        pfxinfo->rs_errors |= (1 << enum_abs);
      }
    }
    {
      unsigned int rs[1];
      pfx_src((uint32_t *)&rs[0], (uint32_t *)&rs_ref[0], 0xdc000ae4, 1);
      unsigned int rd[4] = {0}, rd_out[4] = {0};
      asm volatile("mtvc $0, $131;vmzero.q M400");
      asm volatile("lv.s S000, 0*4(%0)" ::"r"(&rs_ref[0]));
      rd[0] = (rs[0] >> (8 * (0 % 4))) << 24;
      rd[1] = (rs[0] >> (8 * (1 % 4))) << 24;
      rd[2] = (rs[0] >> (8 * (2 % 4))) << 24;
      rd[3] = (rs[0] >> (8 * (3 % 4))) << 24;
      ;
      unsigned int *rd_final = &rd[0]; // No dst prefix
      asm volatile(".word 0xdc000ae4" ::: "memory");
      asm volatile(".word 0xd0390010" ::: "memory");
      asm volatile("sv.s S400, 0*4(%0)" ::"r"(&rd_out[0]));
      asm volatile("sv.s S401, 1*4(%0)" ::"r"(&rd_out[0]));
      asm volatile("sv.s S402, 2*4(%0)" ::"r"(&rd_out[0]));
      asm volatile("sv.s S403, 3*4(%0)" ::"r"(&rd_out[0]));
      int mm = (memcmp(&rd_final[0], &rd_out[0], 4 * sizeof(uint32_t)));
      if (mm) {
        struct test_error_info *rep = &pfxinfo->rs_abs_err;
        static const struct test_decl_info iinfo = {
            .inst = "vc2i.s",
            .instw = 0xd0390010,
            .pfxw = 0xdc000ae4,
            .rdoutsz = 4,
            .inputs = {
                {.inpname = "rs", .size = 1},
            }};
        fill_errinfo(rep, &iinfo, rd_final, rd_out);
        fill_reg(rep->inputs[0], rs_ref);
        pfxinfo->rs_errors |= (1 << enum_abs);
      }
    }
    {
      unsigned int rs[1];
      pfx_src((uint32_t *)&rs[0], (uint32_t *)&rs_ref[0], 0xdc000fe4, 1);
      unsigned int rd[4] = {0}, rd_out[4] = {0};
      asm volatile("mtvc $0, $131;vmzero.q M400");
      asm volatile("lv.s S000, 0*4(%0)" ::"r"(&rs_ref[0]));
      rd[0] = (rs[0] >> (8 * (0 % 4))) << 24;
      rd[1] = (rs[0] >> (8 * (1 % 4))) << 24;
      rd[2] = (rs[0] >> (8 * (2 % 4))) << 24;
      rd[3] = (rs[0] >> (8 * (3 % 4))) << 24;
      ;
      unsigned int *rd_final = &rd[0]; // No dst prefix
      asm volatile(".word 0xdc000fe4" ::: "memory");
      asm volatile(".word 0xd0390010" ::: "memory");
      asm volatile("sv.s S400, 0*4(%0)" ::"r"(&rd_out[0]));
      asm volatile("sv.s S401, 1*4(%0)" ::"r"(&rd_out[0]));
      asm volatile("sv.s S402, 2*4(%0)" ::"r"(&rd_out[0]));
      asm volatile("sv.s S403, 3*4(%0)" ::"r"(&rd_out[0]));
      int mm = (memcmp(&rd_final[0], &rd_out[0], 4 * sizeof(uint32_t)));
      if (mm) {
        struct test_error_info *rep = &pfxinfo->rs_abs_err;
        static const struct test_decl_info iinfo = {
            .inst = "vc2i.s",
            .instw = 0xd0390010,
            .pfxw = 0xdc000fe4,
            .rdoutsz = 4,
            .inputs = {
                {.inpname = "rs", .size = 1},
            }};
        fill_errinfo(rep, &iinfo, rd_final, rd_out);
        fill_reg(rep->inputs[0], rs_ref);
        pfxinfo->rs_errors |= (1 << enum_abs);
      }
    }
    {
      unsigned int rs[1];
      pfx_src((uint32_t *)&rs[0], (uint32_t *)&rs_ref[0], 0xdc00f4a7, 1);
      unsigned int rd[4] = {0}, rd_out[4] = {0};
      asm volatile("mtvc $0, $131;vmzero.q M400");
      asm volatile("lv.s S000, 0*4(%0)" ::"r"(&rs_ref[0]));
      rd[0] = (rs[0] >> (8 * (0 % 4))) << 24;
      rd[1] = (rs[0] >> (8 * (1 % 4))) << 24;
      rd[2] = (rs[0] >> (8 * (2 % 4))) << 24;
      rd[3] = (rs[0] >> (8 * (3 % 4))) << 24;
      ;
      unsigned int *rd_final = &rd[0]; // No dst prefix
      asm volatile(".word 0xdc00f4a7" ::: "memory");
      asm volatile(".word 0xd0390010" ::: "memory");
      asm volatile("sv.s S400, 0*4(%0)" ::"r"(&rd_out[0]));
      asm volatile("sv.s S401, 1*4(%0)" ::"r"(&rd_out[0]));
      asm volatile("sv.s S402, 2*4(%0)" ::"r"(&rd_out[0]));
      asm volatile("sv.s S403, 3*4(%0)" ::"r"(&rd_out[0]));
      int mm = (memcmp(&rd_final[0], &rd_out[0], 4 * sizeof(uint32_t)));
      if (mm) {
        struct test_error_info *rep = &pfxinfo->rs_cst_err;
        static const struct test_decl_info iinfo = {
            .inst = "vc2i.s",
            .instw = 0xd0390010,
            .pfxw = 0xdc00f4a7,
            .rdoutsz = 4,
            .inputs = {
                {.inpname = "rs", .size = 1},
            }};
        fill_errinfo(rep, &iinfo, rd_final, rd_out);
        fill_reg(rep->inputs[0], rs_ref);
        pfxinfo->rs_errors |= (1 << enum_cst);
      }
    }
    {
      unsigned int *rs = &rs_ref[0]; // No src prefix
      unsigned int rd[4] = {0}, rd_out[4] = {0};
      asm volatile("mtvc $0, $131;vmzero.q M400");
      asm volatile("lv.s S000, 0*4(%0)" ::"r"(&rs_ref[0]));
      rd[0] = (rs[0] >> (8 * (0 % 4))) << 24;
      rd[1] = (rs[0] >> (8 * (1 % 4))) << 24;
      rd[2] = (rs[0] >> (8 * (2 % 4))) << 24;
      rd[3] = (rs[0] >> (8 * (3 % 4))) << 24;
      ;
      unsigned int rd_final[4] = {0};
      pfx_dst((uint32_t *)&rd_final[0], (uint32_t *)&rd[0], 0xde000f00, 4);
      asm volatile(".word 0xde000f00" ::: "memory");
      asm volatile(".word 0xd0390010" ::: "memory");
      asm volatile("sv.s S400, 0*4(%0)" ::"r"(&rd_out[0]));
      asm volatile("sv.s S401, 1*4(%0)" ::"r"(&rd_out[0]));
      asm volatile("sv.s S402, 2*4(%0)" ::"r"(&rd_out[0]));
      asm volatile("sv.s S403, 3*4(%0)" ::"r"(&rd_out[0]));
      int mm = (memcmp(&rd_final[0], &rd_out[0], 4 * sizeof(uint32_t)));
      if (mm) {
        struct test_error_info *rep = &pfxinfo->rd_msk_err;
        static const struct test_decl_info iinfo = {
            .inst = "vc2i.s",
            .instw = 0xd0390010,
            .pfxw = 0xde000f00,
            .rdoutsz = 4,
            .inputs = {
                {.inpname = "rs", .size = 1},
            }};
        fill_errinfo(rep, &iinfo, rd_final, rd_out);
        fill_reg(rep->inputs[0], rs_ref);
        pfxinfo->rd_errors |= (1 << enum_msk);
      }
    }
    {
      unsigned int *rs = &rs_ref[0]; // No src prefix
      unsigned int rd[4] = {0}, rd_out[4] = {0};
      asm volatile("mtvc $0, $131;vmzero.q M400");
      asm volatile("lv.s S000, 0*4(%0)" ::"r"(&rs_ref[0]));
      rd[0] = (rs[0] >> (8 * (0 % 4))) << 24;
      rd[1] = (rs[0] >> (8 * (1 % 4))) << 24;
      rd[2] = (rs[0] >> (8 * (2 % 4))) << 24;
      rd[3] = (rs[0] >> (8 * (3 % 4))) << 24;
      ;
      unsigned int rd_final[4] = {0};
      pfx_dst((uint32_t *)&rd_final[0], (uint32_t *)&rd[0], 0xde000055, 4);
      asm volatile(".word 0xde000055" ::: "memory");
      asm volatile(".word 0xd0390010" ::: "memory");
      asm volatile("sv.s S400, 0*4(%0)" ::"r"(&rd_out[0]));
      asm volatile("sv.s S401, 1*4(%0)" ::"r"(&rd_out[0]));
      asm volatile("sv.s S402, 2*4(%0)" ::"r"(&rd_out[0]));
      asm volatile("sv.s S403, 3*4(%0)" ::"r"(&rd_out[0]));
      int mm = (memcmp(&rd_final[0], &rd_out[0], 4 * sizeof(uint32_t)));
      if (mm) {
        struct test_error_info *rep = &pfxinfo->rd_sat_err;
        static const struct test_decl_info iinfo = {
            .inst = "vc2i.s",
            .instw = 0xd0390010,
            .pfxw = 0xde000055,
            .rdoutsz = 4,
            .inputs = {
                {.inpname = "rs", .size = 1},
            }};
        fill_errinfo(rep, &iinfo, rd_final, rd_out);
        fill_reg(rep->inputs[0], rs_ref);
        pfxinfo->rd_errors |= (1 << enum_sat);
      }
    }
    {
      unsigned int *rs = &rs_ref[0]; // No src prefix
      unsigned int rd[4] = {0}, rd_out[4] = {0};
      asm volatile("mtvc $0, $131;vmzero.q M400");
      asm volatile("lv.s S000, 0*4(%0)" ::"r"(&rs_ref[0]));
      rd[0] = (rs[0] >> (8 * (0 % 4))) << 24;
      rd[1] = (rs[0] >> (8 * (1 % 4))) << 24;
      rd[2] = (rs[0] >> (8 * (2 % 4))) << 24;
      rd[3] = (rs[0] >> (8 * (3 % 4))) << 24;
      ;
      unsigned int rd_final[4] = {0};
      pfx_dst((uint32_t *)&rd_final[0], (uint32_t *)&rd[0], 0xde0000ff, 4);
      asm volatile(".word 0xde0000ff" ::: "memory");
      asm volatile(".word 0xd0390010" ::: "memory");
      asm volatile("sv.s S400, 0*4(%0)" ::"r"(&rd_out[0]));
      asm volatile("sv.s S401, 1*4(%0)" ::"r"(&rd_out[0]));
      asm volatile("sv.s S402, 2*4(%0)" ::"r"(&rd_out[0]));
      asm volatile("sv.s S403, 3*4(%0)" ::"r"(&rd_out[0]));
      int mm = (memcmp(&rd_final[0], &rd_out[0], 4 * sizeof(uint32_t)));
      if (mm) {
        struct test_error_info *rep = &pfxinfo->rd_sat_err;
        static const struct test_decl_info iinfo = {
            .inst = "vc2i.s",
            .instw = 0xd0390010,
            .pfxw = 0xde0000ff,
            .rdoutsz = 4,
            .inputs = {
                {.inpname = "rs", .size = 1},
            }};
        fill_errinfo(rep, &iinfo, rd_final, rd_out);
        fill_reg(rep->inputs[0], rs_ref);
        pfxinfo->rd_errors |= (1 << enum_sat);
      }
    }
    {
      unsigned int *rs = &rs_ref[0]; // No src prefix
      unsigned int rd[4] = {0}, rd_out[4] = {0};
      asm volatile("mtvc $0, $131;vmzero.q M400");
      asm volatile("lv.s S000, 0*4(%0)" ::"r"(&rs_ref[0]));
      rd[0] = (rs[0] >> (8 * (0 % 4))) << 24;
      rd[1] = (rs[0] >> (8 * (1 % 4))) << 24;
      rd[2] = (rs[0] >> (8 * (2 % 4))) << 24;
      rd[3] = (rs[0] >> (8 * (3 % 4))) << 24;
      ;
      unsigned int *rd_final = &rd[0]; // No dst prefix
      asm volatile(".word 0xd0390010" ::: "memory");
      asm volatile("sv.s S400, 0*4(%0)" ::"r"(&rd_out[0]));
      asm volatile("sv.s S401, 1*4(%0)" ::"r"(&rd_out[0]));
      asm volatile("sv.s S402, 2*4(%0)" ::"r"(&rd_out[0]));
      asm volatile("sv.s S403, 3*4(%0)" ::"r"(&rd_out[0]));
      int mm = (memcmp(&rd_final[0], &rd_out[0], 4 * sizeof(uint32_t)));
      if (mm) {
        struct test_error_info *rep = &errlist[errcnt];
        static const struct test_decl_info iinfo = {
            .inst = "vc2i.s",
            .instw = 0xd0390010,
            .pfxw = 0x00000000,
            .rdoutsz = 4,
            .inputs = {
                {.inpname = "rs", .size = 1},
            }};
        fill_errinfo(rep, &iinfo, rd_final, rd_out);
        fill_reg(rep->inputs[0], rs_ref);
        errcnt++;
        break;
      }
    }
  }

  return errcnt;
}
