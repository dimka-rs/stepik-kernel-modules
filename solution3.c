#include <linux/module.h>
#include <checker.h>
//extern int array_sum(short *arr, size_t n);

#define ARR_SIZE (64)
#define MSG_SIZE (1024)
#define TRIES (10)

int solution_init(void)
{
    short buf[ARR_SIZE];
    char  msg[MSG_SIZE];
    int   chk_sum, i, t;

    CHECKER_MACRO;
    printk(KERN_INFO "kernel_mooc: Hello world\n");

    /* Fill buffer with values */
    for (i = 0; i < ARR_SIZE; i++)
    {
        buf[i] = i;
    }

    for (t = 0; t < TRIES; t++)
    {
        int my_sum = 0;

        for (i = 0; i < ARR_SIZE; i++)
        {
            my_sum += buf[i];
        }
        chk_sum = array_sum(buf, ARR_SIZE);
        generate_output(chk_sum, buf, ARR_SIZE, msg);

        if (my_sum == chk_sum)
        {
            printk(KERN_INFO "kernel_mooc: %s\n", msg);
        }
        else
        {
            printk(KERN_ERR  "kernel_mooc: %s\n", msg);
        }
    }

    return 0;
}

void solution_exit(void)
{
    CHECKER_MACRO;
    printk(KERN_INFO "kernel_mooc: Bye world\n");
}

module_init(solution_init);
module_exit(solution_exit);

MODULE_LICENSE("GPL");
