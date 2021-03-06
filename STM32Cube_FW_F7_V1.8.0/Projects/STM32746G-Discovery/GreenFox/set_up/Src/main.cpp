 /**
  ******************************************************************************
  * @file    Templates/Src/main.c 
  * @author  MCD Application Team
  * @version V1.0.3
  * @date    22-April-2016 
  * @brief   STM32F7xx HAL API Template project 
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2016 STMicroelectronics</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/** @addtogroup STM32F7xx_HAL_Examples
  * @{
  */

/** @addtogroup Templates
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static void SystemClock_Config(void);
static void Error_Handler(void);
static void MPU_Config(void);
static void CPU_CACHE_Enable(void);

/* Private functions ---------------------------------------------------------*/

/*
 * Function creates and initializes a pin at given port*
 * Return a GPIO_Init struct pointer
 * And initializes that to given parameters
 */
GPIO_InitTypeDef* create_and_init_pin(uint16_t pin_num, uint32_t mode, uint32_t pull_mode, uint32_t speed, GPIO_TypeDef *port)
{
	GPIO_InitTypeDef *pin = new GPIO_InitTypeDef;  // create a config structure
	pin->Pin = pin_num;                            // sets pin
	pin->Mode = mode;                              // Configure mode
	pin->Pull = pull_mode;                         // pull mode
	pin->Speed = speed;                            // conf speed

	HAL_GPIO_Init(port, pin);                      // initialize the pin on GPIOx port with HAL

	return pin;
}

typedef struct {

	GPIO_InitTypeDef *pin;
	GPIO_TypeDef *port;

} pin_at_portx_t;

/*
 * Flahes the members of the param array, with param size, and for param ms long each
 */
void blink_led_array_at_rate(pin_at_portx_t pin_port_t_arr[], int size, int ms)
{
  for (int i = 0; i < size;  ++i) {
	  pin_port_t_arr[i].port->ODR = pin_port_t_arr[i].port->ODR | pin_port_t_arr[i].pin->Pin;
	  HAL_Delay(ms);
	  pin_port_t_arr[i].port->ODR = pin_port_t_arr[i].port->ODR & ~pin_port_t_arr[i].pin->Pin;
  }
}

/*
 * flashes different adjacent pins connecting the same param port
 */
void bit_shift_blinker(GPIO_TypeDef *port, int range, uint16_t start_pin)
{
  for (int i = 0; i < range; ++i) {
	  port->ODR = port->ODR | (start_pin >> i);
	  HAL_Delay(300);
	  port->ODR = port->ODR & ~(start_pin >> i);
  }
}

/*
 * This function flashes led from given port/pin at given rate
 */

void flash_led_at_pin_in_given_ms(GPIO_TypeDef *port, uint16_t pin_num, int ms)
{
	HAL_GPIO_WritePin(port, pin_num, GPIO_PIN_SET);   // setting the pin to 1
	HAL_Delay(ms);                                    // wait a second
	HAL_GPIO_WritePin(port, pin_num, GPIO_PIN_RESET); // setting the pin to 0
}

/**
  * @brief  Main program
  * @param  None
  * @retval None
  */
