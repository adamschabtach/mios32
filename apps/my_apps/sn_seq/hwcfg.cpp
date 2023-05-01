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

static const mios32_enc_config_t enc_config[HWCFG_NUM_ENCODERS] = {
	// data wheel
  { .cfg.type=DETENTED3, .cfg.speed=NORMAL, .cfg.speed_par=0, .cfg.sr= 1, .cfg.pos=7 }, // Data Wheel
	// step encoders
  { .cfg.type=DETENTED3, .cfg.speed=NORMAL, .cfg.speed_par=0, .cfg.sr= 2, .cfg.pos=1 }, // GP1
  { .cfg.type=DETENTED3, .cfg.speed=NORMAL, .cfg.speed_par=0, .cfg.sr= 2, .cfg.pos=3 }, // GP2
  { .cfg.type=DETENTED3, .cfg.speed=NORMAL, .cfg.speed_par=0, .cfg.sr= 2, .cfg.pos=5 }, // GP3
  { .cfg.type=DETENTED3, .cfg.speed=NORMAL, .cfg.speed_par=0, .cfg.sr= 2, .cfg.pos=7 }, // GP4

  { .cfg.type=DETENTED3, .cfg.speed=NORMAL, .cfg.speed_par=0, .cfg.sr= 4, .cfg.pos=1 }, // GP5
  { .cfg.type=DETENTED3, .cfg.speed=NORMAL, .cfg.speed_par=0, .cfg.sr= 4, .cfg.pos=3 }, // GP6
  { .cfg.type=DETENTED3, .cfg.speed=NORMAL, .cfg.speed_par=0, .cfg.sr= 4, .cfg.pos=5 }, // GP7
  { .cfg.type=DETENTED3, .cfg.speed=NORMAL, .cfg.speed_par=0, .cfg.sr= 4, .cfg.pos=7 }, // GP8
  
  { .cfg.type=DETENTED3, .cfg.speed=NORMAL, .cfg.speed_par=0, .cfg.sr= 5, .cfg.pos=1 }, // GP9
  { .cfg.type=DETENTED3, .cfg.speed=NORMAL, .cfg.speed_par=0, .cfg.sr= 5, .cfg.pos=3 }, // GP10
  { .cfg.type=DETENTED3, .cfg.speed=NORMAL, .cfg.speed_par=0, .cfg.sr= 5, .cfg.pos=5 }, // GP11
  { .cfg.type=DETENTED3, .cfg.speed=NORMAL, .cfg.speed_par=0, .cfg.sr= 5, .cfg.pos=7 }, // GP12

  { .cfg.type=DETENTED3, .cfg.speed=NORMAL, .cfg.speed_par=0, .cfg.sr= 7, .cfg.pos=1 }, // GP13
  { .cfg.type=DETENTED3, .cfg.speed=NORMAL, .cfg.speed_par=0, .cfg.sr= 7, .cfg.pos=3 }, // GP14
  { .cfg.type=DETENTED3, .cfg.speed=NORMAL, .cfg.speed_par=0, .cfg.sr= 7, .cfg.pos=5 }, // GP15
  { .cfg.type=DETENTED3, .cfg.speed=NORMAL, .cfg.speed_par=0, .cfg.sr= 7, .cfg.pos=7 }, // GP16
};