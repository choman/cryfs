project (blockstore-test)

set(SOURCES
    utils/BlockStoreUtilsTest.cpp
    interface/helpers/BlockStoreWithRandomKeysTest.cpp
    interface/BlockStoreTest.cpp
    interface/BlockTest.cpp
    implementations/testfake/TestFakeBlockStoreTest.cpp
    implementations/inmemory/InMemoryBlockStoreTest.cpp
    implementations/parallelaccess/ParallelAccessBlockStoreTest.cpp
    implementations/compressing/CompressingBlockStoreTest.cpp
    implementations/compressing/compressors/testutils/CompressorTest.cpp
    implementations/encrypted/EncryptedBlockStoreTest_Specific.cpp
    implementations/encrypted/EncryptedBlockStoreTest_Generic.cpp
    implementations/ondisk/OnDiskBlockStoreTest.cpp
    implementations/ondisk/OnDiskBlockTest/OnDiskBlockCreateTest.cpp
    implementations/ondisk/OnDiskBlockTest/OnDiskBlockFlushTest.cpp
    implementations/ondisk/OnDiskBlockTest/OnDiskBlockLoadTest.cpp
    implementations/caching/CachingBlockStoreTest.cpp
    implementations/caching/cache/QueueMapTest_Values.cpp
    implementations/caching/cache/testutils/MinimalKeyType.cpp
    implementations/caching/cache/testutils/CopyableMovableValueType.cpp
    implementations/caching/cache/testutils/MinimalValueType.cpp
    implementations/caching/cache/testutils/QueueMapTest.cpp
    implementations/caching/cache/testutils/CacheTest.cpp
    implementations/caching/cache/QueueMapTest_Size.cpp
    implementations/caching/cache/CacheTest_MoveConstructor.cpp
    implementations/caching/cache/CacheTest_PushAndPop.cpp
    implementations/caching/cache/QueueMapTest_MoveConstructor.cpp
    implementations/caching/cache/QueueMapTest_MemoryLeak.cpp
    implementations/caching/cache/CacheTest_RaceCondition.cpp
    implementations/caching/cache/PeriodicTaskTest.cpp
    implementations/caching/cache/QueueMapTest_Peek.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} googletest blockstore)
add_test(${PROJECT_NAME} ${PROJECT_NAME})

target_enable_style_warnings(${PROJECT_NAME})
target_activate_cpp14(${PROJECT_NAME})