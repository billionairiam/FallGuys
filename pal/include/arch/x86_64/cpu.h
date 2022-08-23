#pragma once

#define PAGE_SIZE (1<<12)
#define PRESET_PAGESIZE PAGE_SIZE

static inline noreturn void die_or_inf_loop(void){
    __asm__ volatile(
        "1: \n"
        "ud2 \n"
        "jmp 1b\n"
    );
    //Remove dead code (that programmer knows will never be executed)
    //Linearize the code by letting compiler know that the path is "cold" 
    //(similar effect is achieved by calling noreturn function)
    __builtin_unreachable();
}