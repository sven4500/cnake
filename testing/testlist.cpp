#include <gtest/gtest.h>
#include <list.h>

/* node_create tests */

TEST(NodeCreate, ReturnsNode)
{
    auto const node = node_create(0, 0);
    ASSERT_NE(node, nullptr);
}

TEST(NodeCreate, NextNull)
{
    auto const node = node_create(0, 0);
    ASSERT_EQ(node->next, nullptr);
}

TEST(NodeCreate, CorrectData)
{
    auto const node = node_create(-8, 7);
    ASSERT_EQ(node->x, -8);
    ASSERT_EQ(node->y, 7);
}

/* node_destroy tests */

TEST(NodeDestroy, DoesntCrashIfNull)
{
    node_destroy(nullptr);
}

TEST(NodeDestroy, DoesntCrashIfNotNull)
{
    auto const node = node_create(0, 0);
    node_destroy(node);
}

/* node_push_back tests */

TEST(NodePushBack, ReturnsNullIfRootNull)
{
    auto const node = node_push_back(nullptr, 0, 0);
    ASSERT_EQ(node, nullptr);
}

TEST(NodePushBack, CorrectData)
{
    auto const root = node_create(0, 0);
    auto const node = node_push_back(root, 4, -1);
    ASSERT_EQ(node->x, 4);
    ASSERT_EQ(node->y, -1);
}

TEST(NodePushBack, NextChangedIfSizeEqualsOne)
{
    auto const root = node_create(0, 0);
    auto const node = node_push_back(root, 0, 0);
    ASSERT_EQ(root->next, node);
}

TEST(NodePushBack, NextUnchangedIfSizeGreaterOne)
{
    auto const root = node_create(0, 0);
    auto const node1 = node_push_back(root, 0, 0);
    auto const node2 = node_push_back(root, 0, 0);
    ASSERT_EQ(root->next, node1);
}

/* node_push_front tests */

TEST(NodePushFront, ReturnsNullIfRootNull)
{
    auto const node = node_push_front(nullptr, 0, 0);
    ASSERT_EQ(node, nullptr);
}

TEST(NodePushFront, NewRoot)
{
    auto const root = node_create(0, 0);
    auto const node = node_push_front(root, 0, 0);
    ASSERT_EQ(node->next, root);
}

TEST(NodePushFront, CorrectData)
{
    auto const root = node_create(0, 0);
    auto const node = node_push_front(root, -3, 9);
    ASSERT_EQ(node->x, -3);
    ASSERT_EQ(node->y, 9);
}

/* node_count tests */

TEST(NodeCount, DoesntCrashIfNull)
{
    node_count(nullptr);
}

TEST(NodeCount, NullCountsZero)
{
    ASSERT_EQ(node_count(nullptr), 0);
}

TEST(NodeCount, RootCountsOne)
{
    auto const root = node_create(0, 0);
    ASSERT_EQ(node_count(root), 1);
}

TEST(NodeCount, PushBackCountsTwo)
{
    auto const root = node_create(0, 0);
    node_push_back(root, 0, 0);
    ASSERT_EQ(node_count(root), 2);
}

TEST(NodeCount, PushFrontCountsTwo)
{
    auto const root = node_create(0, 0);
    auto const node = node_push_front(root, 0, 0);
    ASSERT_EQ(node_count(node), 2);
}
