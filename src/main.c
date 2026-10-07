/*
 * main.c - лише каркас: ініціалізація ядра й тактування та виклик
 * прикладного шару. Логіки блимання тут немає - вона в app.c.
 */
#include "stm32f1xx_hal.h"
#include "app.h"

static void SystemClock_Config(void);
static void Error_Handler(void);

int main(void)
{
    HAL_Init();           // SysTick на 1 мс, базова ініціалізація HAL
    SystemClock_Config(); // HSE 8 МГц -> PLL x9 -> SYSCLK 72 МГц

    setup(); // один раз

    while (1)
    {
        loop(); // нескінченно, як в Arduino Framework
    }
}

// HSE 8 МГц (кварц на платі) -> PLL x9 -> 72 МГц; APB1 = 36 МГц, APB2 = 72 МГц
static void SystemClock_Config(void)
{
    RCC_OscInitTypeDef osc = {0};
    RCC_ClkInitTypeDef clk = {0};

    osc.OscillatorType = RCC_OSCILLATORTYPE_HSE;
    osc.HSEState = RCC_HSE_ON;
    osc.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
    osc.PLL.PLLState = RCC_PLL_ON;
    osc.PLL.PLLSource = RCC_PLLSOURCE_HSE;
    osc.PLL.PLLMUL = RCC_PLL_MUL9;
    if (HAL_RCC_OscConfig(&osc) != HAL_OK)
    {
        Error_Handler();
    }

    clk.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK |
                    RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
    clk.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    clk.AHBCLKDivider = RCC_SYSCLK_DIV1;
    clk.APB1CLKDivider = RCC_HCLK_DIV2; // APB1 максимум 36 МГц
    clk.APB2CLKDivider = RCC_HCLK_DIV1;
    if (HAL_RCC_ClockConfig(&clk, FLASH_LATENCY_2) != HAL_OK)
    {
        Error_Handler();
    }
}

// Без цього обробника HAL_GetTick() не зростає і HAL_Delay() зависає назавжди
void SysTick_Handler(void)
{
    HAL_IncTick();
}

static void Error_Handler(void)
{
    __disable_irq();
    while (1)
    {
    }
}
