#include <gtest/gtest.h>

#include "blockstore/implementations/inmemory/InMemoryBlockStore.h"
#include "blockstore/implementations/inmemory/InMemoryBlock.h"
#include "blobstore/implementations/onblocks/BlobStoreOnBlocks.h"
#include "blobstore/implementations/onblocks/impl/DataNode.h"
#include "blobstore/implementations/onblocks/impl/DataLeafNode.h"
#include "blobstore/implementations/onblocks/impl/DataInnerNode.h"

using ::testing::Test;
using std::unique_ptr;
using std::make_unique;
using std::string;

using blockstore::BlockStore;
using blockstore::inmemory::InMemoryBlockStore;
using namespace blobstore;
using namespace blobstore::onblocks;

class DataNodeTest: public Test {
public:
  unique_ptr<BlockStore> blockStore = make_unique<InMemoryBlockStore>();
};

#define EXPECT_IS_PTR_TYPE(Type, ptr) EXPECT_NE(nullptr, dynamic_cast<Type*>(ptr)) << "Given pointer cannot be cast to the given type"

TEST_F(DataNodeTest, CreateLeafNodeCreatesLeafNode) {
  auto block = blockStore->create(BlobStoreOnBlocks::BLOCKSIZE);
  auto node = DataNode::createNewLeafNode(std::move(block.block));
  EXPECT_IS_PTR_TYPE(DataLeafNode, node.get());
}

TEST_F(DataNodeTest, CreateInnerNodeCreatesInnerNode) {
  auto block = blockStore->create(BlobStoreOnBlocks::BLOCKSIZE);
  auto node = DataNode::createNewInnerNode(std::move(block.block));
  EXPECT_IS_PTR_TYPE(DataInnerNode, node.get());
}

TEST_F(DataNodeTest, LeafNodeIsRecognizedAfterStoreAndLoad) {
  auto block = blockStore->create(BlobStoreOnBlocks::BLOCKSIZE);
  Key key = block.key;
  {
    DataNode::createNewLeafNode(std::move(block.block));
  }

  auto loaded_node = DataNode::load(blockStore->load(key));

  EXPECT_IS_PTR_TYPE(DataLeafNode, loaded_node.get());
}

TEST_F(DataNodeTest, InnerNodeIsRecognizedAfterStoreAndLoad) {
  auto block = blockStore->create(BlobStoreOnBlocks::BLOCKSIZE);
  Key key = block.key;
  {
    DataNode::createNewInnerNode(std::move(block.block));
  }

  auto loaded_node = DataNode::load(blockStore->load(key));

  EXPECT_IS_PTR_TYPE(DataInnerNode, loaded_node.get());
}

TEST_F(DataNodeTest, DataNodeCrashesOnLoadIfMagicNumberIsWrong) {
  auto block = blockStore->create(BlobStoreOnBlocks::BLOCKSIZE);
  Key key = block.key;
  {
    DataNodeView view(std::move(block.block));
    *view.MagicNumber() = 0xFF; // this is an invalid magic number
  }

  auto loaded_block = blockStore->load(key);
  EXPECT_ANY_THROW(
    DataNode::load(std::move(loaded_block))
  );
}