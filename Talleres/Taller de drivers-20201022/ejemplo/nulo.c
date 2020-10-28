#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/cdev.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <linux/uaccess.h>
#include <linux/slab.h>

ssize_t nulo_read(struct file *filp, char __user *data, size_t s, loff_t *off) {
    return 0;
}

ssize_t nulo_write(struct file *filp, const char __user *data, size_t s, loff_t *off) {
    return s;
}

static struct cdev dev;
const static struct file_operations fops = {.owner = THIS_MODULE, .read = nulo_read, .write = nulo_write};
static dev_t num;
static struct class *mi_class;

static int __init nulo_init(void) {
	// inicializamos el dispositivo
	cdev_init(&dev, &fops);

	// pedimos major y minor al kernel
    alloc_chrdev_region(&num, 0, 1, "nulo");
	
	// asignamos major y minor al dispositivo
	cdev_add(&dev, num, 1);
	
	// cremos los nodos del fs
	mi_class = class_create(THIS_MODULE, "nulo");
    device_create(mi_class, NULL, num, NULL, "nulo");
	
	return 0;
}

static void __exit nulo_exit(void) {
    // finalizo device
    unregister_chrdev_region(num, 1);
    cdev_del(&dev);
    
    // desasigno del fs
    device_destroy(mi_class, num);
    class_destroy(mi_class);
    
    return;
}

module_init(nulo_init);
module_exit(nulo_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("La banda de SO");
MODULE_DESCRIPTION("Una suerte de 'Hola, mundo'");
