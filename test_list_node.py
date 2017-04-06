import unittest

import list_node
from _lib_list_node import lib, ffi


class ListNodeTestCase(unittest.TestCase):
    def test_creation_zero_elements(self):
        num_elements = 0
        root_node = lib.newList(num_elements)
        self.assertEqual(root_node.nextListItem, ffi.NULL)
        self.assertEqual(root_node.prevListItem, ffi.NULL)

    def test_creation_one_elements(self):
        num_elements = 1
        root_node = lib.newList(num_elements)
        self.assertEqual(root_node.prevListItem, ffi.NULL)
        self.assertEqual(root_node.nextListItem.nextListItem, ffi.NULL)
        self.assertEqual(root_node.nextListItem.prevListItem, root_node)

    def test_put_one_item(self):
        num_elements = 0
        root_node = lib.newList(num_elements)

        item = lib.createItem()
        lib.putItem(item, root_node)
        self.assertEqual(root_node.nextListItem, item)
        self.assertEqual(item.prevListItem, root_node)


if __name__ == "__main__":
    unittest.main()
