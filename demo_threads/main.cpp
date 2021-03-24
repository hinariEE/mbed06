#include "mbed.h"
#include "mbed_events.h"

DigitalOut led(LED1);
DigitalOut led3(LED3);
EventQueue queue1;
EventQueue queue2;
InterruptIn btn(USER_BUTTON);

void printf_high() {
    printf("tHigh\n");
}

void printf_low() {
    printf("tLow\n");
}

void flip1() {
    led = !led;
    queue1.call(&printf_high);
}

void flip2() {
    led3 = !led3;
    queue2.call(&printf_low);
}

int main() {

    Thread tHigh(osPriorityNormal);
    tHigh.start(callback(&queue1, &EventQueue::dispatch_forever));

    Thread tLow(osPriorityLow);
    tLow.start(callback(&queue2, &EventQueue::dispatch_forever));

    Ticker printfTicker;
    printfTicker.attach(&flip1, 1s);

    btn.fall(&flip2);

    while (1) ;
}
