#include <linux/module.h>
#include <linux/slab.h>
#include <checker.h>

#define ARR_SIZE (64)
#define MSG_SIZE (1024)
#define TRIES (10)

void    *void_ptr;
int     *int_ptr;
struct device *dev_ptr;

int solution_init(void)
{
    printk(KERN_INFO "kernel_mooc: Hello world\n");

    void_ptr = kmalloc(get_void_size(), GFP_KERNEL);
    submit_void_ptr(void_ptr);

    int_ptr = (int *) kmalloc(sizeof(int)*get_int_array_size(), GFP_KERNEL);
    submit_int_array_ptr(int_ptr);

    dev_ptr = (struct device *) kmalloc(sizeof(struct device), GFP_KERNEL);
    submit_struct_ptr(dev_ptr);

    return 0;
}

void solution_exit(void)
{
    printk(KERN_INFO "kernel_mooc: Bye world\n");

    checker_kfree(void_ptr);
    checker_kfree(int_ptr);
    checker_kfree(dev_ptr);

}

module_init(solution_init);
module_exit(solution_exit);

MODULE_LICENSE("GPL");
