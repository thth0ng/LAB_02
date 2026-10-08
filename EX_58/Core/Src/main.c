/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
TIM_HandleTypeDef htim2;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_TIM2_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void display7SEG(int num) {
    // 1. Tắt toàn bộ 7 đoạn trước (Anode chung: SET = TẮT)
    HAL_GPIO_WritePin(GPIOB, SEG0_Pin|SEG1_Pin|SEG2_Pin|SEG3_Pin
                           |SEG4_Pin|SEG5_Pin|SEG6_Pin, GPIO_PIN_SET);

    // 2. Bật đúng các đoạn cần hiển thị (RESET = S�?NG)
    switch (num) {
        case 0: // a, b, c, d, e, f
            HAL_GPIO_WritePin(GPIOB, SEG0_Pin|SEG1_Pin|SEG2_Pin|SEG3_Pin|SEG4_Pin|SEG5_Pin, GPIO_PIN_RESET);
            break;
        case 1: // b, c
            HAL_GPIO_WritePin(GPIOB, SEG1_Pin|SEG2_Pin, GPIO_PIN_RESET);
            break;
        case 2: // a, b, d, e, g
            HAL_GPIO_WritePin(GPIOB, SEG0_Pin|SEG1_Pin|SEG3_Pin|SEG4_Pin|SEG6_Pin, GPIO_PIN_RESET);
            break;
        case 3: // a, b, c, d, g
            HAL_GPIO_WritePin(GPIOB, SEG0_Pin|SEG1_Pin|SEG2_Pin|SEG3_Pin|SEG6_Pin, GPIO_PIN_RESET);
            break;
        case 4: // b, c, f, g
            HAL_GPIO_WritePin(GPIOB, SEG1_Pin|SEG2_Pin|SEG5_Pin|SEG6_Pin, GPIO_PIN_RESET);
            break;
        case 5: // a, c, d, f, g
            HAL_GPIO_WritePin(GPIOB, SEG0_Pin|SEG2_Pin|SEG3_Pin|SEG5_Pin|SEG6_Pin, GPIO_PIN_RESET);
            break;
        case 6: // a, c, d, e, f, g
            HAL_GPIO_WritePin(GPIOB, SEG0_Pin|SEG2_Pin|SEG3_Pin|SEG4_Pin|SEG5_Pin|SEG6_Pin, GPIO_PIN_RESET);
            break;
        case 7: // a, b, c
            HAL_GPIO_WritePin(GPIOB, SEG0_Pin|SEG1_Pin|SEG2_Pin, GPIO_PIN_RESET);
            break;
        case 8: // a, b, c, d, e, f, g
            HAL_GPIO_WritePin(GPIOB, SEG0_Pin|SEG1_Pin|SEG2_Pin|SEG3_Pin|SEG4_Pin|SEG5_Pin|SEG6_Pin, GPIO_PIN_RESET);
            break;
        case 9: // a, b, c, d, f, g
            HAL_GPIO_WritePin(GPIOB, SEG0_Pin|SEG1_Pin|SEG2_Pin|SEG3_Pin|SEG5_Pin|SEG6_Pin, GPIO_PIN_RESET);
            break;
        default:
            break;
    }
}

// =========================EX5==================================
// Khai báo biến cho Bài 5 (Đồng hồ)
const int MAX_LED = 4;                 // Số lượng LED 7 đoạn
int index_led = 0;                     // Vị trí LED đang được quét
int led_buffer[4] = {1, 5, 0, 8};      // Khởi tạo ban đầu hiển thị 15:08

int hour = 15;                         // Giờ ban đầu
int minute = 8;                        // Phút ban đầu
int second = 50;                       // Giây ban đầu (đặt 50s để test nhanh sang 15:09)

// Hàm cập nhật mảng led_buffer theo hour và minute
void updateClockBuffer() {
    led_buffer[0] = hour / 10;   // Hàng chục của Giờ
    led_buffer[1] = hour % 10;   // Hàng đơn vị của Giờ
    led_buffer[2] = minute / 10; // Hàng chục của Phút
    led_buffer[3] = minute % 10; // Hàng đơn vị của Phút
}