int main(void)
{
  /* This project template calls firstly two functions in order to configure MPU feature 
     and to enable the CPU Cache, respectively MPU_Config() and CPU_CACHE_Enable().
     These functions are provided as template implementation that User may integrate 
     in his application, to enhance the performance in case of use of AXI interface 
     with several masters. */ 
  
  /* Configure the MPU attributes as Write Through */
  MPU_Config();

  /* Enable the CPU Cache */
  CPU_CACHE_Enable();

  /* STM32F7xx HAL library initialization:
       - Configure the Flash ART accelerator on ITCM interface
       - Configure the Systick to generate an interrupt each 1 msec
       - Set NVIC Group Priority to 4
       - Low Level Initialization
     */
  HAL_Init();

  /* Configure the System clock to have a frequency of 216 MHz */
  SystemClock_Config();

  __HAL_RCC_GPIOA_CLK_ENABLE();       // we need to enable the GPIOA port's clock first

  GPIO_InitTypeDef pin_A_0;           // create a config structure
  pin_A_0.Pin = GPIO_PIN_0;           // this is about PIN 0
  pin_A_0.Mode = GPIO_MODE_OUTPUT_PP; // Configure as output with push-up-down enabled
  pin_A_0.Pull = GPIO_PULLDOWN;       // the push-up-down should work as pulldown
  pin_A_0.Speed = GPIO_SPEED_HIGH;    // we need a high-speed output

  HAL_GPIO_Init(GPIOA, &pin_A_0);     // initialize the pin on GPIOA port with HAL

  __HAL_RCC_GPIOF_CLK_ENABLE();       // we need to enable the GPIOA port's clock first
  __HAL_RCC_GPIOC_CLK_ENABLE();

  GPIO_InitTypeDef pin_D_0;           // connected to an external button
  pin_D_0.Pin = GPIO_PIN_7;           // this is about PIN 7
  pin_D_0.Mode = GPIO_MODE_INPUT;     // Configure as input
  pin_D_0.Pull = GPIO_PULLUP;         // the push-up-down should work as pullup
  pin_D_0.Speed = GPIO_SPEED_HIGH;    // we need a high-speed input


  HAL_GPIO_Init(GPIOC, &pin_D_0);

  // init from pin_A_1 to pint_A_3
  GPIO_InitTypeDef *pin_A_1 = create_and_init_pin(GPIO_PIN_10, GPIO_MODE_OUTPUT_PP, GPIO_PULLDOWN, GPIO_SPEED_HIGH, GPIOF);
  GPIO_InitTypeDef *pin_A_2 = create_and_init_pin(GPIO_PIN_9, GPIO_MODE_OUTPUT_PP, GPIO_PULLDOWN, GPIO_SPEED_HIGH, GPIOF);
  GPIO_InitTypeDef *pin_A_3 = create_and_init_pin(GPIO_PIN_8, GPIO_MODE_OUTPUT_PP, GPIO_PULLDOWN, GPIO_SPEED_HIGH, GPIOF);
  // init pin_A_4 to be alle to operate led through a push button
  GPIO_InitTypeDef *pin_A_4 = create_and_init_pin(GPIO_PIN_7, GPIO_MODE_OUTPUT_PP, GPIO_PULLDOWN, GPIO_SPEED_HIGH, GPIOF);

  /* Add your application code here     */
  BSP_LED_Init(LED_GREEN);
  BSP_LED_On(LED_GREEN);
  BSP_PB_Init(BUTTON_KEY, BUTTON_MODE_GPIO);

  // creating pin_at_portx_t structs
  pin_at_portx_t a0_t;
  a0_t.pin = &pin_A_0;
  a0_t.port = GPIOA;
  pin_at_portx_t a1_t;
  a1_t.pin = pin_A_1;
  a1_t.port = GPIOF;
  pin_at_portx_t a2_t;
  a2_t.pin = pin_A_2;
  a2_t.port = GPIOF;
  pin_at_portx_t a3_t;
  a3_t.pin = pin_A_3;
  a3_t.port = GPIOF;

  pin_at_portx_t pin_at_portx_arr[4] = {a0_t, a1_t, a2_t, a3_t};

  int state = 0;

  while (1)
  {
	if (HAL_GPIO_ReadPin(GPIOC, pin_D_0.Pin) == 0) {
		 blink_led_array_at_rate(pin_at_portx_arr, 4, 50);
	}

    if (BSP_PB_GetState(BUTTON_KEY))
	    state++;

    if (state == 0) {
	    flash_led_at_pin_in_given_ms(GPIOF, GPIO_PIN_10, 300);
    } else if (state == 1) {
	    blink_led_array_at_rate(pin_at_portx_arr, 4, 300);
    } else if (state == 2) {
	    blink_led_array_at_rate(pin_at_portx_arr, 4, 200);
    } else if (state == 3) {
	    blink_led_array_at_rate(pin_at_portx_arr, 4, 100);
    } else if (state == 4) {
	   state = 0;
	   HAL_Delay(200);
    }

//	  if (BSP_PB_GetState(BUTTON_KEY))
//		  blink_led_array_at_rate(pin_at_portx_arr, 4, 400);

    GPIOF->ODR = GPIOF->ODR | GPIO_PIN_7;

//	  	bit_shift_blinker(GPIOF, 3, GPIO_PIN_10);

//	  	if (BSP_PB_GetState(BUTTON_KEY)) {
//	  		flash_led_at_pin_in_given_ms(GPIOA, GPIO_PIN_0, 1000);
//	  		flash_led_at_pin_in_given_ms(GPIOF, GPIO_PIN_8, 1000);
//
//	  	}
//
//	  	flash_led_at_pin_in_given_ms(GPIOA, GPIO_PIN_0, 600);
//	  	flash_led_at_pin_in_given_ms(GPIOF, GPIO_PIN_10, 500);
//	  	flash_led_at_pin_in_given_ms(GPIOF, GPIO_PIN_9, 200);
//	  	flash_led_at_pin_in_given_ms(GPIOF, GPIO_PIN_8, 500);
//
//	  	GPIOF->ODR = GPIOF->ODR | 0X0400U;
//	  	HAL_Delay(400);
//	  	GPIOF->ODR = GPIOF->ODR & ~0X0400U;
//
//	  	GPIOF->ODR = GPIOF->ODR | 0b1000000000U;
//	  	HAL_Delay(500);
//	  	GPIOF->ODR = GPIOF->ODR & ~0b1000000000U;
//
//	  	GPIOF->ODR = GPIOF->ODR | (1 << 8);
//	  	HAL_Delay(300);
//	  	GPIOF->ODR = GPIOF->ODR & ~(1 << 8);

  }
}

