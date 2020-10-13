#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>

MODULE_LICENSE(”GPL”);
#define MODULE_NAME ”test_chardev_”
static char *test_data  =  ”test\n”;
static int dev_counter  =  0;
static int major;
static int chardev_open(struct inode*,struct file*);
static int chardev_release(struct inode*,struct file*);
static ssize_t chardev_read(struct file*,char*,size_t ,lofft*);

static  struct  file_operations chardev_operations =  {
	.open = chardev_open,
	.read = chardev_read,
	.release = chardev_release,
};

static  int  chardev_open(struct inode *inode, struct file *file) {
	if (dev_counter) return −EBUSY;
	dev_counter++;
	try_module_get(THIS_MODULE);
	return 0;
}

static int chardev_release(struct inode *inode, struct file *file) {
	dev_counter−−;
	module_put(THIS_MODULE);
	return 0;
}

static ssize_t chardev_read(struct file *file, char *buf, size_t count, loff_t *off) {
	int test_data_lenght = strlen(test_data);
	if(*off != 0) return 0;
	if(copy_to_user(buf, test_data, test_data_lenght)) return  −EINVAL;
	*off = test_data_lenght;
	return  test_data_lenght;
}

static int inittestchardev_init(void) {
	major = register_chrdev(0, ”test_chardev_”, &chardev_operations);
	printk(KERN_INFO” loaded_major_dev%d\n”, major);
	return 0;
}

static void __exit test_chardev_exit(void) {
	unregister_chrdev(major, MODULE_NAME);
	print k(KERN_INFO ”removed\n”);
}

moduleinit(test_chardev_init);
moduleexit(test_chardev_exit);
