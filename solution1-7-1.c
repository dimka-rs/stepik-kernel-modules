#include <linux/module.h>

int init_module(void)
{
    printk(KERN_INFO "kernel_mooc: Hello world\n");
    return 0;
}

void cleanup_module(void)
{
    printk(KERN_INFO "kernel_mooc: Bye world\n");
}

MODULE_LICENSE("GPL");
