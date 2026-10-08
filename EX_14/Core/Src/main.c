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
/* USER CODE BEGIN 0 */

void display7SEG(int num) {
    // -------------------------------------------------------------
    // Bước 1: Xóa hiển thị cũ bằng cách kéo tất cả các chân lên HIGH (TẮT)
    // -------------------------------------------------------------
    HAL_GPIO_WritePin(GPIOB, SEG0_Pin | SEG1_Pin | SEG2_Pin | SEG3_Pin
                           | SEG4_Pin | SEG5_Pin | SEG6_Pin, GPIO_PIN_SET);

    // -------------------------------------------------------------
    // Bước 2: Kéo chân các thanh LED cần hiển thị xuống LOW (SÁNG)
    // -------------------------------------------------------------
    switch (num) {
        case 0: // Số 0 -> Sáng: a, b, c, d, e, f (Tắt thanh g)
            HAL_GPIO_WritePin(GPIOB, SEG0_Pin | SEG1_Pin | SEG2_Pin | SEG3_Pin | SEG4_Pin | SEG5_Pin, GPIO_PIN_RESET);
            break;
        case 1: // Số 1 -> Sáng: b, c (Tắt a, d, e, f, g)
            HAL_GPIO_WritePin(GPIOB, SEG1_Pin | SEG2_Pin, GPIO_PIN_RESET);
            break;
        case 2: // Số 2 -> Sáng: a, b, d, e, g (Tắt c, f)
            HAL_GPIO_WritePin(GPIOB, SEG0_Pin | SEG1_Pin | SEG3_Pin | SEG4_Pin | SEG6_Pin, GPIO_PIN_RESET);
            break;
        case 3: // Số 3 -> Sáng: a, b, c, d, g (Tắt e, f)
            HAL_GPIO_WritePin(GPIOB, SEG0_Pin | SEG1_Pin | SEG2_Pin | SEG3_Pin | SEG6_Pin, GPIO_PIN_RESET);
            break;
        case 4: // Số 4 -> Sáng: b, c, f, g (Tắt a, d, e)
            HAL_GPIO_WritePin(GPIOB, SEG1_Pin | SEG2_Pin | SEG5_Pin | SEG6_Pin, GPIO_PIN_RESET);
            break;
        case 5: // Số 5 -> Sáng: a, c, d, f, g (Tắt b, e)
            HAL_GPIO_WritePin(GPIOB, SEG0_Pin | SEG2_Pin | SEG3_Pin | SEG5_Pin | SEG6_Pin, GPIO_PIN_RESET);
            break;
        case 6: // Số 6 -> Sáng: a, c, d, e, f, g (Tắt b)
            HAL_GPIO_WritePin(GPIOB, SEG0_Pin | SEG2_Pin | SEG3_Pin | SEG4_Pin | SEG5_Pin | SEG6_Pin, GPIO_PIN_RESET);
            break;
        case 7: // Số 7 -> Sáng: a, b, c (Tắt d, e, f, g)
            HAL_GPIO_WritePin(GPIOB, SEG0_Pin | SEG1_Pin | SEG2_Pin, GPIO_PIN_RESET);
            break;
        case 8: // Số 8 -> Sáng toàn bộ các thanh a, b, c, d, e, f, g
            HAL_GPIO_WritePin(GPIOB, SEG0_Pin | SEG1_Pin | SEG2_Pin | SEG3_Pin | SEG4_Pin | SEG5_Pin | SEG6_Pin, GPIO_PIN_RESET);
            break;
        case 9: // Số 9 -> Sáng: a, b, c, d, f, g (Tắt e)
            HAL_GPIO_WritePin(GPIOB, SEG0_Pin | SEG1_Pin | SEG2_Pin | SEG3_Pin | SEG5_Pin | SEG6_Pin, GPIO_PIN_RESET);
            break;
        default: // Trường hợp dữ liệu đầu vào ngoài phạm vi 0-9
            break;
    }
}
// =========================EX3==================================
const int MAX_LED = 4;                 // Số lượng LED 7 đoạn
int index_led = 0;                     // Vị trí LED đang được quét
int led_buffer[4] = {1, 2, 3, 4};      // Mảng chứa giá trị hiển thị: 1, 2, 3, 4

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
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
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
//=================INTRO========================================
//int counter = 100;
//void HAL_TIM_PeriodElapsedCallback ( TIM_HandleTypeDef * htim )
//{
//	counter--;
//	if (counter <= 0) {
//		counter = 100;
//		HAL_GPIO_TogglePin ( LED_RED_GPIO_Port , LED_RED_Pin );
//	}
//}
// ==============================================================


// =========================EX1==================================
//int counter_led = 50; // 50 * 10ms = 500ms (0.5 giây)
//int state_led = 0;    // Trạng thái quét 0 hoặc 1
//
//void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
//    if (htim->Instance == TIM2) {
//        counter_led--;
//
//        if (counter_led <= 0) {
//            counter_led = 50; // Reset lại bộ đếm 500ms
//
//            // Tắt cả 2 LED trước để tránh bị lem (PNP: SET = TẮT)
//            HAL_GPIO_WritePin(GPIOA, EN0_Pin | EN1_Pin, GPIO_PIN_SET);
//
//            switch (state_led) {
//                case 0:
//                    HAL_GPIO_WritePin(GPIOA, EN0_Pin, GPIO_PIN_RESET); // Bật LED 0
//                    display7SEG(1);                                    // Hiện số 1
//                    state_led = 1;
//                    break;
//
//                case 1:
//                    HAL_GPIO_WritePin(GPIOA, EN1_Pin, GPIO_PIN_RESET); // Bật LED 1
//                    display7SEG(2);                                    // Hiện số 2
//                    state_led = 0;
//                    break;
//
//                default:
//                    state_led = 0;
//                    break;
//            }
//        }
//    }
//}
// ==============================================================

