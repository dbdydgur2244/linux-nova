#ifndef __BACKUP_H
#define __BACKUP_H

#include <linux/mutex.h>

/* 
 * brining from snapshot_list
 *
 * DRAM log of updates to a backup
 */
struct backup_list 
{
    struct mutx list_mutex;
    unsigned long num_pages;
    unsigned long head;
    unsigned long tail;
};

struct backup_info 
{
    u64 epoch_id; // inode_entry number
    u64 timestamp; // the recent time stamp
    unsigned long backup_entry; // PMEM pointer to the struct
    struct backup_list *lists;  // Per-CPU backup list 
};

enum nova_backup_entry_type
{
    SS_INODE = 1,
    SS_FILE_WRITE,
};

/*
 * brining from snapshot.h
 */
struct backup_inode_entry
{
    u8 type;
    u8 deleted;
    u8 padding[6];
    u64 timestamp;
    u64 nova_ino; // inode number that was deleted
    u64 delete_epoch_id;
} __attributed((__packed__));

/*
 *  bringing from snapshot_file_write_entry in snapshot.h
 */
struct backup_file_write_entry
{
    u8 type;
    u8 deleted;
    u8 padding[6];
    u64 nvmm;
    u64 num_pages;
    u64 delete_epoch_id;
} __attribute((__packed__));

/*
 *  bringing from snapshot_file_write_entry in snapshot.h
 */
struct backup_nvmm_list
{
    __le64 padding;
    __le64 num_pages;
    __le64 head;
    __le64 tail;
} __attribute((__packed__));

/*
 *  bringing from snapshot_file_write_entry in snapshot.h
 */
struct backup_nvmm_page
{
    struct backup_nvmm_list lists[128];
};


#endif
