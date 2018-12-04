#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/module.h>
#include <linux/io.h>
#include <linux/gpio.h>
#include <asm/uaccess.h>
#include <linux/delay.h>
#include <linux/time.h>
#include <linux/interrupt.h>


//#include <mach/platform.h>
#define GPIO_BASE	0x3f200000

MODULE_LICENSE("GPL");

#define GPIO_MAJOR	243
#define GPIO_MINOR	0
#define GPIO_DEVICE	"sensor"
#define GPIO_TRIG	18
#define GPIO_ECHO	24

unsigned int distance;
volatile unsigned *gpio;
//static char msg[BLOCK_SIZE] = {0};

static int gpio_open(struct inode*, struct file*);
//static ssize_t gpio_read(struct file*, char*, size_t, loff_t*);
//static ssize_t gpio_write(struct file*, const char*, size_t, loff_t*);
static int gpio_close(struct inode*, struct file*);
static long gpio_ioctl(struct file *flip, unsigned int, unsigned long);

static struct file_operations gpio_fops = {

	.owner = THIS_MODULE,
	//.read = gpio_read,
	//.write = gpio_write,
	.unlocked_ioctl = gpio_ioctl,
	.open = gpio_open,
	.release = gpio_close,

};

struct cdev gpio_cdev;
struct timeval after, before;


int start_module(void){

	dev_t devno;
	unsigned int count;
	int err;

	//printk(KERN_INFO "Hello module\n");

	devno = MKDEV(GPIO_MAJOR, GPIO_MINOR);
	register_chrdev_region(devno, 1, GPIO_DEVICE);

	cdev_init(&gpio_cdev, &gpio_fops);

	gpio_cdev.owner = THIS_MODULE;
	count = 1;
	err = cdev_add(&gpio_cdev, devno, count);
	if(err<0){
	
		printk("ERROR : DEVICE Add\n");
		return -1;
	}
	gpio_request(GPIO_TRIG,"TRIG");
	gpio_direction_output(GPIO_TRIG,0);
	gpio_request(GPIO_ECHO,"ECHO");
	gpio_direction_input(GPIO_ECHO);

	//printk("'mknod /dev/%s c %d 0'\n", GPIO_DEVICE, GPIO_MAJOR);
	//printk("'chmod 666 /dev/%s'\n", GPIO_DEVICE);

	return 0;


}

void end_module(void) {

	dev_t devno = MKDEV(GPIO_MAJOR, GPIO_MINOR);
	unregister_chrdev_region(devno,1);

	cdev_del(&gpio_cdev);

    gpio_free(GPIO_TRIG);
    gpio_free(GPIO_ECHO);

	//printk(KERN_INFO "Good bye module!!\n");
}

	module_init(start_module);
	module_exit(end_module);

	static int gpio_open(struct inode *inod, struct file *fil){
	
		//printk("GPIO Device opened(%d/%d)\n", imajor(inod), iminor(inod));
		try_module_get(THIS_MODULE);
		return 0;
	}

	static int gpio_close(struct inode* inod, struct file* fil){
	
		//printk("GPIO Device closed(%d/%d)\n", imajor(inod), iminor(inod));
		module_put(THIS_MODULE);
		return 0;
	}


static long gpio_ioctl(struct file *flip, unsigned int tmp, unsigned long arg)
{
	int count;
	gpio_set_value(GPIO_TRIG,1);
	udelay(10);
	gpio_set_value(GPIO_TRIG,0);

	while(gpio_get_value(GPIO_ECHO)==0);
	do_gettimeofday(&before);

	while(gpio_get_value(GPIO_ECHO)==1);
	do_gettimeofday(&after);

	distance = (after.tv_usec - before.tv_usec)*34/1000/2;
	count = copy_to_user((void*)arg,(const void*)&distance,sizeof(int));
	return count;
}



/*


static ssize_t gpio_read(struct file* inode, char* buff, size_t len, loff_t* off){

	int count;
	strcat(msg, "from kernel");
	count = copy_to_user(buff, msg, strlen(msg)+1);
	printk("GPIO Device(%d) read : %s(%d)\n", 243, msg, count);

	return count;
}
static ssize_t gpio_write(struct file* inode, const char* buff, size_t len, loff_t* off){

	short count;
	memset(msg, 0, BLOCK_SIZE);
	count = copy_from_user(msg, buff, len);

    if(gpio_get_value(GPIO_SW) && !gpio_get_value(GPIO_LED)){
        gpio_set_value(GPIO_LED, 1);
    } 
    else if(gpio_get_value(GPIO_SW) && gpio_get_value(GPIO_LED)) {
    
        gpio_set_value(GPIO_LED, 0);
    }

	//printk("GPIO Device(%d) write : %s(%d)\n", 243, msg, len);
	return count;
}

*/

