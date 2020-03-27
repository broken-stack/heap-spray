#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int secure_method() {
    printf("I did something.\n");
    return 1;
}

int main(void) {
    int size = 100 * sizeof(char);
    char* simulated_user_input = malloc(0);
    const char shellcode[] = "\xe9\x1e\x00\x00\x00\xb8\x04\x00\x00\x00\xbb\x01\x00\x00\x00\x59\xba\x0f\x00\x00\x00\xcd\x80\xb8\x01\x00\x00\x00\xbb\x00\x00\x00\x00\xcd\x80\xe8\xdd\xff\xff\xffHello world!\r\n";

    // simulate spraying all NOP over the heap
    for(int i = 1; i <= 1000; i++) {
        size = 100 * i * sizeof(char);
        
        // dynamically allocate more memory
        simulated_user_input = realloc(simulated_user_input, size);

        // fill input with NOP
        memset(simulated_user_input, '\x90', size);
    }

    // add shell code into the user input
    simulated_user_input = realloc(simulated_user_input, (sizeof(shellcode) * sizeof(char)));
    memcpy(simulated_user_input, shellcode, sizeof(shellcode) * sizeof(char));

    volatile int (*function_pointer)();
    char buffer[64];

    function_pointer = &secure_method;

    printf("Simulated user input\t 0x%08x\n", simulated_user_input);
    printf("Buffer for overflow\t 0x%08x\n", buffer);
    printf("Function pointer\t 0x%08x\n", &function_pointer);

    // corrupt the function pointer
    scanf("%s", buffer);

    // if function pointer exists, execute
    if (function_pointer)
    {
        printf("Calling func pointer\t 0x%08x\n", function_pointer);
        function_pointer();
    }
    return 0;
}
