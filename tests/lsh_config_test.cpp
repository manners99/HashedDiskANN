#include "index.h"
#include "index_config.h"
#include <gtest/gtest.h>

TEST(IndexConfigTest, LSHInitialization) {
    // Step 1: Create an IndexConfig with LSH enabled
    size_t num_hash_tables = 10;
    size_t num_hashes_per_table = 50;

    diskann::IndexConfig index_config = diskann::IndexConfigBuilder()
        .with_metric(diskann::Metric::L2)
        .with_dimension(128)
        .with_max_points(1000)
        .is_dynamic_index(true)
        .is_enable_tags(true)
        .is_use_lsh(true) // Enable LSH
        .with_num_hash_tables(num_hash_tables)
        .with_num_hashes_per_table(num_hashes_per_table)
        .build();

    // Step 2: Create an Index with the LSH-enabled config
    std::shared_ptr<diskann::AbstractDataStore<float>> data_store = nullptr; // Mock or real implementation
    std::unique_ptr<diskann::AbstractGraphStore> graph_store = nullptr;      // Mock or real implementation

    diskann::Index<float, uint32_t, uint32_t> index(index_config, data_store, std::move(graph_store), nullptr);

    // Step 3: Verify LSH buckets are initialized correctly using public methods
    ASSERT_TRUE(index.is_lsh_enabled()); // Ensure LSH is enabled
    ASSERT_EQ(index.get_lsh_bucket_count(), num_hash_tables); // Check number of hash tables

    for (size_t i = 0; i < num_hash_tables; ++i) {
        ASSERT_GE(index.get_lsh_table_capacity(i), num_hashes_per_table); // Check capacity of each table
    }
}

TEST(IndexConfigTest, NoLSHInitialization) {
    // Step 1: Create an IndexConfig with LSH disabled
    diskann::IndexConfig index_config = diskann::IndexConfigBuilder()
        .with_metric(diskann::Metric::L2)
        .with_dimension(128)
        .with_max_points(1000)
        .is_dynamic_index(true)
        .is_enable_tags(true)
        .is_use_lsh(false) // Disable LSH
        .build();

    // Step 2: Create an Index with the LSH-disabled config
    std::shared_ptr<diskann::AbstractDataStore<float>> data_store = nullptr; // Mock or real implementation
    std::unique_ptr<diskann::AbstractGraphStore> graph_store = nullptr;      // Mock or real implementation

    diskann::Index<float, uint32_t, uint32_t> index(index_config, data_store, std::move(graph_store), nullptr);

    // Step 3: Verify LSH is disabled
    EXPECT_FALSE(index.is_lsh_enabled()); // Ensure LSH is disabled

    // Step 4: Verify that there are no LSH tables
    if (index.get_lsh_bucket_count() > 0) {
        for (size_t i = 0; i < index.get_lsh_bucket_count(); ++i) {
            EXPECT_EQ(index.get_lsh_table_capacity(i), 0);
        }
    } else {
        SUCCEED() << "No LSH buckets created as expected";
    }
}