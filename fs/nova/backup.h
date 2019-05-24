#ifndef __BACKUP_H
#define __BACKUP_H

#include <linux/list.h>

struct backup_list_item
{
    struct list_head list;
    struct nova_file_write_entry *entry;
    struct nova_inode *pi;
};

bool do_nova_backup(struct nova_file_write_entry *entry,
                    struct nova_inode *pi);

#endif
