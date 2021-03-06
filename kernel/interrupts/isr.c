#include "../include/types.h"
#include "../include/interrupts/isr.h"
#include "../include/interrupts/pic.h"
#include "../include/VGA.h"
#include "../include/defs.h"
#include "../constants/kbScancode.h"

void (*isr_funcs[NINTRS])(); // function ptr to handlers

// See
// https://www.amd.com/system/files/TechDocs/24593.pdf
char *exception_messages[] = {
    "Division by Zero\n",
    "Debug\n",
    "Non-Maskable Interrupt\n",
    "Breakpoint\n",
    "Overflow\n",
    "Out of Bounds\n",
    "Invalid Opcode\n",
    "No Coprocessor\n",

    "Double Fault\n",
    "Coprocessor Segment Overrun\n",
    "Bat TSS\n",
    "Segment not Present\n",
    "Stack Fault\n",
    "General Protection Fault\n",
    "Page Fault\n",
    "Unknown Interrupt\n",

    "Coprocessor Fault\n",
    "Alignment Check\n",
    "Reserved\n",
    "Reserved\n",
    "Reserved\n",
    "Reserved\n",
    "Reserved\n",

    "Reserved\n",
    "Reserved\n",
    "Reserved\n",
    "Reserved\n",
    "Reserved\n",
    "Reserved\n",
    "Reserved\n",
    "Reserved\n",
    "Reserved\n",

    "Timer\n",
    "Keyboard\n",
};

void
doublefault_handler()
{
    // VGA_panic("panic(): double fault");
}

void
timer_handler()
{
    // vga_putc('.');
    end_interrupt(IRQ_TIMER);
}

void
keyboard_handler()
{
    const u8 n = r_port(0x60);
    // do nothing on null ascii
    if(kbsc[n])
        vga_putc(kbsc[n]);

    end_interrupt(IRQ_KB);
}

void
isr_registry()
{
    isr_funcs[IRQ_DOUBLEFAULT] = doublefault_handler;
    isr_funcs[IRQ_TIMER] = timer_handler;
    isr_funcs[IRQ_KB] = keyboard_handler;
}

// called from isr_wrap.S, by isr_common
// a naive handler for now, will use intr_nr to multiplex to other C functions
void
irq_handler(isf sf)
{
    if(isr_funcs[sf.intr_nr])
        isr_funcs[sf.intr_nr]();
    else{
        const char *msg = exception_messages[sf.intr_nr];
        vga_putstr(msg);
    }
}