// =========================EX2==================================
//int counter_led = 50;  // 50 * 10ms = 500ms (0.5s) đổi LED 7 đoạn 1 lần
//int counter_dot = 100; // 100 * 10ms = 1000ms (1s) chớp tắt LED DOT 1 lần
//int state_led = 0;     // Trạng thái quét 0, 1, 2, 3 tương ứng 4 LED
//
//void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
//    if (htim->Instance == TIM2) {
//
//        // -------------------------------------------------------------
//        // 1. Xử lý chớp tắt 2 LED DOT (PA4) mỗi 1 giây
//        // -------------------------------------------------------------
//        counter_dot--;
//        if (counter_dot <= 0) {
//            counter_dot = 100; // Reset đếm 1000ms
//            HAL_GPIO_TogglePin(GPIOA, DOT_Pin); // �?ảo trạng thái DOT (PA4)
//        }
//
//        // -------------------------------------------------------------
//        // 2. Xử lý quét 4 LED 7 đoạn mỗi 500ms (dùng switch-case)
//        // -------------------------------------------------------------
//        counter_led--;
//        if (counter_led <= 0) {
//            counter_led = 50; // Reset đếm 500ms
//
//            // Tắt tất cả 4 transistor đi�?u khiển trước (Anode PNP: SET = TẮT)
//            HAL_GPIO_WritePin(GPIOA, EN0_Pin | EN1_Pin | EN2_Pin | EN3_Pin, GPIO_PIN_SET);
//
//            switch (state_led) {
//                case 0: // Bật LED 0 -> Hiển thị số 1
//                    HAL_GPIO_WritePin(GPIOA, EN0_Pin, GPIO_PIN_RESET);
//                    display7SEG(1);
//                    state_led = 1;
//                    break;
//
//                case 1: // Bật LED 1 -> Hiển thị số 2
//                    HAL_GPIO_WritePin(GPIOA, EN1_Pin, GPIO_PIN_RESET);
//                    display7SEG(2);
//                    state_led = 2;
//                    break;
//
//                case 2: // Bật LED 2 -> Hiển thị số 3
//                    HAL_GPIO_WritePin(GPIOA, EN2_Pin, GPIO_PIN_RESET);
//                    display7SEG(3);
//                    state_led = 3;
//                    break;
//
//                case 3: // Bật LED 3 -> Hiển thị số 0
//                    HAL_GPIO_WritePin(GPIOA, EN3_Pin, GPIO_PIN_RESET);
//                    display7SEG(0);
//                    state_led = 0;
//                    break;
//
//                default:
//                    state_led = 0;
//                    break;
//            }
//        }
//    }
//}
// ==============================================================


// =========================EX3==================================
//int counter_led = 50;  // 50 * 10ms = 500ms (0.5s) quét 1 LED
//int counter_dot = 100; // 100 * 10ms = 1000ms (1s) chớp tắt DOT
//
//void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
//    if (htim->Instance == TIM2) {
//
//        // 1. Chớp tắt 2 LED DOT mỗi 1 giây
//        counter_dot--;
//        if (counter_dot <= 0) {
//            counter_dot = 100;
//            HAL_GPIO_TogglePin(GPIOA, DOT_Pin);
//        }
//
//        // 2. Quét LED 7 đoạn mỗi 500ms
//        counter_led--;
//        if (counter_led <= 0) {
//            counter_led = 50;
//
//            // Gọi hàm quét LED dựa trên biến index_led hiện tại
//            update7SEG(index_led);
//
//            // Tăng index_led để lần ngắt sau quét LED tiếp theo
//            index_led++;
//
//            // Nếu vượt quá MAX_LED thì quay vòng về 0
//            if (index_led >= MAX_LED) {
//                index_led = 0;
//            }
//        }
//    }
//}

// ==============================================================

// =========================EX4==================================
int counter_led = 25;  // 25 * 10ms = 250ms đổi LED 1 lần -> 4 LED mất 1000ms (tần số 1Hz)
int counter_dot = 100; // 100 * 10ms = 1000ms (1s) chớp tắt LED DOT 1 lần

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
    if (htim->Instance == TIM2) {

        // 1. Chớp tắt 2 LED DOT (PA4) mỗi 1 giây
        counter_dot--;
        if (counter_dot <= 0) {
            counter_dot = 100;
            HAL_GPIO_TogglePin(GPIOA, DOT_Pin);
        }

        // 2. Quét LED 7 đoạn (Chuyển LED mỗi 250ms)
        counter_led--;
        if (counter_led <= 0) {
            counter_led = 25;

            // Cập nhật giá trị lên LED hiện tại
            update7SEG(index_led);

            // Tăng vị trí LED cho lần ngắt tiếp theo
            index_led++;
            if (index_led >= MAX_LED) {
                index_led = 0;
            }
        }
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

