/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  */
/* USER CODE END Header */

#include "main.h"

/* Private variables ---------------------------------------------------------*/
COM_InitTypeDef BspCOMInit;

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);

/* USER CODE BEGIN 0 */
GPIO_PinState Button1State = 0;

void CenterGlass(void);
void Result(void);
/* USER CODE END 0 */

int main(void)
{
  HAL_Init();
  SystemClock_Config();
  MX_GPIO_Init();

  BSP_LED_Init(LED_GREEN);
  BSP_PB_Init(BUTTON_USER, BUTTON_MODE_EXTI);

  BspCOMInit.BaudRate   = 115200;
  BspCOMInit.WordLength = COM_WORDLENGTH_8B;
  BspCOMInit.StopBits   = COM_STOPBITS_1;
  BspCOMInit.Parity     = COM_PARITY_NONE;
  BspCOMInit.HwFlowCtl  = COM_HWCONTROL_NONE;
  if (BSP_COM_Init(COM1, &BspCOMInit) != BSP_ERROR_NONE)
  {
    Error_Handler();
  }

  /* USER CODE BEGIN WHILE */
  while (1)
  {
      if(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_4)==0 && HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_5)==1)
      {
          // Drive motor left
          HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, GPIO_PIN_SET);
          HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_RESET);
          HAL_GPIO_WritePin(GPIOF, GPIO_PIN_0, GPIO_PIN_SET);
          HAL_GPIO_WritePin(GPIOF, GPIO_PIN_1, GPIO_PIN_SET);
      }

      if(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_5)==0 && HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_4)==1)
      {
          // Drive motor right
          HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, GPIO_PIN_RESET);
          HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_SET);
          HAL_GPIO_WritePin(GPIOF, GPIO_PIN_0, GPIO_PIN_SET);
          HAL_GPIO_WritePin(GPIOF, GPIO_PIN_1, GPIO_PIN_SET);
      }

      if(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_6)==0 && HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_7)==1)
      {
          // Drive motor up
          HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, GPIO_PIN_SET);
          HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_RESET);
          HAL_GPIO_WritePin(GPIOF, GPIO_PIN_0, GPIO_PIN_SET);
          HAL_GPIO_WritePin(GPIOF, GPIO_PIN_1, GPIO_PIN_RESET);
      }

      if(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_7)==0 && HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_6)==1)
      {
          // Drive motor down
          HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, GPIO_PIN_RESET);
          HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_SET);
          HAL_GPIO_WritePin(GPIOF, GPIO_PIN_0, GPIO_PIN_SET);
          HAL_GPIO_WritePin(GPIOF, GPIO_PIN_1, GPIO_PIN_RESET);
      }

      CenterGlass();
      Result();
  }
  /* USER CODE END WHILE */
}

/* USER CODE BEGIN 4 */

void CenterGlass(void)
{
    // logic for centering glass
}

void Result(void)
{
    // logic for final result
}

/* USER CODE END 4 */

void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1_BOOST);

  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = RCC_PLLM_DIV4;
  RCC_OscInitStruct.PLL.PLLN = 85;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;

  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
  {
    Error_Handler();
  }
}

static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1;
  HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
}

void Error_Handler(void)
{
  __disable_irq();
  while (1)
  {
  }
}
