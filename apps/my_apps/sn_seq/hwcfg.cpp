/**
 * hwcfg.cpp
 * 
 * See header file for more info.
 * 
 * Adam Schabtach
 * April 2023
 * 
 */

#include <mios32.h>
#include "hwcfg.h"
const mios32_enc_config_t my_enc_config[HWCFG_NUM_ENCODERS] = {
  { .cfg = {.type=DETENTED3, .speed=NORMAL, .speed_par=0, .pos=1 , .sr= 2} }, // GP1
  { .cfg = {.type=DETENTED3, .speed=NORMAL, .speed_par=0, .pos=3 , .sr= 2} }, // GP2
  { .cfg = {.type=DETENTED3, .speed=NORMAL, .speed_par=0, .pos=5 , .sr= 2} }, // GP3
  { .cfg = {.type=DETENTED3, .speed=NORMAL, .speed_par=0, .pos=7 , .sr= 2} }, // GP4
  { .cfg = {.type=DETENTED3, .speed=NORMAL, .speed_par=0, .pos=1 , .sr= 4} }, // GP5
  { .cfg = {.type=DETENTED3, .speed=NORMAL, .speed_par=0, .pos=3 , .sr= 4} }, // GP6
  { .cfg = {.type=DETENTED3, .speed=NORMAL, .speed_par=0, .pos=5 , .sr= 4} }, // GP7
  { .cfg = {.type=DETENTED3, .speed=NORMAL, .speed_par=0, .pos=7 , .sr= 4} }, // GP8
  { .cfg = {.type=DETENTED3, .speed=NORMAL, .speed_par=0, .pos=1 , .sr= 5} }, // GP9
  { .cfg = {.type=DETENTED3, .speed=NORMAL, .speed_par=0, .pos=3 , .sr= 5} }, // GP10
  { .cfg = {.type=DETENTED3, .speed=NORMAL, .speed_par=0, .pos=5 , .sr= 5} }, // GP11
  { .cfg = {.type=DETENTED3, .speed=NORMAL, .speed_par=0, .pos=7 , .sr= 5} }, // GP12
  { .cfg = {.type=DETENTED3, .speed=NORMAL, .speed_par=0, .pos=1 , .sr= 7} }, // GP13
  { .cfg = {.type=DETENTED3, .speed=NORMAL, .speed_par=0, .pos=3 , .sr= 7} }, // GP14
  { .cfg = {.type=DETENTED3, .speed=NORMAL, .speed_par=0, .pos=5 , .sr= 7} }, // GP15
  { .cfg = {.type=DETENTED3, .speed=NORMAL, .speed_par=0, .pos=7 , .sr= 7} }, // GP16
  { .cfg = {.type = DETENTED3, .speed = NORMAL, .speed_par = 0, .pos = 7, .sr = 1} } // Data Wheel
};

void hwcfg_init()
{
  int i;

  // initialize encoders
  for (i = 0; i < HWCFG_NUM_ENCODERS; ++i)
    MIOS32_ENC_ConfigSet(i, my_enc_config[i]);

  // using 16 SRs by default, can be increased to up to 23 SRs
  MIOS32_SRIO_ScanNumSet(16);
#if 0
  // disable gate SRs
  for (i = 0; i < SEQ_HWCFG_NUM_SR_DOUT_GATES; ++i)
    seq_hwcfg_dout_gate_sr[i] = 0;
  for (i = 0; i < SEQ_HWCFG_NUM_SR_CV_GATES; ++i)
    seq_hwcfg_cv_gate_sr[i] = 0;

#if !defined(SEQ_DONT_USE_BLM8X8)
  // initial debounce delay for BLM8x8
  {
    int blm;

    for (blm = 0; blm < SEQ_BLM8X8_NUM; ++blm) {
      seq_blm8x8_config_t config = SEQ_BLM8X8_ConfigGet(blm);
      config.debounce_delay = 20; // mS
      SEQ_BLM8X8_ConfigSet(blm, config);
    }
  }
#endif
#endif
}