/**
  * @brief  System Clock Configuration
  *         The system Clock is configured as follow : 
  *            System Clock source            = PLL (HSE)
  *            SYSCLK(Hz)                     = 216000000
  *            HCLK(Hz)                       = 216000000
  *            AHB Prescaler                  = 1
  *            APB1 Prescaler                 = 4
  *            APB2 Prescaler                 = 2
  *            HSE Frequency(Hz)              = 25000000
  *            PLL_M                          = 25
  *            PLL_N                          = 432
  *            PLL_P                          = 2
  *            PLL_Q                          = 9
  *            VDD(V)                         = 3.3
  *            Main regulator output voltage  = Scale1 mode
  *            Flash Latency(WS)              = 7
  * @param  None
  * @retval None
  */
static void SystemClock_Config(void)
{
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_OscInitTypeDef RCC_OscInitStruct;

  /* Enable HSE Oscillator and activate PLL with HSE as source */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSIState = RCC_HSI_OFF;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 25;
  RCC_OscInitStruct.PLL.PLLN = 432;  
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 9;
  if(HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /* activate the OverDrive to reach the 216 Mhz Frequency */
  if(HAL_PWREx_EnableOverDrive() != HAL_OK)
  {
    Error_Handler();
  }
  
  /* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2 
     clocks dividers */
  RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;  
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;  
  if(HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_7) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
static void Error_Handler(void)
{
  /* User may add here some code to deal with this error */
  while(1)
  {
  }
}

/**
  * @brief  Configure the MPU attributes as Write Through for SRAM1/2.
  * @note   The Base Address is 0x20010000 since this memory interface is the AXI.
  *         The Region Size is 256KB, it is related to SRAM1 and SRAM2  memory size.
  * @param  None
  * @retval None
  */
static void MPU_Config(void)
{
  MPU_Region_InitTypeDef MPU_InitStruct;
  
  /* Disable the MPU */
  HAL_MPU_Disable();

  /* Configure the MPU attributes as WT for SRAM */
  MPU_InitStruct.Enable = MPU_REGION_ENABLE;
  MPU_InitStruct.BaseAddress = 0x20010000;
  MPU_InitStruct.Size = MPU_REGION_SIZE_256KB;
  MPU_InitStruct.AccessPermission = MPU_REGION_FULL_ACCESS;
  MPU_InitStruct.IsBufferable = MPU_ACCESS_NOT_BUFFERABLE;
  MPU_InitStruct.IsCacheable = MPU_ACCESS_CACHEABLE;
  MPU_InitStruct.IsShareable = MPU_ACCESS_SHAREABLE;
  MPU_InitStruct.Number = MPU_REGION_NUMBER0;
  MPU_InitStruct.TypeExtField = MPU_TEX_LEVEL0;
  MPU_InitStruct.SubRegionDisable = 0x00;
  MPU_InitStruct.DisableExec = MPU_INSTRUCTION_ACCESS_ENABLE;

  HAL_MPU_ConfigRegion(&MPU_InitStruct);

  /* Enable the MPU */
  HAL_MPU_Enable(MPU_PRIVILEGED_DEFAULT);
}

/**
  * @brief  CPU L1-Cache enable.
  * @param  None
  * @retval None
  */
static void CPU_CACHE_Enable(void)
{
  /* Enable I-Cache */
  SCB_EnableICache();

  /* Enable D-Cache */
  SCB_EnableDCache();
}

#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/**
  * @}
  */ 

/**
  * @}
  */ 

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
