/****************************************************************************
 * arch/risc-v/src/esp32c3/hardware/esp32c3_gpio_sigmap.h
 *
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.  The
 * ASF licenses this file to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance with the
 * License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  See the
 * License for the specific language governing permissions and limitations
 * under the License.
 *
 ****************************************************************************/

#ifndef __ARCH_RISCV_SRC_ESP32C3_HARDWARE_ESP32C3_GPIO_SIGMAP_H
#define __ARCH_RISCV_SRC_ESP32C3_HARDWARE_ESP32C3_GPIO_SIGMAP_H

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

#define SPICLK_OUT_MUX_IDX            SPICLK_OUT_IDX
#define SPIQ_IN_IDX                   0
#define SPIQ_OUT_IDX                  0
#define SPID_IN_IDX                   1
#define SPID_OUT_IDX                  1
#define SPIHD_IN_IDX                  2
#define SPIHD_OUT_IDX                 2
#define SPIWP_IN_IDX                  3
#define SPIWP_OUT_IDX                 3
#define SPICLK_OUT_IDX                4
#define SPICS0_OUT_IDX                5
#define U0RXD_IN_IDX                  6
#define U0TXD_OUT_IDX                 6
#define U0CTS_IN_IDX                  7
#define U0RTS_OUT_IDX                 7
#define U0DSR_IN_IDX                  8
#define U0DTR_OUT_IDX                 8
#define U1RXD_IN_IDX                  9
#define U1TXD_OUT_IDX                 9
#define U1CTS_IN_IDX                  10
#define U1RTS_OUT_IDX                 10
#define U1DSR_IN_IDX                  11
#define U1DTR_OUT_IDX                 11
#define I2S_MCLK_IN_IDX               12
#define I2S_MCLK_OUT_IDX              12
#define I2SO_BCK_IN_IDX               13
#define I2SO_BCK_OUT_IDX              13
#define I2SO_WS_IN_IDX                14
#define I2SO_WS_OUT_IDX               14
#define I2SI_SD_IN_IDX                15
#define I2SO_SD_OUT_IDX               15
#define I2SI_BCK_IN_IDX               16
#define I2SI_BCK_OUT_IDX              16
#define I2SI_WS_IN_IDX                17
#define I2SI_WS_OUT_IDX               17
#define GPIO_BT_PRIORITY_IDX          18
#define GPIO_WLAN_PRIO_IDX            18
#define GPIO_BT_ACTIVE_IDX            19
#define GPIO_WLAN_ACTIVE_IDX          19
#define BB_DIAG0_IDX                  20
#define BB_DIAG1_IDX                  21
#define BB_DIAG2_IDX                  22
#define BB_DIAG3_IDX                  23
#define BB_DIAG4_IDX                  24
#define BB_DIAG5_IDX                  25
#define BB_DIAG6_IDX                  26
#define BB_DIAG7_IDX                  27
#define BB_DIAG8_IDX                  28
#define BB_DIAG9_IDX                  29
#define BB_DIAG10_IDX                 30
#define BB_DIAG11_IDX                 31
#define BB_DIAG12_IDX                 32
#define BB_DIAG13_IDX                 33
#define BB_DIAG14_IDX                 34
#define BB_DIAG15_IDX                 35
#define BB_DIAG16_IDX                 36
#define BB_DIAG17_IDX                 37
#define BB_DIAG18_IDX                 38
#define BB_DIAG19_IDX                 39
#define USB_EXTPHY_VP_IDX             40
#define USB_EXTPHY_OEN_IDX            40
#define USB_EXTPHY_VM_IDX             41
#define USB_EXTPHY_SPEED_IDX          41
#define USB_EXTPHY_RCV_IDX            42
#define USB_EXTPHY_VPO_IDX            42
#define USB_EXTPHY_VMO_IDX            43
#define USB_EXTPHY_SUSPND_IDX         44
#define EXT_ADC_START_IDX             45
#define LEDC_LS_SIG_OUT0_IDX          45
#define LEDC_LS_SIG_OUT1_IDX          46
#define LEDC_LS_SIG_OUT2_IDX          47
#define LEDC_LS_SIG_OUT3_IDX          48
#define LEDC_LS_SIG_OUT4_IDX          49
#define LEDC_LS_SIG_OUT5_IDX          50
#define RMT_SIG_IN0_IDX               51
#define RMT_SIG_OUT0_IDX              51
#define RMT_SIG_IN1_IDX               52
#define RMT_SIG_OUT1_IDX              52
#define I2CEXT0_SCL_IN_IDX            53
#define I2CEXT0_SCL_OUT_IDX           53
#define I2CEXT0_SDA_IN_IDX            54
#define I2CEXT0_SDA_OUT_IDX           54
#define GPIO_SD0_OUT_IDX              55
#define GPIO_SD1_OUT_IDX              56
#define GPIO_SD2_OUT_IDX              57
#define GPIO_SD3_OUT_IDX              58
#define FSPICLK_IN_IDX                63
#define FSPICLK_OUT_IDX               63
#define FSPIQ_IN_IDX                  64
#define FSPIQ_OUT_IDX                 64
#define FSPID_IN_IDX                  65
#define FSPID_OUT_IDX                 65
#define FSPIHD_IN_IDX                 66
#define FSPIHD_OUT_IDX                66
#define FSPIWP_IN_IDX                 67
#define FSPIWP_OUT_IDX                67
#define FSPICS0_IN_IDX                68
#define FSPICS0_OUT_IDX               68
#define FSPICS1_OUT_IDX               69
#define FSPICS2_OUT_IDX               70
#define FSPICS3_OUT_IDX               71
#define FSPICS4_OUT_IDX               72
#define FSPICS5_OUT_IDX               73
#define TWAI_RX_IDX                   74
#define TWAI_TX_IDX                   74
#define TWAI_BUS_OFF_ON_IDX           75
#define TWAI_CLKOUT_IDX               76
#define PCMFSYNC_IN_IDX               77
#define BT_AUDIO0_IRQ_IDX             77
#define PCMCLK_IN_IDX                 78
#define BT_AUDIO1_IRQ_IDX             78
#define PCMDIN_IDX                    79
#define BT_AUDIO2_IRQ_IDX             79
#define RW_WAKEUP_REQ_IDX             80
#define BLE_AUDIO0_IRQ_IDX            80
#define BLE_AUDIO1_IRQ_IDX            81
#define BLE_AUDIO2_IRQ_IDX            82
#define PCMFSYNC_OUT_IDX              83
#define PCMCLK_OUT_IDX                84
#define PCMDOUT_IDX                   85
#define BLE_AUDIO_SYNC0_P_IDX         86
#define BLE_AUDIO_SYNC1_P_IDX         87
#define BLE_AUDIO_SYNC2_P_IDX         88
#define ANT_SEL0_IDX                  89
#define ANT_SEL1_IDX                  90
#define ANT_SEL2_IDX                  91
#define ANT_SEL3_IDX                  92
#define ANT_SEL4_IDX                  93
#define ANT_SEL5_IDX                  94
#define ANT_SEL6_IDX                  95
#define ANT_SEL7_IDX                  96
#define SIG_IN_FUNC_97_IDX            97
#define SIG_IN_FUNC97_IDX             97
#define SIG_IN_FUNC_98_IDX            98
#define SIG_IN_FUNC98_IDX             98
#define SIG_IN_FUNC_99_IDX            99
#define SIG_IN_FUNC99_IDX             99
#define SIG_IN_FUNC_100_IDX           100
#define SIG_IN_FUNC100_IDX            100
#define SYNCERR_IDX                   101
#define SYNCFOUND_FLAG_IDX            102
#define EVT_CNTL_IMMEDIATE_ABORT_IDX  103
#define LINKLBL_IDX                   104
#define DATA_EN_IDX                   105
#define DATA_IDX                      106
#define PKT_TX_ON_IDX                 107
#define PKT_RX_ON_IDX                 108
#define RW_TX_ON_IDX                  109
#define RW_RX_ON_IDX                  110
#define EVT_REQ_P_IDX                 111
#define EVT_STOP_P_IDX                112
#define BT_MODE_ON_IDX                113
#define GPIO_LC_DIAG0_IDX             114
#define GPIO_LC_DIAG1_IDX             115
#define GPIO_LC_DIAG2_IDX             116
#define CH_IDX_IDX                    117
#define RX_WINDOW_IDX                 118
#define UPDATE_RX_IDX                 119
#define RX_STATUS_IDX                 120
#define CLK_GPIO_IDX                  121
#define NBT_BLE_IDX                   122
#define CLK_OUT_OUT1_IDX              123
#define CLK_OUT_OUT2_IDX              124
#define CLK_OUT_OUT3_IDX              125
#define SPICS1_OUT_IDX                126
#define SIG_GPIO_OUT_IDX              128
#define GPIO_MAP_DATE_IDX             0x2006130

#endif  /* __ARCH_RISCV_SRC_ESP32C3_HARDWARE_ESP32C3_GPIO_SIGMAP_H */
