#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/fs.h>

struct file * f;

void test_file(void){
  if(f != NULL){
     char arr[100];

     char * str = "I just wrote something";
     file_write(f,0, str, strlen(str)); 

     memset(arr, '\0', 100);
     file_read(f, 0, arr, 20);
     printk(KERN_INFO "Read %s\n",arr); 

     file_close(f);
    }else{
     printk(KERN_ERR "Error! Cannot open file\n");
    }
}


void test_function(void){
   test_file(); // access the file from the kthread
} 


static int __init file_init(void) { 
    // Create and open the file in user space
    f = file_open("./interval.txt", O_CREAT |  O_RDWR | O_APPEND, \
                                S_IRWXU | S_IRWXG | S_IRWXO);

   struct task_struct * test_thread = kthread_run((void *)test_function, \
                                                   NULL, "Test");
}


module_init(file_init)
