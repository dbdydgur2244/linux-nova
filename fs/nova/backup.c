#include <linux/list.h>

#include "backup.h"
#include "nova.h"
#include "inode.h"

static struct list backup_list;

/*
 * declaration in nova.h
 * assume that already checked whether the file is read before calling this function.
 * caculate rari value of each data block
 */
bool nova_calculate_rari(struct nova_file_write_entry *prev_entry, struct nova_file_write_entry *new_entry)
{   
    // caculate ...
}

/*
 * backup을 할 때 필요한 정보
 * 1. inode address
 * 2. nova_inode_info address
 */

/* backup시 체크해야하는 정보
 * 1. 지금 garbage collection이 제거하는 inode가 backup node에 있는지
 */ 

/* 
 * invalid log entry로 변하는 과정
 * 1. nova_reassign_file_tree (in file.c)
 * 2. nova_reassign_file_tree (in dax.c)
 * 3. nova_assign_write_entry (in log.c)
 * 4. (1)if free flag is true -> nova_free_old_entry (in log.c)
 *       -> nova_invalidate_write_entry -> nova_invalidate_reassign_logentry
 *       -> nova_execute_invalidate_reassign_logentry
 *          => if (type == FILE_WRITE)
 *             invalid_pages += num_free
 *             if (invalid_pages == num_pages)
 *                 invalid = 1 => nova_inc_page_invalid_entries
 *    (2)if not, nova_invalidate_write_entry (in log.c)
 */

/*
 * called in do_nova_cow_file_write
 * Because access_ok and inode_integrity are already done in do_nova_cow_file_write,
 * no checking in do_back_up
 * return backup success(0)/fail(1)
 */
bool do_nova_backup(struct nova_file_write_entry *entry,
                    struct nova_indoe *pi,
                    struct nova_inode_log_page *log_page)
{
    struct backup_list_item *new_list_elem;

    INIT_TIMING(backup_time);
    NOVA_START_TIMING(do_backup_t, backup_time);

    // pi = nova_get_block(sb, sih->pi_addr);
    new_list_elem = kmalloc(sizeof(struct backup_list_item), GFP_ATOMIC);
    if (!new_list_elem) {
        return 1;
    }
    new_list_elem->entry    = entry;
    new_list_elem->pi       = pi;
    new_list_elem->log_page = log_page;
    list_push_back(&backup_list, &new_list_elem->elem);
    nova_dbgv("%s: backup listt\n", __func__)

    NOVA_END_TIMING(do_backup_t, backup_time);
    return 0;
}
