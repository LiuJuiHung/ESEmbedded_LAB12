#include <stdint.h>
#include "reg.h"
#include "blink.h"

void setup_systick(uint32_t ticks);

int main(void)
{
	setup_systick(4200000); //200 ms (168e6 / 8 / 5)
	blink(LED_BLUE); //should not return
}

void setup_systick(uint32_t ticks)
{
	// set reload value
	WRITE_BITS(SYST_BASE + SYST_RVR_OFFSET, 23, 0, ticks - 1);

	// uses external reference clock
	CLEAR_BIT(SYST_BASE + SYST_CSR_OFFSET, SYST_CLKSOURCE_BIT);

	// enable systick exception
	SET_BIT(SYST_BASE + SYST_CSR_OFFSET, SYST_TICKINT_BIT);

	// enable systick
	SET_BIT(SYST_BASE + SYST_CSR_OFFSET, SYST_ENABLE_BIT);
}

void systick_handler(void)
{
	blink_count(LED_ORANGE, 1);
}
