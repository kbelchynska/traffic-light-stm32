#include "app.h"
#include "stm32f1xx_hal.h"

#define LED_PORT GPIOC
#define LED_PIN GPIO_PIN_13
#define BLINK_HALF_PERIOD_MS 500

void setup(void)
{
    __HAL_RCC_GPIOC_CLK_ENABLE();

    GPIO_InitTypeDef led = {0};
    led.Pin = LED_PIN;
    led.Mode = GPIO_MODE_OUTPUT_PP;
    led.Pull = GPIO_NOPULL;
    led.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(LED_PORT, &led);

    HAL_GPIO_WritePin(LED_PORT, LED_PIN, GPIO_PIN_SET);
}

void loop(void)
{
    HAL_GPIO_TogglePin(LED_PORT, LED_PIN);
    HAL_Delay(BLINK_HALF_PERIOD_MS);
}
