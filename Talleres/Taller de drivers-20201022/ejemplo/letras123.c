#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/cdev.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <linux/uaccess.h>
#include <linux/slab.h>
#include <linux/random.h>

unsigned int azar_max = 0;
unsigned int random, res, cant_char;
char *ptr;

ssize_t azar_read(struct file *filp, char __user *data, size_t s, loff_t *off) {
    if (azar_max == 0) {return -EPERM;}
    
    get_random_bytes(&random, sizeof(int));
    printk(KERN_ALERT "get_random");
    res = random;
    res = res % azar_max;
    printk(KERN_ALERT "%d %d\n", random, res);
    
    ptr = (char*) kmalloc(s+1, GFP_KERNEL);
    printk(KERN_ALERT "kmalloc");
    cant_char = snprintf(ptr, s+1, "%d\n", res);
    printk(KERN_ALERT "snprintf");
    copy_to_user(data, ptr, cant_char);
    printk(KERN_ALERT "copy_to");
    kfree(ptr);
    printk(KERN_ALERT "kfree");
    return s;
}

ssize_t azar_write(struct file *filp, const char __user *data, size_t s, loff_t *off) {
    
    ptr = (char*) kmalloc(s+1, GFP_KERNEL);
    ptr[s] = '\0';
    
    copy_from_user(ptr, data, s);
    if (kstrtoint(ptr, 10, &azar_max)) {return -EPERM;}
    
    kfree(ptr);

    printk(KERN_ALERT "%d\n", azar_max);
    
    return s;
}

static struct cdev dev;
const static struct file_operations fops = {.owner = THIS_MODULE, .read = azar_read, .write = azar_write};
static dev_t num;
static struct class *mi_class;
char *nombre;

static int __init azar_init(void) {
    nombre = "azar";
	// inicializamos el dispositivo
	cdev_init(&dev, &fops);

	// pedimos major y minor al kernel
    alloc_chrdev_region(&num, 0, 1, nombre);
	
	// asignamos major y minor al dispositivo
	cdev_add(&dev, num, 1);
	
	// cremos los nodos del fs
	mi_class = class_create(THIS_MODULE, nombre);
    device_create(mi_class, NULL, num, NULL, nombre);
	
	return 0;
}

static void __exit azar_exit(void) {
    // finalizo device
    unregister_chrdev_region(num, 1);
    cdev_del(&dev);
    
    // desasigno del fs
    device_destroy(mi_class, num);
    class_destroy(mi_class);
    
    return;
}

module_init(azar_init);
module_exit(azar_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("La banda de SO");
MODULE_DESCRIPTION("Una suerte de 'Hola, mundo'");
