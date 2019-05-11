#include <linux/fs.h>
#include <asm/segment.h>
#include <asm/uaccess.h>
#include <linux/buffer_head.h>
#include <linux/kthread.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>


struct file* file_open(const char* path, int flags, int rights) {
    struct file* filp = NULL;
    mm_segment_t oldfs;
    int err = 0;

    oldfs = get_fs();
    set_fs(get_ds());
    filp = filp_open(path, flags, rights);
    set_fs(oldfs);
    if(IS_ERR(filp)) {
        err = PTR_ERR(filp);
        return NULL;
    }
    return filp;
}

void file_close(struct file* file) {
    filp_close(file, NULL);
}

int file_read(struct file* file, unsigned long long offset, unsigned char* data, unsigned int size) {
    mm_segment_t oldfs;
    int ret;

    oldfs = get_fs();
    set_fs(get_ds());

    ret = vfs_read(file, data, size, &offset);

    set_fs(oldfs);
    return ret;
}

int file_write(struct file* file, unsigned long long offset, unsigned char* data, unsigned int size) {
    mm_segment_t oldfs;
    int ret;

    oldfs = get_fs();
    set_fs(get_ds());

    ret = vfs_write(file, data, size, &offset);

    set_fs(oldfs);
    return ret;
}

int file_sync(struct file* file) {
    vfs_fsync(file, 0);
    return 0;
}

struct file * f;
struct file * fw;

void test_file(void){
  if(f != NULL){
     char arr[100];
     file_read(f, 0, arr, 20);
     printk(KERN_INFO "Read %s\n",arr); 
     
    fw = file_open("./testBAckUoFile.txt", O_CREAT |  O_RDWR | O_APPEND, \
                                S_IRWXU | S_IRWXG | S_IRWXO);

     char * str = "I just wrote something";
     file_write(fw,0, arr, strlen(str)); 

     memset(arr, '\0', 100);

     file_close(f);
     file_close(fw);
    }else{
     printk(KERN_ERR "Error! Cannot open file\n");
    }
}


void test_function(void){
   test_file(); 
} 


static int __init file_init(void)
{ 

    f = file_open("./testtesta.txt", O_CREAT |  O_RDWR | O_APPEND, \
                                S_IRWXU | S_IRWXG | S_IRWXO);

   struct task_struct * test_thread = kthread_run((void *)test_function, \
                                                   NULL, "Test");
	return 0;
}

static void __exit dev_exit(void){
	printk(KERN_INFO "ASDASDASDASDASDASD");
}

module_init(file_init);
module_exit(dev_exit);

MODULE_LICENSE("GPL");