// ==============================================================
void update7SEG(int index) {
    // Tắt tất cả 4 transistor điều khiển trước để chống lem (PNP: SET = TẮT)
    HAL_GPIO_WritePin(GPIOA, EN0_Pin | EN1_Pin | EN2_Pin | EN3_Pin, GPIO_PIN_SET);

    switch (index) {
        case 0:
            // Bật LED thứ 1 và hiển thị dữ liệu ở phần tử 0
            HAL_GPIO_WritePin(GPIOA, EN0_Pin, GPIO_PIN_RESET);
            display7SEG(led_buffer[0]);
            break;
        case 1:
            // Bật LED thứ 2 và hiển thị dữ liệu ở phần tử 1
            HAL_GPIO_WritePin(GPIOA, EN1_Pin, GPIO_PIN_RESET);
            display7SEG(led_buffer[1]);
            break;
        case 2:
            // Bật LED thứ 3 và hiển thị dữ liệu ở phần tử 2
            HAL_GPIO_WritePin(GPIOA, EN2_Pin, GPIO_PIN_RESET);
            display7SEG(led_buffer[2]);
            break;
        case 3:
            // Bật LED thứ 4 và hiển thị dữ liệu ở phần tử 3
            HAL_GPIO_WritePin(GPIOA, EN3_Pin, GPIO_PIN_RESET);
            display7SEG(led_buffer[3]);
            break;
        default:
            break;
    }
}
// =========================EX6==================================
//int timer0_counter = 0;
//int timer0_flag = 0;
//int TIMER_CYCLE = 10;
//
//void setTimer0(int duration){
//    timer0_counter = duration / TIMER_CYCLE;
//    timer0_flag = 0;
//}
//
//void timer_run(){
//    if(timer0_counter > 0){
//        timer0_counter--;
//        if(timer0_counter == 0) timer0_flag = 1;
//    }
//}
// ==============================================================

//// =========================EX7==================================
//int timer0_counter = 0;
//int timer0_flag = 0;
//
//int timer1_counter = 0;
//int timer1_flag = 0;
//
//int TIMER_CYCLE = 10; // Chu kỳ ngắt 10ms
//
//void setTimer0(int duration) {
//    timer0_counter = duration / TIMER_CYCLE;
//    timer0_flag = 0;
//}
//
//void setTimer1(int duration) {
//    timer1_counter = duration / TIMER_CYCLE;
//    timer1_flag = 0;
//}
//
//void timer_run() {
//    // Đếm ngược cho Timer 0 (Đồng hồ)
//    if (timer0_counter > 0) {
//        timer0_counter--;
//        if (timer0_counter == 0) timer0_flag = 1;
//    }
//    // Đếm ngược cho Timer 1 (LED DOT)
//    if (timer1_counter > 0) {
//        timer1_counter--;
//        if (timer1_counter == 0) timer1_flag = 1;
//    }
//}
//// ==============================================================

// =========================EX8==================================
int timer0_counter = 0;
int timer0_flag = 0;

int timer1_counter = 0;
int timer1_flag = 0;

int timer2_counter = 0; // THÊM: Timer cho quét LED
int timer2_flag = 0;

int TIMER_CYCLE = 10; // Chu kỳ ngắt 10ms

void setTimer0(int duration) {
    timer0_counter = duration / TIMER_CYCLE;
    timer0_flag = 0;
}

void setTimer1(int duration) {
    timer1_counter = duration / TIMER_CYCLE;
    timer1_flag = 0;
}

// THÊM: Hàm setTimer2
void setTimer2(int duration) {
    timer2_counter = duration / TIMER_CYCLE;
    timer2_flag = 0;
}

void timer_run() {
    // Timer 0: Đồng hồ (1000ms)
    if (timer0_counter > 0) {
        timer0_counter--;
        if (timer0_counter == 0) timer0_flag = 1;
    }
    // Timer 1: LED DOT (1000ms)
    if (timer1_counter > 0) {
        timer1_counter--;
        if (timer1_counter == 0) timer1_flag = 1;
    }
    // THÊM: Timer 2 quét LED 7 đoạn (250ms)
    if (timer2_counter > 0) {
        timer2_counter--;
        if (timer2_counter == 0) timer2_flag = 1;
    }
}
// ==============================================================
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_TIM2_Init();
  /* USER CODE BEGIN 2 */
  HAL_TIM_Base_Start_IT(&htim2);
  // =========================EX6==================================
  setTimer0(1000);
  // ==============================================================

  // =========================EX7==================================
  setTimer1(1000);
  // ==============================================================

  // =========================EX8==================================
  setTimer2(250);
  // ==============================================================
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

