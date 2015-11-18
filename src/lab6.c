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
#define WAIT_TIME 10 // In seconds

MODULE_LICENSE("GPL");

struct cdev *kernel_cdev;
dev_t dev_no;
int Major;

char buffer[BUFF_SIZE];
struct rw_semaphore sema;

wait_queue_head_t queue;


ssize_t read(struct file *filp, char *buff, size_t count, loff_t *offp) {
    // Grab the semaphore for readers (lock out writers)
    down_read(&sema);
    // Wait so that we can test for concurrency issues
    wait_event_timeout(queue, 0, WAIT_TIME*HZ);
    copy_to_user(buff, buffer, count);
    // Release the semaphore for readers (writers can now write)
    up_read(&sema);
    // Return the number of bytes read, because that's what the
    // documentation on the man pages says to do
    return count;
}

ssize_t write(struct file *filp, const char *buff, size_t count, loff_t *offp) {
    // Graph the semaphore for THIS writer (lock out all other readers AND writers)
    down_write(&sema);
    // Wait so that we can test for concurrency issues
    wait_event_timeout(queue, 0, WAIT_TIME*HZ);
    copy_from_user(buffer, buff, count);
    // Release the semaphore for this writer (open for reading or writing now)
    up_write(&sema);
    return count;
}

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

    init_rwsem(&sema);

    init_waitqueue_head(&queue);

    printk("lab6 major number: %d\n", Major);

    return 0;
}

void cleanup_module(void) {
    printk("lab6 module uninstalling\n");

    cdev_del(kernel_cdev);
    unregister_chrdev_region(dev_no, 1);
    unregister_chrdev(Major, "interface");

    return;
}