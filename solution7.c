#include <linux/kobject.h>
#include <linux/string.h>
#include <linux/sysfs.h>
#include <linux/module.h>
#include <linux/init.h>

static int a, b, count;
static int c[5];

module_param(a, int, 0);
module_param(b, int, 0);
module_param_array(c, int, &count, 0);

static ssize_t my_sys_show(struct kobject *kobj, struct kobj_attribute *attr,
                           char *buf)
{
    return sprintf(buf, "%d\n", a+b+c[0]+c[1]+c[2]+c[3]+c[4]);
}

static ssize_t my_sys_store(struct kobject *kobj, struct kobj_attribute *attr,
                            const char *buf, size_t count)
{
    return count;
}

static struct kobj_attribute my_sys_attribute =
    __ATTR(my_sys, 0664, my_sys_show, my_sys_store);

static struct attribute *attrs[] = {
    &my_sys_attribute.attr,
    NULL,   /* need to NULL terminate the list of attributes */
};

static struct attribute_group attr_group = {
    .attrs = attrs,
};

static struct kobject *my_kobj;

static int __init solution_init(void)
{
    int retval;

    printk(KERN_INFO "kernel_mooc: Hello world\n");

    my_kobj = kobject_create_and_add("my_kobject", kernel_kobj);
    if (!my_kobj)
        return -ENOMEM;

    retval = sysfs_create_group(my_kobj, &attr_group);
    if (retval)
        kobject_put(my_kobj);

    return 0;
}


static void __exit solution_exit(void)
{
    printk(KERN_INFO "kernel_mooc: Bye world\n");
    kobject_put(my_kobj);
}

module_init(solution_init);
module_exit(solution_exit);

MODULE_LICENSE("GPL");
