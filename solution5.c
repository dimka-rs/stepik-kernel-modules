#include <linux/module.h>
#include <linux/slab.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/init.h>
#include <linux/cdev.h>

static dev_t first;
static unsigned int count = 1;
static int my_major = 700;
static int my_minor = 0;
static struct cdev *my_cdev;

#define MYDEV_NAME "mychardev"
#define KBUF_SIZE (size_t)((10) * PAGE_SIZE)

static int mychrdev_open(struct inode *inode, struct file *file)
{
    static int counter = 0;
    char *kbuf = kmalloc(KBUF_SIZE, GFP_KERNEL);
    file->private_data = kbuf;
    counter++;

    printk(KERN_INFO "Opening device %s, counter = %d\n, refcounter = %d", MYDEV_NAME, counter, module_refcount(THIS_MODULE));
    return 0;
}


static int mychrdev_release(struct inode *inode, struct file *file)
{
    char *kbuf = file->private_data;
    if (kbuf)
        kfree(kbuf);
    kbuf = NULL;
    file->private_data = NULL;

    printk(KERN_INFO "Releasing device %s\n", MYDEV_NAME);
    return 0;
}


static ssize_t mychrdev_read(struct file *file, char __user *buf, size_t lbuf, loff_t *ppos)
{
    char *kbuf = file->private_data;
    int nbytes = lbuf - copy_to_user(buf, kbuf + *ppos, lbuf);
    *ppos += nbytes;

    printk(KERN_INFO "Reading device %s, nbytes = %d, ppos = %d\n", MYDEV_NAME, nbytes, (int)*ppos);
    return nbytes;
}


static ssize_t mychrdev_write(struct file *file, const char __user *buf, size_t lbuf, loff_t *ppos)
{
    char *kbuf = file->private_data;
    int nbytes = lbuf - copy_from_user(kbuf + *ppos, buf, lbuf);
    *ppos += nbytes;

    printk(KERN_INFO "Writing device %s, nbytes = %d, ppos = %d\n", MYDEV_NAME, nbytes, (int)*ppos);
    return nbytes;
}

static const struct file_operations mycdev_fops = {
    .owner = THIS_MODULE,
    .read    = mychrdev_read,
    .write   = mychrdev_write,
    .open    = mychrdev_open,
    .release = mychrdev_release
};

static int __init solution_init(void)
{
    printk(KERN_INFO "kernel_mooc: Hello world\n");

    first = MKDEV(my_major, my_minor);
    register_chrdev_region(first, count, MYDEV_NAME);

    my_cdev = cdev_alloc();
    cdev_init(my_cdev, &mycdev_fops);
    cdev_add(my_cdev, first, count);

    return 0;
}


static void __exit solution_exit(void)
{
    printk(KERN_INFO "kernel_mooc: Bye world\n");
    if (my_cdev)
        cdev_del(my_cdev);
    unregister_chrdev_region(first, count);
}

module_init(solution_init);
module_exit(solution_exit);

MODULE_LICENSE("GPL");
