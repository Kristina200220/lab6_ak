#include <linux/module.h>
#include <linux/init.h>
#include <linux/printk.h>
#include <linux/ktime.h>
#include <linux/slab.h>

struct head_list
{
    struct head_list *next;
    ktime_t time;
};

MODULE_AUTHOR("Kristina Bondar <kristina.bondar200220@gmail.com>");
MODULE_DESCRIPTION("Hello, world in Linux Kernel Training");
MODULE_LICENSE("Dual BSD/GPL");

static struct head_list *head;

static int count = 1;
module_param(count, uint, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);
MODULE_PARM_DESC(count, "A parameter that determines how many times the message will be displayed. Accepts values from 0-10.");

static int __init hello_init(void)
{
    uint i = 0;

    struct head_list *var_1, *var_2;

    head = kmalloc(sizeof(struct head_list *), GFP_KERNEL);


    var_1 = head;
    if(count == 0)
    {
        printk(KERN_WARNING "Be careful, the value is so small!!!");
    }
    else if(count >= 5 && count <= 10)
    {
        printk(KERN_WARNING "Be careful, the value is midle!");
    }
    BUG_ON(count > 10);

    for(i=0; i < count; i++)
    {
        var_1->next = kmalloc(sizeof(struct head_list), GFP_KERNEL);
        if (i == 6) var_1 = NULL;
        var_1->time = ktime_get();
        printk(KERN_EMERG "Hello, world!\n");
        var_2 = var_1;
        var_1 = var_1->next;
    }

    if (count != 0) {
        kfree(var_2->next);
        var_2->next = NULL;
    }


    printk(KERN_INFO "Count: %d\n", count);

    return 0;
}

static void __exit hello_exit(void)
{
    struct head_list *var;

    while (head != NULL && count != 0) {
        var = head;
        printk(KERN_INFO "Printing time: %lld\n", var->time);
        head = var->next;
        kfree(var);
    }
}

module_init(hello_init);
module_exit(hello_exit);
