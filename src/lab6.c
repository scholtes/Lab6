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

#define BUFF_SIZE 100

MODULE_LICENSE("GPL");

int init_module(void) {
    printk("lab6 module installing\n");

    return 0;
}

void cleanup_module(void) {
    printk("lab6 module uninstalling\n");

    return;
}