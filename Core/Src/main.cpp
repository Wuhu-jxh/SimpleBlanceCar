/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
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
#include <cstring>
#include "main.h"
#include "i2c.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "pidControl.h"
#include "settings.h"
#include "encoder.h"
#include "relocated.h"
#include "SerialIO.h"
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

/* USER CODE BEGIN PV */
/**********编码器**********/
int32_t encoderLeft = 0;
int32_t encoderRight = 0;
/**********电机**********/
int32_t motorLeft = 0;
int32_t motorRight = 0;
/**********PID**********/
float pidSpeed = 0;
float pidBlance = 0;
float pidTurn = 0;
PID pidBlanceStruct, pidSpeedStruct,pidTurnStruct;
/**********速度**********/
float speed = 0;
/**********角度**********/
float angle = 0;
/**********滤波**********/
kalman_filter kalmanFilterStruct;
low_pass_filter lowPassFilterStruct;
/*********串口IO********/
float x = 0;
float y = 0;
float z = 0;
/********陀螺仪*********/
char rxBuffer;
char RxBuffer[RXBUFFERSIZE];
int Uart1_Rx_Cnt = 0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_NVIC_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
    pid_Init(&pidBlanceStruct, POSITION_PID_KP,0,POSITION_PID_KD);
    pid_Init(&pidSpeedStruct, SPEED_PID_KP, SPEED_PID_KI, 0);
    pid_Init(&pidTurnStruct, ANGLE_PID_KP, 0, 0);
    kalmanFilter_Init(&kalmanFilterStruct, KALMAN_P, KALMAN_Q, KALMAN_R,KALMAN_K,0,0);
    lowPassInit(&lowPassFilterStruct, LOW_PASS_FILTER_A);


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
  MX_I2C1_Init();
  MX_TIM2_Init();
  MX_TIM3_Init();
  MX_I2C2_Init();
  MX_TIM1_Init();
  MX_USART1_UART_Init();

  /* Initialize interrupts */
  MX_NVIC_Init();
  /* USER CODE BEGIN 2 */
    /*******串口重定向*********/
    RetargetInit(&huart1);
    sysLog(LOG_DEBUG,"串口重定向完成");

  /********HAL库相关的初始化********/
    HAL_TIM_Encoder_Start(&htim2, TIM_CHANNEL_1);
    HAL_TIM_Encoder_Start(&htim3, TIM_CHANNEL_1);
    HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
    HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2);
    HAL_UART_Receive_IT(&huart1, (uint8_t *) &rxBuffer, 1);
    HAL_I2C_Init(&hi2c1);
    sysLog(LOG_DEBUG,"HAL库相关的初始化完成");

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
    pidSpeed = pid_calc(&pidSpeedStruct, speed, encoderSpeedCal());

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
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }

  /** Enables the Clock Security System
  */
  HAL_RCC_EnableCSS();
}

/**
  * @brief NVIC Configuration.
  * @retval None
  */
static void MX_NVIC_Init(void)
{
  /* TIM3_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(TIM3_IRQn, 1, 0);
  HAL_NVIC_EnableIRQ(TIM3_IRQn);
}

/* USER CODE BEGIN 4 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{

}
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{

}
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if (Uart1_Rx_Cnt >= RXBUFFERSIZE)  //溢出判断
    {
        UNUSED(huart);
        Uart1_Rx_Cnt = 0;
        memset(RxBuffer, 0x00, sizeof(RxBuffer));
        HAL_UART_Transmit(&huart1, (uint8_t *) "数据溢出", 12, 0xFFFF);
    }
    else
    {
        RxBuffer[Uart1_Rx_Cnt++] = rxBuffer;   //接收数据转存
        if (RxBuffer[Uart1_Rx_Cnt - 1] == '#') //判断结束位
        {
            processCommand(RxBuffer,Uart1_Rx_Cnt);
            memset(RxBuffer,0x00,sizeof(RxBuffer));
            Uart1_Rx_Cnt = 0;
        }
    }
    HAL_UART_Receive_IT(&huart1, (uint8_t *) &rxBuffer, 1);   //再开启接收中断
}
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
    sysLogf(LOG_FATAL,"系统已进入ErrorHandler,即将重置....");
    __set_FAULTMASK(1);
    HAL_NVIC_SystemReset();
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
    sysLogf(LOG_FATAL,"系统断言触发！出现严重异常。错误存在于%s,第%d行\r\n",file,line);
    HAL_NVIC_SystemReset();
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
