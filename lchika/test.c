#include <stdint.h>

//regs
#define REG_RW(x)                  ((x) + 0x0000)
#define REG_XOR(x)                 ((x) + 0x1000)
#define REG_SET(x)                 ((x) + 0x2000)
#define REG_CLR(x)                 ((x) + 0x3000)

#define GPIO_RW(x)                 ((x) + 0x0)
#define GPIO_SET(x)                ((x) + 0x4)
#define GPIO_CLR(x)                ((x) + 0x8)

#define RESETS_BASE                (0x4000C000)
#define RESETS_RESET               (RESETS_BASE + 0x0)
#define RESETS_WDSEL               (RESETS_BASE + 0x4)
#define RESETS_RESET_DONE          (RESETS_BASE + 0x8)
#define RESETS_RESET_IO_BANK0      (1 << 5)

#define SIO_BASE                   (0xD0000000)
#define SIO_GPIO_OUT               (SIO_BASE + 0x10)
#define SIO_GPIO_OE                (SIO_BASE + 0x20)

#define IO_BANK0_BASE              (0x40014000)
#define IO_BANK_GPIO_STATUS(num)   (IO_BANK0_BASE + (num * 0x4 * 2) + 0x0)
#define IO_BANK_GPIO_CTRL(num)     (IO_BANK0_BASE + (num * 0x4 * 2) + 0x4)

//gpio functions
#define GPIO_FUNC_XIP              (0)
#define GPIO_FUNC_SPI              (1)
#define GPIO_FUNC_UART             (2)
#define GPIO_FUNC_I2C              (3)
#define GPIO_FUNC_PWM              (4)
#define GPIO_FUNC_SIO              (5)
#define GPIO_FUNC_PIO0             (6)
#define GPIO_FUNC_PIO1             (7)
#define GPIO_FUNC_GPCK             (8)
#define GPIO_FUNC_USB              (9)
#define GPIO_FUNC_NULL             (0xf)
#define GPIO_LED_NUM               (25)

void
write32(volatile uint32_t addr, uint32_t value)
{
	*(volatile uint32_t *)addr = value;
}

uint32_t
read32(volatile uint32_t addr)
{
	return *(volatile uint32_t *)addr;
}

void
sleep_ms(volatile int a)
{
	while(a-- > 0);
}

void
reset()
{
	write32(REG_CLR(RESETS_RESET), RESETS_RESET_IO_BANK0);
	while((read32(RESETS_RESET_DONE) & RESETS_RESET_IO_BANK0) == 0)
	    sleep_ms(256);
}

void
setup_gpio()
{
	write32(GPIO_CLR(SIO_GPIO_OE), (1 << GPIO_LED_NUM));
	write32(GPIO_CLR(SIO_GPIO_OUT), (1 << GPIO_LED_NUM));
	write32(IO_BANK_GPIO_CTRL(GPIO_LED_NUM), GPIO_FUNC_SIO);
	write32(GPIO_SET(SIO_GPIO_OE), (1 << GPIO_LED_NUM));
}

int
main()
{
	reset();
	setup_gpio();
	while (1) {
		write32(GPIO_SET(SIO_GPIO_OUT), (1 << GPIO_LED_NUM));
		sleep_ms(0xFFFF);
		write32(GPIO_CLR(SIO_GPIO_OUT), (1 << GPIO_LED_NUM));
		sleep_ms(0xFFFF);
	}
	return 0;
}

