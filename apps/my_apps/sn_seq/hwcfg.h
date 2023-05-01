/**
 * hwcfg.h
 * 
 * Declarations for setting up the hardware configuration. Eventually
 * this should be replaced by the seqv4 code which loads configurations
 * from the SD card, but I don't know whether I'll get that far with
 * this project. For now I'm just making it work on my hardware.
 * 
 * Adam Schabtach
 * April 2023
 * 
 */

#pragma once

#define HWCFG_NUM_ENCODERS 17

extern const mios32_enc_config_t my_enc_config[HWCFG_NUM_ENCODERS];

void hwcfg_init();
