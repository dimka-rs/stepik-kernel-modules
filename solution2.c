#include <linux/module.h>
#include <checker.h>

int init_module(void)
{
    printk(KERN_INFO "kernel_mooc: Hello world\n");
    call_me("Hello from my module!\n");
    return 0;
}

void cleanup_module(void)
{
    printk(KERN_INFO "kernel_mooc: Bye world\n");
}

MODULE_LICENSE("GPL");
