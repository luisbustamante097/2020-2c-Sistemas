#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

static int __init nulo_init(void) {
	//printk(KERN_ALERT "Hola, Sistemas Operativos!\n");
	return 0;
}

static void __exit nulo_exit(void) {
	//printk(KERN_ALERT "Adios, mundo cruel...\n");
}

module_init(nulo_init);
module_exit(nulo_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("La banda de SO");
MODULE_DESCRIPTION("Una suerte de 'Hola, mundo'");
