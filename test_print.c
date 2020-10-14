#include <linux/init.h>
#include <linux/module.h>


MODULE_LICENSE("GPL");

static int __init test_printk_init(void) {
	printk(KERN_INFO "inserted\n");
	return 0;
}

static void __exit test_printk_exit(void) {
	printk(KERN_INFO "removed\n");
   // return 0;
}

module_init(test_printk_init);
module_exit(test_printk_exit);





