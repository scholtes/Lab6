/* Author: Garrett Scholtes
 * Date:   2015-10-25
 * 
 * Lab6 - CS4029
 * 
 * This module serves as a basic device driver, implemented using a read-write
 * semaphore.  An extra application and script is included for testing.
 * 
 */

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/sched.h>
#include <linux/rwsem.h>
#include <linux/cdev.h>
#include <asm/uaccess.h>
#include <linux/fs.h>

#define BUFF_SIZE 100

MODULE_LICENSE("GPL");

struct cdev *kernel_cdev;
dev_t dev_no;
int Major;


ssize_t read(struct file *filp, char *buff, size_t count, loff_t *offp) { return 0; }

ssize_t write(struct file *filp, const char *buff, size_t count, loff_t *offp) { return 0; }

int open(struct inode *inode, struct file *filp) { return 0; }

int release(struct inode *inode, struct file *filp) { return 0; }

struct file_operations fops = {
    .read = read,
    .write = write,
    .open = open,
    .release = release
};

int init_module(void) {
    int ret;
    int dev;

    printk("lab6 module installing\n");

    kernel_cdev = cdev_alloc();
    kernel_cdev->ops = &fops;
    ret = alloc_chrdev_region(&dev_no, 0, 1, "interface");

    Major = MAJOR(dev_no);
    dev = MKDEV(Major, 0);
    ret = cdev_add(kernel_cdev, dev, 1);

    return 0;
}

void cleanup_module(void) {
    printk("lab6 module uninstalling\n");

    cdev_del(kernel_cdev);
    unregister_chrdev_region(dev_no, 1);
    unregister_chrdev(Major, "interface");

    return;
}