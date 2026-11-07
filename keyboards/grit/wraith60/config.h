// Copyright 2026 unimplanted
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

/* WS2812 underglow on B7 = TIM4_CH2, DMA1 channel 7 (TIM4_UP) */
#define WS2812_PWM_DRIVER PWMD4
#define WS2812_PWM_CHANNEL 2
#define WS2812_DMA_STREAM STM32_DMA1_STREAM7
#define WS2812_DMA_CHANNEL 7
