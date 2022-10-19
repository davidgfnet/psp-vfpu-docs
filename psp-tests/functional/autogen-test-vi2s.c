#include "func-def.h"
#include "prefix-func.h"
#include "test-utils.h"
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
int run_vi2s_p(struct test_error_info *errlist,
               struct prefix_usage_info *pfxinfo) {
  int errcnt = 0;
  // Tests for instruction vi2s.p (Pack integer to short)
  for (unsigned i = 0; i < 128; i++) {
    unsigned int rs_ref[2];
    gen_inputs_u32(i >> 0, &rs_ref[0], 2);
    pfxinfo->inst_name = "vi2s.p";
    pfxinfo->rs_tested = 1;
    pfxinfo->rd_tested = 1;
    {
      unsigned int rs[2];
      pfx_src((uint32_t *)&rs[0], (uint32_t *)&rs_ref[0], 0xdc0000e1, 2);
      unsigned int rd[1] = {0}, rd_out[1] = {0};
      asm volatile("mtvc $0, $131;vmzero.q M400");
      asm volatile("lv.s S000, 0*4(%0)" ::"r"(&rs_ref[0]));
      asm volatile("lv.s S001, 1*4(%0)" ::"r"(&rs_ref[0]));
      rd[0] = ((rs[0 * 2 + 0] >> 16) << 0) | ((rs[0 * 2 + 1] >> 16) << 16);
      ;
      unsigned int *rd_final = &rd[0]; // No dst prefix
      asm volatile(".word 0xdc0000e1" ::: "memory");
      asm volatile(".word 0xd03f0090" ::: "memory");
      asm volatile("sv.s S400, 0*4(%0)" ::"r"(&rd_out[0]));
      int mm = (memcmp(&rd_final[0], &rd_out[0], 1 * sizeof(uint32_t)));
      if (mm) {
        struct test_error_info *rep = &pfxinfo->rs_swz_err;
        static const struct test_decl_info iinfo = {
            .inst = "vi2s.p",
            .instw = 0xd03f0090,
            .pfxw = 0xdc0000e1,
            .rdoutsz = 1,
            .inputs = {
                {.inpname = "rs", .size = 2},
            }};
        fill_errinfo(rep, &iinfo, rd_final, rd_out);
        fill_reg(rep->inputs[0], rs_ref);
        pfxinfo->rs_errors |= (1 << enum_swz);
      }
    }
    {
      unsigned int rs[2];
      pfx_src((uint32_t *)&rs[0], (uint32_t *)&rs_ref[0], 0xdc0500e4, 2);
      unsigned int rd[1] = {0}, rd_out[1] = {0};
      asm volatile("mtvc $0, $131;vmzero.q M400");
      asm volatile("lv.s S000, 0*4(%0)" ::"r"(&rs_ref[0]));
      asm volatile("lv.s S001, 1*4(%0)" ::"r"(&rs_ref[0]));
      rd[0] = ((rs[0 * 2 + 0] >> 16) << 0) | ((rs[0 * 2 + 1] >> 16) << 16);
      ;
      unsigned int *rd_final = &rd[0]; // No dst prefix
      asm volatile(".word 0xdc0500e4" ::: "memory");
      asm volatile(".word 0xd03f0090" ::: "memory");
      asm volatile("sv.s S400, 0*4(%0)" ::"r"(&rd_out[0]));
      int mm = (memcmp(&rd_final[0], &rd_out[0], 1 * sizeof(uint32_t)));
      if (mm) {
        struct test_error_info *rep = &pfxinfo->rs_neg_err;
        static const struct test_decl_info iinfo = {
            .inst = "vi2s.p",
            .instw = 0xd03f0090,
            .pfxw = 0xdc0500e4,
            .rdoutsz = 1,
            .inputs = {
                {.inpname = "rs", .size = 2},
            }};
        fill_errinfo(rep, &iinfo, rd_final, rd_out);
        fill_reg(rep->inputs[0], rs_ref);
        pfxinfo->rs_errors |= (1 << enum_neg);
      }
    }
    {
      unsigned int rs[2];
      pfx_src((uint32_t *)&rs[0], (uint32_t *)&rs_ref[0], 0xdc0a00e4, 2);
      unsigned int rd[1] = {0}, rd_out[1] = {0};
      asm volatile("mtvc $0, $131;vmzero.q M400");
      asm volatile("lv.s S000, 0*4(%0)" ::"r"(&rs_ref[0]));
      asm volatile("lv.s S001, 1*4(%0)" ::"r"(&rs_ref[0]));
      rd[0] = ((rs[0 * 2 + 0] >> 16) << 0) | ((rs[0 * 2 + 1] >> 16) << 16);
      ;
      unsigned int *rd_final = &rd[0]; // No dst prefix
      asm volatile(".word 0xdc0a00e4" ::: "memory");
      asm volatile(".word 0xd03f0090" ::: "memory");
      asm volatile("sv.s S400, 0*4(%0)" ::"r"(&rd_out[0]));
      int mm = (memcmp(&rd_final[0], &rd_out[0], 1 * sizeof(uint32_t)));
      if (mm) {
        struct test_error_info *rep = &pfxinfo->rs_neg_err;
        static const struct test_decl_info iinfo = {
            .inst = "vi2s.p",
            .instw = 0xd03f0090,
            .pfxw = 0xdc0a00e4,
            .rdoutsz = 1,
            .inputs = {
                {.inpname = "rs", .size = 2},
            }};
        fill_errinfo(rep, &iinfo, rd_final, rd_out);
        fill_reg(rep->inputs[0], rs_ref);
        pfxinfo->rs_errors |= (1 << enum_neg);
      }
    }
    {
      unsigned int rs[2];
      pfx_src((uint32_t *)&rs[0], (uint32_t *)&rs_ref[0], 0xdc0f00e4, 2);
      unsigned int rd[1] = {0}, rd_out[1] = {0};
      asm volatile("mtvc $0, $131;vmzero.q M400");
      asm volatile("lv.s S000, 0*4(%0)" ::"r"(&rs_ref[0]));
      asm volatile("lv.s S001, 1*4(%0)" ::"r"(&rs_ref[0]));
      rd[0] = ((rs[0 * 2 + 0] >> 16) << 0) | ((rs[0 * 2 + 1] >> 16) << 16);
      ;
      unsigned int *rd_final = &rd[0]; // No dst prefix
      asm volatile(".word 0xdc0f00e4" ::: "memory");
      asm volatile(".word 0xd03f0090" ::: "memory");
      asm volatile("sv.s S400, 0*4(%0)" ::"r"(&rd_out[0]));
      int mm = (memcmp(&rd_final[0], &rd_out[0], 1 * sizeof(uint32_t)));
      if (mm) {
        struct test_error_info *rep = &pfxinfo->rs_neg_err;
        static const struct test_decl_info iinfo = {
            .inst = "vi2s.p",
            .instw = 0xd03f0090,
            .pfxw = 0xdc0f00e4,
            .rdoutsz = 1,
            .inputs = {
                {.inpname = "rs", .size = 2},
            }};
        fill_errinfo(rep, &iinfo, rd_final, rd_out);
        fill_reg(rep->inputs[0], rs_ref);
        pfxinfo->rs_errors |= (1 << enum_neg);
      }
    }
    {
      unsigned int rs[2];
      pfx_src((uint32_t *)&rs[0], (uint32_t *)&rs_ref[0], 0xdc0005e4, 2);
      unsigned int rd[1] = {0}, rd_out[1] = {0};
      asm volatile("mtvc $0, $131;vmzero.q M400");
      asm volatile("lv.s S000, 0*4(%0)" ::"r"(&rs_ref[0]));
      asm volatile("lv.s S001, 1*4(%0)" ::"r"(&rs_ref[0]));
      rd[0] = ((rs[0 * 2 + 0] >> 16) << 0) | ((rs[0 * 2 + 1] >> 16) << 16);
      ;
      unsigned int *rd_final = &rd[0]; // No dst prefix
      asm volatile(".word 0xdc0005e4" ::: "memory");
      asm volatile(".word 0xd03f0090" ::: "memory");
      asm volatile("sv.s S400, 0*4(%0)" ::"r"(&rd_out[0]));
      int mm = (memcmp(&rd_final[0], &rd_out[0], 1 * sizeof(uint32_t)));
      if (mm) {
        struct test_error_info *rep = &pfxinfo->rs_abs_err;
        static const struct test_decl_info iinfo = {
            .inst = "vi2s.p",
            .instw = 0xd03f0090,
            .pfxw = 0xdc0005e4,
            .rdoutsz = 1,
            .inputs = {
                {.inpname = "rs", .size = 2},
            }};
        fill_errinfo(rep, &iinfo, rd_final, rd_out);
        fill_reg(rep->inputs[0], rs_ref);
        pfxinfo->rs_errors |= (1 << enum_abs);
      }
    }
    {
      unsigned int rs[2];
      pfx_src((uint32_t *)&rs[0], (uint32_t *)&rs_ref[0], 0xdc000ae4, 2);
      unsigned int rd[1] = {0}, rd_out[1] = {0};
      asm volatile("mtvc $0, $131;vmzero.q M400");
      asm volatile("lv.s S000, 0*4(%0)" ::"r"(&rs_ref[0]));
      asm volatile("lv.s S001, 1*4(%0)" ::"r"(&rs_ref[0]));
      rd[0] = ((rs[0 * 2 + 0] >> 16) << 0) | ((rs[0 * 2 + 1] >> 16) << 16);
      ;
      unsigned int *rd_final = &rd[0]; // No dst prefix
      asm volatile(".word 0xdc000ae4" ::: "memory");
      asm volatile(".word 0xd03f0090" ::: "memory");
      asm volatile("sv.s S400, 0*4(%0)" ::"r"(&rd_out[0]));
      int mm = (memcmp(&rd_final[0], &rd_out[0], 1 * sizeof(uint32_t)));
      if (mm) {
        struct test_error_info *rep = &pfxinfo->rs_abs_err;
        static const struct test_decl_info iinfo = {
            .inst = "vi2s.p",
            .instw = 0xd03f0090,
            .pfxw = 0xdc000ae4,
            .rdoutsz = 1,
            .inputs = {
                {.inpname = "rs", .size = 2},
            }};
        fill_errinfo(rep, &iinfo, rd_final, rd_out);
        fill_reg(rep->inputs[0], rs_ref);
        pfxinfo->rs_errors |= (1 << enum_abs);
      }
    }
    {
      unsigned int rs[2];
      pfx_src((uint32_t *)&rs[0], (uint32_t *)&rs_ref[0], 0xdc000fe4, 2);
      unsigned int rd[1] = {0}, rd_out[1] = {0};
      asm volatile("mtvc $0, $131;vmzero.q M400");
      asm volatile("lv.s S000, 0*4(%0)" ::"r"(&rs_ref[0]));
      asm volatile("lv.s S001, 1*4(%0)" ::"r"(&rs_ref[0]));
      rd[0] = ((rs[0 * 2 + 0] >> 16) << 0) | ((rs[0 * 2 + 1] >> 16) << 16);
      ;
      unsigned int *rd_final = &rd[0]; // No dst prefix
      asm volatile(".word 0xdc000fe4" ::: "memory");
      asm volatile(".word 0xd03f0090" ::: "memory");
      asm volatile("sv.s S400, 0*4(%0)" ::"r"(&rd_out[0]));
      int mm = (memcmp(&rd_final[0], &rd_out[0], 1 * sizeof(uint32_t)));
      if (mm) {
        struct test_error_info *rep = &pfxinfo->rs_abs_err;
        static const struct test_decl_info iinfo = {
            .inst = "vi2s.p",
            .instw = 0xd03f0090,
            .pfxw = 0xdc000fe4,
            .rdoutsz = 1,
            .inputs = {
                {.inpname = "rs", .size = 2},
            }};
        fill_errinfo(rep, &iinfo, rd_final, rd_out);
        fill_reg(rep->inputs[0], rs_ref);
        pfxinfo->rs_errors |= (1 << enum_abs);
      }
    }
    {
      unsigned int rs[2];
      pfx_src((uint32_t *)&rs[0], (uint32_t *)&rs_ref[0], 0xdc00f4a7, 2);
      unsigned int rd[1] = {0}, rd_out[1] = {0};
      asm volatile("mtvc $0, $131;vmzero.q M400");
      asm volatile("lv.s S000, 0*4(%0)" ::"r"(&rs_ref[0]));
      asm volatile("lv.s S001, 1*4(%0)" ::"r"(&rs_ref[0]));
      rd[0] = ((rs[0 * 2 + 0] >> 16) << 0) | ((rs[0 * 2 + 1] >> 16) << 16);
      ;
      unsigned int *rd_final = &rd[0]; // No dst prefix
      asm volatile(".word 0xdc00f4a7" ::: "memory");
      asm volatile(".word 0xd03f0090" ::: "memory");
      asm volatile("sv.s S400, 0*4(%0)" ::"r"(&rd_out[0]));
      int mm = (memcmp(&rd_final[0], &rd_out[0], 1 * sizeof(uint32_t)));
      if (mm) {
        struct test_error_info *rep = &pfxinfo->rs_cst_err;
        static const struct test_decl_info iinfo = {
            .inst = "vi2s.p",
            .instw = 0xd03f0090,
            .pfxw = 0xdc00f4a7,
            .rdoutsz = 1,
            .inputs = {
                {.inpname = "rs", .size = 2},
            }};
        fill_errinfo(rep, &iinfo, rd_final, rd_out);
        fill_reg(rep->inputs[0], rs_ref);
        pfxinfo->rs_errors |= (1 << enum_cst);
      }
    }
    {
      unsigned int *rs = &rs_ref[0]; // No src prefix
      unsigned int rd[1] = {0}, rd_out[1] = {0};
      asm volatile("mtvc $0, $131;vmzero.q M400");
      asm volatile("lv.s S000, 0*4(%0)" ::"r"(&rs_ref[0]));
      asm volatile("lv.s S001, 1*4(%0)" ::"r"(&rs_ref[0]));
      rd[0] = ((rs[0 * 2 + 0] >> 16) << 0) | ((rs[0 * 2 + 1] >> 16) << 16);
      ;
      unsigned int rd_final[1] = {0};
      pfx_dst((uint32_t *)&rd_final[0], (uint32_t *)&rd[0], 0xde000f00, 1);
      asm volatile(".word 0xde000f00" ::: "memory");
      asm volatile(".word 0xd03f0090" ::: "memory");
      asm volatile("sv.s S400, 0*4(%0)" ::"r"(&rd_out[0]));
      int mm = (memcmp(&rd_final[0], &rd_out[0], 1 * sizeof(uint32_t)));
      if (mm) {
        struct test_error_info *rep = &pfxinfo->rd_msk_err;
        static const struct test_decl_info iinfo = {
            .inst = "vi2s.p",
            .instw = 0xd03f0090,
            .pfxw = 0xde000f00,
            .rdoutsz = 1,
            .inputs = {
                {.inpname = "rs", .size = 2},
            }};
        fill_errinfo(rep, &iinfo, rd_final, rd_out);
        fill_reg(rep->inputs[0], rs_ref);
        pfxinfo->rd_errors |= (1 << enum_msk);
      }
    }
    {
      unsigned int *rs = &rs_ref[0]; // No src prefix
      unsigned int rd[1] = {0}, rd_out[1] = {0};
      asm volatile("mtvc $0, $131;vmzero.q M400");
      asm volatile("lv.s S000, 0*4(%0)" ::"r"(&rs_ref[0]));
      asm volatile("lv.s S001, 1*4(%0)" ::"r"(&rs_ref[0]));
      rd[0] = ((rs[0 * 2 + 0] >> 16) << 0) | ((rs[0 * 2 + 1] >> 16) << 16);
      ;
      unsigned int rd_final[1] = {0};
      pfx_dst((uint32_t *)&rd_final[0], (uint32_t *)&rd[0], 0xde000055, 1);
      asm volatile(".word 0xde000055" ::: "memory");
      asm volatile(".word 0xd03f0090" ::: "memory");
      asm volatile("sv.s S400, 0*4(%0)" ::"r"(&rd_out[0]));
      int mm = (memcmp(&rd_final[0], &rd_out[0], 1 * sizeof(uint32_t)));
      if (mm) {
        struct test_error_info *rep = &pfxinfo->rd_sat_err;
        static const struct test_decl_info iinfo = {
            .inst = "vi2s.p",
            .instw = 0xd03f0090,
            .pfxw = 0xde000055,
            .rdoutsz = 1,
            .inputs = {
                {.inpname = "rs", .size = 2},
            }};
        fill_errinfo(rep, &iinfo, rd_final, rd_out);
        fill_reg(rep->inputs[0], rs_ref);
        pfxinfo->rd_errors |= (1 << enum_sat);
      }
    }
    {
      unsigned int *rs = &rs_ref[0]; // No src prefix
      unsigned int rd[1] = {0}, rd_out[1] = {0};
      asm volatile("mtvc $0, $131;vmzero.q M400");
      asm volatile("lv.s S000, 0*4(%0)" ::"r"(&rs_ref[0]));
      asm volatile("lv.s S001, 1*4(%0)" ::"r"(&rs_ref[0]));
      rd[0] = ((rs[0 * 2 + 0] >> 16) << 0) | ((rs[0 * 2 + 1] >> 16) << 16);
      ;
      unsigned int rd_final[1] = {0};
      pfx_dst((uint32_t *)&rd_final[0], (uint32_t *)&rd[0], 0xde0000ff, 1);
      asm volatile(".word 0xde0000ff" ::: "memory");
      asm volatile(".word 0xd03f0090" ::: "memory");
      asm volatile("sv.s S400, 0*4(%0)" ::"r"(&rd_out[0]));
      int mm = (memcmp(&rd_final[0], &rd_out[0], 1 * sizeof(uint32_t)));
      if (mm) {
        struct test_error_info *rep = &pfxinfo->rd_sat_err;
        static const struct test_decl_info iinfo = {
            .inst = "vi2s.p",
            .instw = 0xd03f0090,
            .pfxw = 0xde0000ff,
            .rdoutsz = 1,
            .inputs = {
                {.inpname = "rs", .size = 2},
            }};
        fill_errinfo(rep, &iinfo, rd_final, rd_out);
        fill_reg(rep->inputs[0], rs_ref);
        pfxinfo->rd_errors |= (1 << enum_sat);
      }
    }
    {
      unsigned int *rs = &rs_ref[0]; // No src prefix
      unsigned int rd[1] = {0}, rd_out[1] = {0};
      asm volatile("mtvc $0, $131;vmzero.q M400");
      asm volatile("lv.s S000, 0*4(%0)" ::"r"(&rs_ref[0]));
      asm volatile("lv.s S001, 1*4(%0)" ::"r"(&rs_ref[0]));
      rd[0] = ((rs[0 * 2 + 0] >> 16) << 0) | ((rs[0 * 2 + 1] >> 16) << 16);
      ;
      unsigned int *rd_final = &rd[0]; // No dst prefix
      asm volatile(".word 0xd03f0090" ::: "memory");
      asm volatile("sv.s S400, 0*4(%0)" ::"r"(&rd_out[0]));
      int mm = (memcmp(&rd_final[0], &rd_out[0], 1 * sizeof(uint32_t)));
      if (mm) {
        struct test_error_info *rep = &errlist[errcnt];
        static const struct test_decl_info iinfo = {
            .inst = "vi2s.p",
            .instw = 0xd03f0090,
            .pfxw = 0x00000000,
            .rdoutsz = 1,
            .inputs = {
                {.inpname = "rs", .size = 2},
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
int run_vi2s_q(struct test_error_info *errlist,
               struct prefix_usage_info *pfxinfo) {
  int errcnt = 0;
  // Tests for instruction vi2s.q (Pack integer to short)
  for (unsigned i = 0; i < 128; i++) {
    unsigned int rs_ref[4];
    gen_inputs_u32(i >> 0, &rs_ref[0], 4);
    pfxinfo->inst_name = "vi2s.q";
    pfxinfo->rs_tested = 1;
    pfxinfo->rd_tested = 1;
    {
      unsigned int rs[4];
      pfx_src((uint32_t *)&rs[0], (uint32_t *)&rs_ref[0], 0xdc000039, 4);
      unsigned int rd[2] = {0}, rd_out[2] = {0};
      asm volatile("mtvc $0, $131;vmzero.q M400");
      asm volatile("lv.s S000, 0*4(%0)" ::"r"(&rs_ref[0]));
      asm volatile("lv.s S001, 1*4(%0)" ::"r"(&rs_ref[0]));
      asm volatile("lv.s S002, 2*4(%0)" ::"r"(&rs_ref[0]));
      asm volatile("lv.s S003, 3*4(%0)" ::"r"(&rs_ref[0]));
      rd[0] = ((rs[0 * 2 + 0] >> 16) << 0) | ((rs[0 * 2 + 1] >> 16) << 16);
      rd[1] = ((rs[1 * 2 + 0] >> 16) << 0) | ((rs[1 * 2 + 1] >> 16) << 16);
      ;
      unsigned int *rd_final = &rd[0]; // No dst prefix
      asm volatile(".word 0xdc000039" ::: "memory");
      asm volatile(".word 0xd03f8090" ::: "memory");
      asm volatile("sv.s S400, 0*4(%0)" ::"r"(&rd_out[0]));
      asm volatile("sv.s S401, 1*4(%0)" ::"r"(&rd_out[0]));
      int mm = (memcmp(&rd_final[0], &rd_out[0], 2 * sizeof(uint32_t)));
      if (mm) {
        struct test_error_info *rep = &pfxinfo->rs_swz_err;
        static const struct test_decl_info iinfo = {
            .inst = "vi2s.q",
            .instw = 0xd03f8090,
            .pfxw = 0xdc000039,
            .rdoutsz = 2,
            .inputs = {
                {.inpname = "rs", .size = 4},
            }};
        fill_errinfo(rep, &iinfo, rd_final, rd_out);
        fill_reg(rep->inputs[0], rs_ref);
        pfxinfo->rs_errors |= (1 << enum_swz);
      }
    }
    {
      unsigned int rs[4];
      pfx_src((uint32_t *)&rs[0], (uint32_t *)&rs_ref[0], 0xdc0500e4, 4);
      unsigned int rd[2] = {0}, rd_out[2] = {0};
      asm volatile("mtvc $0, $131;vmzero.q M400");
      asm volatile("lv.s S000, 0*4(%0)" ::"r"(&rs_ref[0]));
      asm volatile("lv.s S001, 1*4(%0)" ::"r"(&rs_ref[0]));
      asm volatile("lv.s S002, 2*4(%0)" ::"r"(&rs_ref[0]));
      asm volatile("lv.s S003, 3*4(%0)" ::"r"(&rs_ref[0]));
      rd[0] = ((rs[0 * 2 + 0] >> 16) << 0) | ((rs[0 * 2 + 1] >> 16) << 16);
      rd[1] = ((rs[1 * 2 + 0] >> 16) << 0) | ((rs[1 * 2 + 1] >> 16) << 16);
      ;
      unsigned int *rd_final = &rd[0]; // No dst prefix
      asm volatile(".word 0xdc0500e4" ::: "memory");
      asm volatile(".word 0xd03f8090" ::: "memory");
      asm volatile("sv.s S400, 0*4(%0)" ::"r"(&rd_out[0]));
      asm volatile("sv.s S401, 1*4(%0)" ::"r"(&rd_out[0]));
      int mm = (memcmp(&rd_final[0], &rd_out[0], 2 * sizeof(uint32_t)));
      if (mm) {
        struct test_error_info *rep = &pfxinfo->rs_neg_err;
        static const struct test_decl_info iinfo = {
            .inst = "vi2s.q",
            .instw = 0xd03f8090,
            .pfxw = 0xdc0500e4,
            .rdoutsz = 2,
            .inputs = {
                {.inpname = "rs", .size = 4},
            }};
        fill_errinfo(rep, &iinfo, rd_final, rd_out);
        fill_reg(rep->inputs[0], rs_ref);
        pfxinfo->rs_errors |= (1 << enum_neg);
      }
    }
    {
      unsigned int rs[4];
      pfx_src((uint32_t *)&rs[0], (uint32_t *)&rs_ref[0], 0xdc0a00e4, 4);
      unsigned int rd[2] = {0}, rd_out[2] = {0};
      asm volatile("mtvc $0, $131;vmzero.q M400");
      asm volatile("lv.s S000, 0*4(%0)" ::"r"(&rs_ref[0]));
      asm volatile("lv.s S001, 1*4(%0)" ::"r"(&rs_ref[0]));
      asm volatile("lv.s S002, 2*4(%0)" ::"r"(&rs_ref[0]));
      asm volatile("lv.s S003, 3*4(%0)" ::"r"(&rs_ref[0]));
      rd[0] = ((rs[0 * 2 + 0] >> 16) << 0) | ((rs[0 * 2 + 1] >> 16) << 16);
      rd[1] = ((rs[1 * 2 + 0] >> 16) << 0) | ((rs[1 * 2 + 1] >> 16) << 16);
      ;
      unsigned int *rd_final = &rd[0]; // No dst prefix
      asm volatile(".word 0xdc0a00e4" ::: "memory");
      asm volatile(".word 0xd03f8090" ::: "memory");
      asm volatile("sv.s S400, 0*4(%0)" ::"r"(&rd_out[0]));
      asm volatile("sv.s S401, 1*4(%0)" ::"r"(&rd_out[0]));
      int mm = (memcmp(&rd_final[0], &rd_out[0], 2 * sizeof(uint32_t)));
      if (mm) {
        struct test_error_info *rep = &pfxinfo->rs_neg_err;
        static const struct test_decl_info iinfo = {
            .inst = "vi2s.q",
            .instw = 0xd03f8090,
            .pfxw = 0xdc0a00e4,
            .rdoutsz = 2,
            .inputs = {
                {.inpname = "rs", .size = 4},
            }};
        fill_errinfo(rep, &iinfo, rd_final, rd_out);
        fill_reg(rep->inputs[0], rs_ref);
        pfxinfo->rs_errors |= (1 << enum_neg);
      }
    }
    {
      unsigned int rs[4];
      pfx_src((uint32_t *)&rs[0], (uint32_t *)&rs_ref[0], 0xdc0f00e4, 4);
      unsigned int rd[2] = {0}, rd_out[2] = {0};
      asm volatile("mtvc $0, $131;vmzero.q M400");
      asm volatile("lv.s S000, 0*4(%0)" ::"r"(&rs_ref[0]));
      asm volatile("lv.s S001, 1*4(%0)" ::"r"(&rs_ref[0]));
      asm volatile("lv.s S002, 2*4(%0)" ::"r"(&rs_ref[0]));
      asm volatile("lv.s S003, 3*4(%0)" ::"r"(&rs_ref[0]));
      rd[0] = ((rs[0 * 2 + 0] >> 16) << 0) | ((rs[0 * 2 + 1] >> 16) << 16);
      rd[1] = ((rs[1 * 2 + 0] >> 16) << 0) | ((rs[1 * 2 + 1] >> 16) << 16);
      ;
      unsigned int *rd_final = &rd[0]; // No dst prefix
      asm volatile(".word 0xdc0f00e4" ::: "memory");
      asm volatile(".word 0xd03f8090" ::: "memory");
      asm volatile("sv.s S400, 0*4(%0)" ::"r"(&rd_out[0]));
      asm volatile("sv.s S401, 1*4(%0)" ::"r"(&rd_out[0]));
      int mm = (memcmp(&rd_final[0], &rd_out[0], 2 * sizeof(uint32_t)));
      if (mm) {
        struct test_error_info *rep = &pfxinfo->rs_neg_err;
        static const struct test_decl_info iinfo = {
            .inst = "vi2s.q",
            .instw = 0xd03f8090,
            .pfxw = 0xdc0f00e4,
            .rdoutsz = 2,
            .inputs = {
                {.inpname = "rs", .size = 4},
            }};
        fill_errinfo(rep, &iinfo, rd_final, rd_out);
        fill_reg(rep->inputs[0], rs_ref);
        pfxinfo->rs_errors |= (1 << enum_neg);
      }
    }
    {
      unsigned int rs[4];
      pfx_src((uint32_t *)&rs[0], (uint32_t *)&rs_ref[0], 0xdc0005e4, 4);
      unsigned int rd[2] = {0}, rd_out[2] = {0};
      asm volatile("mtvc $0, $131;vmzero.q M400");
      asm volatile("lv.s S000, 0*4(%0)" ::"r"(&rs_ref[0]));
      asm volatile("lv.s S001, 1*4(%0)" ::"r"(&rs_ref[0]));
      asm volatile("lv.s S002, 2*4(%0)" ::"r"(&rs_ref[0]));
      asm volatile("lv.s S003, 3*4(%0)" ::"r"(&rs_ref[0]));
      rd[0] = ((rs[0 * 2 + 0] >> 16) << 0) | ((rs[0 * 2 + 1] >> 16) << 16);
      rd[1] = ((rs[1 * 2 + 0] >> 16) << 0) | ((rs[1 * 2 + 1] >> 16) << 16);
      ;
      unsigned int *rd_final = &rd[0]; // No dst prefix
      asm volatile(".word 0xdc0005e4" ::: "memory");
      asm volatile(".word 0xd03f8090" ::: "memory");
      asm volatile("sv.s S400, 0*4(%0)" ::"r"(&rd_out[0]));
      asm volatile("sv.s S401, 1*4(%0)" ::"r"(&rd_out[0]));
      int mm = (memcmp(&rd_final[0], &rd_out[0], 2 * sizeof(uint32_t)));
      if (mm) {
        struct test_error_info *rep = &pfxinfo->rs_abs_err;
        static const struct test_decl_info iinfo = {
            .inst = "vi2s.q",
            .instw = 0xd03f8090,
            .pfxw = 0xdc0005e4,
            .rdoutsz = 2,
            .inputs = {
                {.inpname = "rs", .size = 4},
            }};
        fill_errinfo(rep, &iinfo, rd_final, rd_out);
        fill_reg(rep->inputs[0], rs_ref);
        pfxinfo->rs_errors |= (1 << enum_abs);
      }
    }
    {
      unsigned int rs[4];
      pfx_src((uint32_t *)&rs[0], (uint32_t *)&rs_ref[0], 0xdc000ae4, 4);
      unsigned int rd[2] = {0}, rd_out[2] = {0};
      asm volatile("mtvc $0, $131;vmzero.q M400");
      asm volatile("lv.s S000, 0*4(%0)" ::"r"(&rs_ref[0]));
      asm volatile("lv.s S001, 1*4(%0)" ::"r"(&rs_ref[0]));
      asm volatile("lv.s S002, 2*4(%0)" ::"r"(&rs_ref[0]));
      asm volatile("lv.s S003, 3*4(%0)" ::"r"(&rs_ref[0]));
      rd[0] = ((rs[0 * 2 + 0] >> 16) << 0) | ((rs[0 * 2 + 1] >> 16) << 16);
      rd[1] = ((rs[1 * 2 + 0] >> 16) << 0) | ((rs[1 * 2 + 1] >> 16) << 16);
      ;
      unsigned int *rd_final = &rd[0]; // No dst prefix
      asm volatile(".word 0xdc000ae4" ::: "memory");
      asm volatile(".word 0xd03f8090" ::: "memory");
      asm volatile("sv.s S400, 0*4(%0)" ::"r"(&rd_out[0]));
      asm volatile("sv.s S401, 1*4(%0)" ::"r"(&rd_out[0]));
      int mm = (memcmp(&rd_final[0], &rd_out[0], 2 * sizeof(uint32_t)));
      if (mm) {
        struct test_error_info *rep = &pfxinfo->rs_abs_err;
        static const struct test_decl_info iinfo = {
            .inst = "vi2s.q",
            .instw = 0xd03f8090,
            .pfxw = 0xdc000ae4,
            .rdoutsz = 2,
            .inputs = {
                {.inpname = "rs", .size = 4},
            }};
        fill_errinfo(rep, &iinfo, rd_final, rd_out);
        fill_reg(rep->inputs[0], rs_ref);
        pfxinfo->rs_errors |= (1 << enum_abs);
      }
    }
    {
      unsigned int rs[4];
      pfx_src((uint32_t *)&rs[0], (uint32_t *)&rs_ref[0], 0xdc000fe4, 4);
      unsigned int rd[2] = {0}, rd_out[2] = {0};
      asm volatile("mtvc $0, $131;vmzero.q M400");
      asm volatile("lv.s S000, 0*4(%0)" ::"r"(&rs_ref[0]));
      asm volatile("lv.s S001, 1*4(%0)" ::"r"(&rs_ref[0]));
      asm volatile("lv.s S002, 2*4(%0)" ::"r"(&rs_ref[0]));
      asm volatile("lv.s S003, 3*4(%0)" ::"r"(&rs_ref[0]));
      rd[0] = ((rs[0 * 2 + 0] >> 16) << 0) | ((rs[0 * 2 + 1] >> 16) << 16);
      rd[1] = ((rs[1 * 2 + 0] >> 16) << 0) | ((rs[1 * 2 + 1] >> 16) << 16);
      ;
      unsigned int *rd_final = &rd[0]; // No dst prefix
      asm volatile(".word 0xdc000fe4" ::: "memory");
      asm volatile(".word 0xd03f8090" ::: "memory");
      asm volatile("sv.s S400, 0*4(%0)" ::"r"(&rd_out[0]));
      asm volatile("sv.s S401, 1*4(%0)" ::"r"(&rd_out[0]));
      int mm = (memcmp(&rd_final[0], &rd_out[0], 2 * sizeof(uint32_t)));
      if (mm) {
        struct test_error_info *rep = &pfxinfo->rs_abs_err;
        static const struct test_decl_info iinfo = {
            .inst = "vi2s.q",
            .instw = 0xd03f8090,
            .pfxw = 0xdc000fe4,
            .rdoutsz = 2,
            .inputs = {
                {.inpname = "rs", .size = 4},
            }};
        fill_errinfo(rep, &iinfo, rd_final, rd_out);
        fill_reg(rep->inputs[0], rs_ref);
        pfxinfo->rs_errors |= (1 << enum_abs);
      }
    }
    {
      unsigned int rs[4];
      pfx_src((uint32_t *)&rs[0], (uint32_t *)&rs_ref[0], 0xdc00f4a7, 4);
      unsigned int rd[2] = {0}, rd_out[2] = {0};
      asm volatile("mtvc $0, $131;vmzero.q M400");
      asm volatile("lv.s S000, 0*4(%0)" ::"r"(&rs_ref[0]));
      asm volatile("lv.s S001, 1*4(%0)" ::"r"(&rs_ref[0]));
      asm volatile("lv.s S002, 2*4(%0)" ::"r"(&rs_ref[0]));
      asm volatile("lv.s S003, 3*4(%0)" ::"r"(&rs_ref[0]));
      rd[0] = ((rs[0 * 2 + 0] >> 16) << 0) | ((rs[0 * 2 + 1] >> 16) << 16);
      rd[1] = ((rs[1 * 2 + 0] >> 16) << 0) | ((rs[1 * 2 + 1] >> 16) << 16);
      ;
      unsigned int *rd_final = &rd[0]; // No dst prefix
      asm volatile(".word 0xdc00f4a7" ::: "memory");
      asm volatile(".word 0xd03f8090" ::: "memory");
      asm volatile("sv.s S400, 0*4(%0)" ::"r"(&rd_out[0]));
      asm volatile("sv.s S401, 1*4(%0)" ::"r"(&rd_out[0]));
      int mm = (memcmp(&rd_final[0], &rd_out[0], 2 * sizeof(uint32_t)));
      if (mm) {
        struct test_error_info *rep = &pfxinfo->rs_cst_err;
        static const struct test_decl_info iinfo = {
            .inst = "vi2s.q",
            .instw = 0xd03f8090,
            .pfxw = 0xdc00f4a7,
            .rdoutsz = 2,
            .inputs = {
                {.inpname = "rs", .size = 4},
            }};
        fill_errinfo(rep, &iinfo, rd_final, rd_out);
        fill_reg(rep->inputs[0], rs_ref);
        pfxinfo->rs_errors |= (1 << enum_cst);
      }
    }
    {
      unsigned int *rs = &rs_ref[0]; // No src prefix
      unsigned int rd[2] = {0}, rd_out[2] = {0};
      asm volatile("mtvc $0, $131;vmzero.q M400");
      asm volatile("lv.s S000, 0*4(%0)" ::"r"(&rs_ref[0]));
      asm volatile("lv.s S001, 1*4(%0)" ::"r"(&rs_ref[0]));
      asm volatile("lv.s S002, 2*4(%0)" ::"r"(&rs_ref[0]));
      asm volatile("lv.s S003, 3*4(%0)" ::"r"(&rs_ref[0]));
      rd[0] = ((rs[0 * 2 + 0] >> 16) << 0) | ((rs[0 * 2 + 1] >> 16) << 16);
      rd[1] = ((rs[1 * 2 + 0] >> 16) << 0) | ((rs[1 * 2 + 1] >> 16) << 16);
      ;
      unsigned int rd_final[2] = {0};
      pfx_dst((uint32_t *)&rd_final[0], (uint32_t *)&rd[0], 0xde000f00, 2);
      asm volatile(".word 0xde000f00" ::: "memory");
      asm volatile(".word 0xd03f8090" ::: "memory");
      asm volatile("sv.s S400, 0*4(%0)" ::"r"(&rd_out[0]));
      asm volatile("sv.s S401, 1*4(%0)" ::"r"(&rd_out[0]));
      int mm = (memcmp(&rd_final[0], &rd_out[0], 2 * sizeof(uint32_t)));
      if (mm) {
        struct test_error_info *rep = &pfxinfo->rd_msk_err;
        static const struct test_decl_info iinfo = {
            .inst = "vi2s.q",
            .instw = 0xd03f8090,
            .pfxw = 0xde000f00,
            .rdoutsz = 2,
            .inputs = {
                {.inpname = "rs", .size = 4},
            }};
        fill_errinfo(rep, &iinfo, rd_final, rd_out);
        fill_reg(rep->inputs[0], rs_ref);
        pfxinfo->rd_errors |= (1 << enum_msk);
      }
    }
    {
      unsigned int *rs = &rs_ref[0]; // No src prefix
      unsigned int rd[2] = {0}, rd_out[2] = {0};
      asm volatile("mtvc $0, $131;vmzero.q M400");
      asm volatile("lv.s S000, 0*4(%0)" ::"r"(&rs_ref[0]));
      asm volatile("lv.s S001, 1*4(%0)" ::"r"(&rs_ref[0]));
      asm volatile("lv.s S002, 2*4(%0)" ::"r"(&rs_ref[0]));
      asm volatile("lv.s S003, 3*4(%0)" ::"r"(&rs_ref[0]));
      rd[0] = ((rs[0 * 2 + 0] >> 16) << 0) | ((rs[0 * 2 + 1] >> 16) << 16);
      rd[1] = ((rs[1 * 2 + 0] >> 16) << 0) | ((rs[1 * 2 + 1] >> 16) << 16);
      ;
      unsigned int rd_final[2] = {0};
      pfx_dst((uint32_t *)&rd_final[0], (uint32_t *)&rd[0], 0xde000055, 2);
      asm volatile(".word 0xde000055" ::: "memory");
      asm volatile(".word 0xd03f8090" ::: "memory");
      asm volatile("sv.s S400, 0*4(%0)" ::"r"(&rd_out[0]));
      asm volatile("sv.s S401, 1*4(%0)" ::"r"(&rd_out[0]));
      int mm = (memcmp(&rd_final[0], &rd_out[0], 2 * sizeof(uint32_t)));
      if (mm) {
        struct test_error_info *rep = &pfxinfo->rd_sat_err;
        static const struct test_decl_info iinfo = {
            .inst = "vi2s.q",
            .instw = 0xd03f8090,
            .pfxw = 0xde000055,
            .rdoutsz = 2,
            .inputs = {
                {.inpname = "rs", .size = 4},
            }};
        fill_errinfo(rep, &iinfo, rd_final, rd_out);
        fill_reg(rep->inputs[0], rs_ref);
        pfxinfo->rd_errors |= (1 << enum_sat);
      }
    }
    {
      unsigned int *rs = &rs_ref[0]; // No src prefix
      unsigned int rd[2] = {0}, rd_out[2] = {0};
      asm volatile("mtvc $0, $131;vmzero.q M400");
      asm volatile("lv.s S000, 0*4(%0)" ::"r"(&rs_ref[0]));
      asm volatile("lv.s S001, 1*4(%0)" ::"r"(&rs_ref[0]));
      asm volatile("lv.s S002, 2*4(%0)" ::"r"(&rs_ref[0]));
      asm volatile("lv.s S003, 3*4(%0)" ::"r"(&rs_ref[0]));
      rd[0] = ((rs[0 * 2 + 0] >> 16) << 0) | ((rs[0 * 2 + 1] >> 16) << 16);
      rd[1] = ((rs[1 * 2 + 0] >> 16) << 0) | ((rs[1 * 2 + 1] >> 16) << 16);
      ;
      unsigned int rd_final[2] = {0};
      pfx_dst((uint32_t *)&rd_final[0], (uint32_t *)&rd[0], 0xde0000ff, 2);
      asm volatile(".word 0xde0000ff" ::: "memory");
      asm volatile(".word 0xd03f8090" ::: "memory");
      asm volatile("sv.s S400, 0*4(%0)" ::"r"(&rd_out[0]));
      asm volatile("sv.s S401, 1*4(%0)" ::"r"(&rd_out[0]));
      int mm = (memcmp(&rd_final[0], &rd_out[0], 2 * sizeof(uint32_t)));
      if (mm) {
        struct test_error_info *rep = &pfxinfo->rd_sat_err;
        static const struct test_decl_info iinfo = {
            .inst = "vi2s.q",
            .instw = 0xd03f8090,
            .pfxw = 0xde0000ff,
            .rdoutsz = 2,
            .inputs = {
                {.inpname = "rs", .size = 4},
            }};
        fill_errinfo(rep, &iinfo, rd_final, rd_out);
        fill_reg(rep->inputs[0], rs_ref);
        pfxinfo->rd_errors |= (1 << enum_sat);
      }
    }
    {
      unsigned int *rs = &rs_ref[0]; // No src prefix
      unsigned int rd[2] = {0}, rd_out[2] = {0};
      asm volatile("mtvc $0, $131;vmzero.q M400");
      asm volatile("lv.s S000, 0*4(%0)" ::"r"(&rs_ref[0]));
      asm volatile("lv.s S001, 1*4(%0)" ::"r"(&rs_ref[0]));
      asm volatile("lv.s S002, 2*4(%0)" ::"r"(&rs_ref[0]));
      asm volatile("lv.s S003, 3*4(%0)" ::"r"(&rs_ref[0]));
      rd[0] = ((rs[0 * 2 + 0] >> 16) << 0) | ((rs[0 * 2 + 1] >> 16) << 16);
      rd[1] = ((rs[1 * 2 + 0] >> 16) << 0) | ((rs[1 * 2 + 1] >> 16) << 16);
      ;
      unsigned int *rd_final = &rd[0]; // No dst prefix
      asm volatile(".word 0xd03f8090" ::: "memory");
      asm volatile("sv.s S400, 0*4(%0)" ::"r"(&rd_out[0]));
      asm volatile("sv.s S401, 1*4(%0)" ::"r"(&rd_out[0]));
      int mm = (memcmp(&rd_final[0], &rd_out[0], 2 * sizeof(uint32_t)));
      if (mm) {
        struct test_error_info *rep = &errlist[errcnt];
        static const struct test_decl_info iinfo = {
            .inst = "vi2s.q",
            .instw = 0xd03f8090,
            .pfxw = 0x00000000,
            .rdoutsz = 2,
            .inputs = {
                {.inpname = "rs", .size = 4},
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
