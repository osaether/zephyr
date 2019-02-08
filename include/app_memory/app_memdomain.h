#ifndef ZEPHYR_INCLUDE_APP_MEMORY_APP_MEMDOMAIN_H_
#define ZEPHYR_INCLUDE_APP_MEMORY_APP_MEMDOMAIN_H_

#include <linker/linker-defs.h>
#include <misc/dlist.h>
#include <kernel.h>

#if defined(CONFIG_X86)
#define MEM_DOMAIN_ALIGN_SIZE _STACK_BASE_ALIGN
#elif defined(STACK_ALIGN)
#define MEM_DOMAIN_ALIGN_SIZE STACK_ALIGN
#else
#error "Not implemented for this architecture"
#endif

/*
 * There has got to be a better way of doing this. This
 * tries to ensure that a) each subsection has a
 * data_smem_#id_b part and b) that each k_mem_partition
 * matches the page size or MPU region.  If there is no
 * data_smem_#id_b subsection, then the size calculations
 * will fail. Additionally, if each k_mem_partition does
 * not match the page size or MPU region, then the
 * partition will fail to be created.
 * checkpatch.pl complains that __aligned(size) is
 * preferred, but, if implemented, then complains about
 * complex macro without parentheses.
 */
#define _app_dmem_pad(id) \
	__attribute__((aligned(MEM_DOMAIN_ALIGN_SIZE), \
		section("data_smem_" #id)))

#define _app_bmem_pad(id) \
	__attribute__((aligned(MEM_DOMAIN_ALIGN_SIZE), \
		section("data_smem_" #id "b")))

/**
 * @brief Place data in a partition's data section
 *
 * Globals tagged with this will end up in the data section for the
 * specified memory partition. This data should be initalized to some
 * desired value.
 *
 * @param id Name of the memory partition to associate this data
 */
#define K_APP_DMEM(id) \
	__attribute__((section("data_smem_" #id)))

/**
 * @brief Place data in a partition's bss section
 *
 * Globals tagged with this will end up in the bss section for the
 * specified memory partition. This data will be zeroed at boot.
 *
 * @param id Name of the memory partition to associate this data
 */
#define K_APP_BMEM(id) \
	__attribute__((section("data_smem_" #id "b")))

/*
 * Creation of a struct to save start addresses, sizes, and
 * a pointer to a k_mem_partition.  It also adds a linked
 * list node.
 */
struct app_region {
	char *dmem_start;
	char *bmem_start;
	u32_t smem_size;
	struct k_mem_partition *partition;
};

/*
 * Declares a partition and provides a function to add the
 * partition to the linked list and initialize the partition.
 */
#ifdef CONFIG_MPU_REQUIRES_POWER_OF_TWO_ALIGNMENT
/* For power of 2 MPUs linker provides support to help us
 * calculate the region sizes.
 */
#define smem_size_declare(name) extern char data_smem_##name##_size[]
#define smem_size_val(name) ((u32_t)&data_smem_##name##_size)
#else
#define smem_size_declare(name)
#define smem_size_val(name) 0
#endif	/* CONFIG_MPU_REQUIRES_POWER_OF_TWO_ALIGNMENT */

/**
 * @brief Define an application memory partition with linker support
 *
 * Defines a k_mem_paritition with the provided name.
 * This name may be used with the K_APP_DMEM and K_APP_BMEM macros to
 * place globals automatically in this partition.
 *
 * NOTE: placeholder char variable is defined here to prevent build errors
 * if a partition is defined but nothing ever placed in it.
 *
 * @param name Name of the k_mem_partition to declare
 */
#define K_APPMEM_PARTITION_DEFINE(name) \
	extern char *data_smem_##name; \
	extern char *data_smem_##name##b; \
	smem_size_declare(name);		  \
	_app_dmem_pad(name) char name##_dmem_pad; \
	_app_bmem_pad(name) char name##_bmem_pad; \
	struct k_mem_partition name = { \
		.start = (u32_t) &data_smem_##name, \
		.attr = K_MEM_PARTITION_P_RW_U_RW \
	}; \
	_GENERIC_SECTION(.app_regions.name) \
	struct app_region name##_region = { \
		.dmem_start = (char *)&data_smem_##name, \
		.bmem_start = (char *)&data_smem_##name##b, \
		.smem_size = smem_size_val(name), \
		.partition = &name \
	};

#endif /* ZEPHYR_INCLUDE_APP_MEMORY_APP_MEMDOMAIN_H_ */
