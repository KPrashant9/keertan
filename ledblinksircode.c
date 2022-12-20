#define unit32 unsigned int
	
volatile unit32 *RCC_CR = 0x40023800;
volatile unit32 *RCC_AHB1ENR = 0x40023800 + 0x30;
volatile unit32 *GPIOG_MODER = 0x40021800;
volatile unit32 *GPIOG_OTYPER = 0x40021800 + 0x04;
volatile unit32 *GPIOG_OSPEEDR = 0x40021800 + 0x08;
volatile unit32 *GPIOG_PUPDR = 0x40021800 + 0x0C;
volatile unit32 *GPIOG_ODR = 0x40021800 + 0x14;

void clock_internal_enable();
void gpio_init();
void blink_led();

int main()
{
	clock_internal_enable();
	gpio_init();
	while (1)
	{
		blink_led();
	}
}
void clock_internal_enable()
{
	*RCC_CR |=(1<<0);
	*RCC_AHB1ENR = (1<<6);
}
void gpio_init()
{
	*GPIOG_MODER |= (1<<26);
	*GPIOG_MODER &= ~(1<<27);
	*GPIOG_OTYPER &= ~(1<<13);
	*GPIOG_OSPEEDR &= ~(1<<27);
	*GPIOG_OSPEEDR |= (1<<26);
	*GPIOG_PUPDR &= ~(1<<27);
	*GPIOG_PUPDR &= ~(1<<26);
}
void blink_led()
{
	for (unit32 i=0; i<900000; i++)
	{
		*GPIOG_ODR |=(1<<13);
	}
	for (unit32 i=0; i<100000; i++)
	{
		*GPIOG_ODR &= ~(1<<13);
	}
}