// =========================EX5==================================
//	      // Cập nhật đếm đồng hồ
//	      second++;
//	      if ( second >= 60) {
//	    	  second = 0;
//	    	  minute ++;
//	      }
//	      if( minute >= 60) {
//	    	   minute = 0;
//	    	   hour ++;
//	      }
//	      if( hour >=24){
//	    	  hour = 0;
//	      }
//	      updateClockBuffer ();
//	      HAL_Delay (1000) ;
// ==============================================================
// =========================EX6==================================
	  if (timer0_flag == 1) {
	            setTimer0(1000); // Đặt lại timer đếm 1s cho lần kế tiếp

	            // Giữ nguyên logic tăng giờ/phút/giây của Bài 5
	            second++;
	            if (second >= 60) {
	                second = 0;
	                minute++;
	            }
	            if (minute >= 60) {
	                minute = 0;
	                hour++;
	            }
	            if (hour >= 24) {
	                hour = 0;
	            }
	            updateClockBuffer();
	        }
	        // BỎ DÒNG: HAL_Delay(1000);
	  // =========================EX7==================================
	  if (timer1_flag == 1) {
	  	            setTimer1(1000);
	  	            HAL_GPIO_TogglePin(GPIOA, DOT_Pin); // Nháy LED DOT trong main
	  	  }
	  // ==============================================================

	  // =========================EX8==================================
	        if (timer2_flag == 1) {
	            setTimer2(250); // Cài lại timer quét LED chu kỳ 250ms

	            // Cập nhật hiển thị cho LED hiện tại
	            update7SEG(index_led);

	            // Chuyển sang LED tiếp theo cho lần quét sau
	            index_led++;
	            if (index_led >= MAX_LED) {
	                index_led = 0;
	            }
	        }
	  // ==============================================================
  }
// ==============================================================
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief TIM2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM2_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 7999;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 9;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, DOT_Pin|LED_RED_Pin|EN0_Pin|EN1_Pin
                          |EN2_Pin|EN3_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, SEG0_Pin|SEG1_Pin|SEG2_Pin|SEG3_Pin
                          |SEG4_Pin|SEG5_Pin|SEG6_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : DOT_Pin LED_RED_Pin EN0_Pin EN1_Pin
                           EN2_Pin EN3_Pin */
  GPIO_InitStruct.Pin = DOT_Pin|LED_RED_Pin|EN0_Pin|EN1_Pin
                          |EN2_Pin|EN3_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : SEG0_Pin SEG1_Pin SEG2_Pin SEG3_Pin
                           SEG4_Pin SEG5_Pin SEG6_Pin */
  GPIO_InitStruct.Pin = SEG0_Pin|SEG1_Pin|SEG2_Pin|SEG3_Pin
                          |SEG4_Pin|SEG5_Pin|SEG6_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */
// =========================EX5==================================
int counter_led = 25;  // 25 * 10ms = 250ms đổi LED 1 lần -> 4 LED mất 1000ms (tần số 1Hz)

// =========================EX56==================================
//int counter_dot = 100; // 100 * 10ms = 1000ms (1s) chớp tắt LED DOT 1 lần
// ==============================================================

// 567
//void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
//    if (htim->Instance == TIM2) {
//
//    	timer_run(); // =============EX6=============

// =========================EX56==================================
//        // 1. Chớp tắt 2 LED DOT (PA4) mỗi 1 giây
//        counter_dot--;
//        if (counter_dot <= 0) {
//            counter_dot = 100;
//            HAL_GPIO_TogglePin(GPIOA, DOT_Pin);
//        }
// =============================567=================================
//        // 2. Quét LED 7 đoạn (Chuyển LED mỗi 250ms)
//        counter_led--;
//        if (counter_led <= 0) {
//            counter_led = 25;
//
//            // Cập nhật giá trị lên LED hiện tại
//            update7SEG(index_led);
//
//            // Tăng vị trí LED cho lần ngắt tiếp theo
//            index_led++;
//            if (index_led >= MAX_LED) {
//                index_led = 0;
//            }
//        }
//    }
//}
// ==============================================================

// =========================EX8==================================

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
    if (htim->Instance == TIM2) {
    	timer_run(); // Ngắt chỉ làm nhiệm vụ duy nhất là đếm thời gian
    }
}
// ==============================================================

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

