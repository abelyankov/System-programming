#include <linux/module.h>
#include <linux/delay.h>
#include <linux/kthread.h>
#include <linux/jiffies.h>
#include <linux/power_supply.h>


 
static int N = 2;            // N - число потоков
module_param( N, int, 0 );
int _ret = 0;
char _path[] = "..";

static int __init kernel_syscall_init(void) {

}
 
 

 
static int thread_fun1( void* data ) {
   int N = (int)data - 1;
   struct task_struct *t1 = NULL;
   printk( "%s is parent [%05d]\n", current->parent->pid );
   if( N > 0 ){
      t1 = kthread_run( thread_fun1, (void*)N, "my_thread_%d", N );
   }
   while( !kthread_should_stop() ) {
	printk("time to back appp");
      msleep( 10000 );
   }
   printk( "%s find signal!\n");
   if( t1 != NULL ) kthread_stop( t1 );
   printk( "%s is completed\n" );
   return 0;
}

static int test_thread( void ) {
   struct task_struct *t1;

   t1 = kthread_run( thread_fun1, (void*)N, "my_thread_%d", N );
   msleep( 10000 );

   return -1;
}

static int __init init_threads(void) {
	test_thread();
}
 


 
static void __exit dev_exit(void){
	printk(KERN_INFO "ASDASDASDASDASDASD");
}

module_init(init_threads);
module_exit(dev_exit);

MODULE_LICENSE("GPL");
