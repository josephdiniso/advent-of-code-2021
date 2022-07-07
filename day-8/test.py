import unittest

import day_8


class Testing(unittest.TestCase):
    def test_contains(self):
        self.assertTrue(day_8.contained_in("dab", "fbcad"))
        self.assertTrue(day_8.contained_in("fbcad", "cefabd"))
        self.assertFalse(day_8.contained_in("fbcad", "cagedb"))


def main():
    unittest.main()


if __name__ == "__main__":
    main()
