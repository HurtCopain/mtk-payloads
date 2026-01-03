#include <stdint.h>
#include <drivers/uart.h>

void mtk_uart_putc(int ch) {
    while (!(*(volatile uint32_t*)(DEFAULT_UART_BASE + UART_LSR_OFFSET) & UART_LSR_THRE));
    *(volatile uint32_t*)(DEFAULT_UART_BASE + UART_THR_OFFSET) = ch;
}
