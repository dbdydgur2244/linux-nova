#ifndef __BACKUP_H
#define __BACKUP_H

struct backup_list_item
{
    struct list_elem elem;
    struct nova_file_write_entry *entry;
    struct nova_inode *pi;
    struct nova_inode_log_page *log_page;
};

bool do_nova_backup(struct nova_file_write_entry *entry,
                    struct nova_indoe *pi,
                    struct nova_inode_log_page *log_page);

#endif
