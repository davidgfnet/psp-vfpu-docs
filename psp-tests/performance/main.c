
#include <pspkernel.h>
#include <psppower.h>
#include <pspthreadman.h>
#include <kubridge.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "test-utils.h"

PSP_MODULE_INFO("PSP VFPU perf test", 0, 1, 1);
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER | THREAD_ATTR_VFPU);

void perf_tests();

#define JUMP_BVT()   \
	"bvt 0, 2f;"     \
	"nop; nop; nop; nop; nop; nop; nop; nop; nop; 2:\n"

#define JUMP_BVF()   \
	"bvf 0, 2f;"     \
	"nop; nop; nop; nop; nop; nop; nop; nop; nop; 2:\n"

#define JUMP_BVTL()  \
	"bvtl 0, 2f;"    \
	"nop; nop; nop; nop; nop; nop; nop; nop; nop; 2:\n"

#define JUMP_BVFL()  \
	"bvfl 0, 2f;"    \
	"nop; nop; nop; nop; nop; nop; nop; nop; nop; 2:\n"

#define JUMP_J()     \
	"j 2f\n"         \
	"nop; nop; nop; nop; nop; nop; nop; nop; nop; 2:\n"

#define VCMP_B()     \
	"vcmp.q NE, R000.q, R000.q\n"   \
	"bvt 0, 1b\n nop\n" \

#define REP8(mc)     \
  mc() mc() mc() mc() mc() mc() mc() mc()

#define REP64(mc)    \
  REP8(mc) REP8(mc) REP8(mc) REP8(mc) REP8(mc) REP8(mc) REP8(mc) REP8(mc)

int main() {
	scePowerSetClockFrequency(333, 333, 166);
	#ifdef _BUILD_EBOOT_
	pspDebugScreenInit();
	logfd = fopen("ms0://test_performance_results.txt", "wb");
	#endif

	logprintf(">>>>>>> Instruction performance tests <<<<<<\n");
	logprintf("PSP model: %d\n", kuKernelGetModel());

	// Calculate jump-to-fetch latency
	// This is the number of cycles "lost" by a branch (minus one due to delay slot)

	uint64_t stt0 = sceKernelGetSystemTimeWide();
	asm volatile(
		".set noreorder\n"
		"vzero.q R000.q\n"
		"vcmp.q EQ, R000.q, R000.q\n"   // Force bits to one
		"li $a3, 16384\n"
		"1: \n"
		REP64(JUMP_BVT) REP64(JUMP_BVT)
		REP64(JUMP_BVT) REP64(JUMP_BVT)
		"sub $a3, $a3, 1\n"
		"bnez $a3, 1b\n nop \n"
		".set reorder\n"
	::: "$a3", "memory");
	uint64_t end0 = sceKernelGetSystemTimeWide();
	unsigned cyclt0 = (unsigned)(end0 - stt0) * 333;
	logprintf("bvt latency: %f\n", cyclt0 / (float)(256 * 16384));

	uint64_t stt1 = sceKernelGetSystemTimeWide();
	asm volatile(
		".set noreorder\n"
		"vzero.q R000.q\n"
		"vcmp.q NE, R000.q, R000.q\n"   // Force bits to zero
		"li $a3, 16384;"
		"1: \n"
		REP64(JUMP_BVF) REP64(JUMP_BVF)
		REP64(JUMP_BVF) REP64(JUMP_BVF)
		"sub $a3, $a3, 1\n"
		"bnez $a3, 1b\n nop \n"
		".set reorder\n"
	::: "$a3", "memory");
	uint64_t end1 = sceKernelGetSystemTimeWide();
	unsigned cyclt1 = (unsigned)(end1 - stt1) * 333;
	logprintf("bvf latency: %f\n", cyclt1 / (float)(256 * 16384));

	uint64_t stt2 = sceKernelGetSystemTimeWide();
	asm volatile(
		".set noreorder\n"
		"vzero.q R000.q\n"
		"vcmp.q EQ, R000.q, R000.q\n"
		"li $a3, 16384\n"
		"1: \n"
		REP64(JUMP_BVTL) REP64(JUMP_BVTL)
		REP64(JUMP_BVTL) REP64(JUMP_BVTL)
		"sub $a3, $a3, 1\n"
		"bnez $a3, 1b\n nop \n"
		".set reorder\n"
	::: "$a3", "memory");
	uint64_t end2 = sceKernelGetSystemTimeWide();
	unsigned cyclt2 = (unsigned)(end2 - stt2) * 333;
	logprintf("bvtl latency: %f\n", cyclt2 / (float)(256 * 16384));

	uint64_t stt3 = sceKernelGetSystemTimeWide();
	asm volatile(
		".set noreorder\n"
		"vzero.q R000.q\n"
		"vcmp.q NE, R000.q, R000.q\n"
		"li $a3, 16384;"
		"1: \n"
		REP64(JUMP_BVFL) REP64(JUMP_BVFL)
		REP64(JUMP_BVFL) REP64(JUMP_BVFL)
		"sub $a3, $a3, 1\n"
		"bnez $a3, 1b\n nop \n"
		".set reorder\n"
	::: "$a3", "memory");
	uint64_t end3 = sceKernelGetSystemTimeWide();
	unsigned cyclt3 = (unsigned)(end3 - stt3) * 333;
	logprintf("bvfl latency: %f\n", cyclt3 / (float)(256 * 16384));

	uint64_t stt4 = sceKernelGetSystemTimeWide();
	asm volatile(
		".set noreorder\n"
		"li $a3, 16384;"
		"1: \n"
		REP64(JUMP_J) REP64(JUMP_J)
		REP64(JUMP_J) REP64(JUMP_J)
		"sub $a3, $a3, 1\n"
		"bnez $a3, 1b\n nop \n"
		".set reorder\n"
	::: "$a3", "memory");
	uint64_t end4 = sceKernelGetSystemTimeWide();
	unsigned cyclt4 = (unsigned)(end4 - stt4) * 333;
	logprintf("j latency: %f\n", cyclt4 / (float)(256 * 16384));


	// Calculate vcmp to bvt/f latency
	// (latency for vcmp->mfvc is different)
	// This is the number of cycles that are "lost" between compare and jump
	// (latency can be hidden by adding instructions in between)

	uint64_t stt5 = sceKernelGetSystemTimeWide();
	asm volatile(
		".set noreorder\n"
		"vzero.q R000.q\n"
		"li $a3, 16384;"
		"1: \n"
		REP64(VCMP_B) REP64(VCMP_B)
		REP64(VCMP_B) REP64(VCMP_B)
		"sub $a3, $a3, 1\n"
		"bnez $a3, 1b\n nop \n"
		".set reorder\n"
	::: "$a3", "memory");
	uint64_t end5 = sceKernelGetSystemTimeWide();
	unsigned cyclt5 = (unsigned)(end5 - stt5) * 333;
	// Remote 1 cycle for branch, 1 for nop
	logprintf("vcmp latency: %f\n", cyclt5 / (float)(256 * 16384) - 2);

	// Run automated tests
	perf_tests();

	#ifdef _BUILD_EBOOT_
	fclose(logfd);
	#endif
	sceKernelExitGame();
}


