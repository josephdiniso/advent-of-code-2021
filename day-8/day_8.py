#!/usr/bin/env python3
from typing import List


def contained_in(sub_string: str, super_string: str) -> bool:
    """
    Checks if the letters in ``sub_string`` are entirely in
    ``super_string``
    """
    for letter in sub_string:
        if letter not in super_string:
            return False
    return True


def find_match(signals: List[str], already_used: List[str], sub_string: str, size: int) -> str:
    for signal in signals:
        if signal not in already_used:
            if len(signal) == size:
                if contained_in(sub_string, signal):
                    return signal
    return None


def main():
    lefts = []
    rights = []
    with open("day_8.txt", "r") as f:
        for line in f.readlines():
            split_line = line.strip().split("|")
            lefts.append(split_line[0].strip().split(" "))
            rights.append(split_line[1].strip().split(" "))
    sum_val = 0
    for i in range(len(lefts)):
        nums = [None for i in range(10)]
        already_used = []
        for signal in lefts[i]:
            add_str = True
            if len(signal) == 2:
                nums[1] = "".join(sorted(signal))
            elif len(signal) == 4:
                nums[4] = "".join(sorted(signal))
            elif len(signal) == 3:
                nums[7] = "".join(sorted(signal))
            elif len(signal) == 7:
                nums[8] = "".join(sorted(signal))
            else:
                add_str = False
            if add_str:
                already_used.append(signal)
        out = find_match(lefts[i], already_used, nums[7], 5)
        nums[3] = "".join(sorted(out))
        already_used.append(out)
        out = find_match(lefts[i], already_used, nums[3], 6)
        nums[9] = "".join(sorted(out))
        already_used.append(out)
        out = find_match(lefts[i], already_used, nums[7], 6)
        nums[0] = "".join(sorted(out))
        already_used.append(out)

        for signal in lefts[i]:
            if signal not in already_used and len(signal) == 6:
                nums[6] = "".join(sorted(signal))
                already_used.append(signal)
                break
        for signal in lefts[i]:
            if len(signal) == 5 and contained_in(signal, nums[6]):
                nums[5] = "".join(sorted(signal))
                already_used.append(signal)
                break
        for signal in lefts[i]:
            if signal not in already_used and len(signal) == 5:
                nums[2] = "".join(sorted(signal))
        out_val = ""
        for signal in rights[i]:
            out_val += str(nums.index("".join(sorted(signal))))
        sum_val += int(out_val)
    print(sum_val)

if __name__ == "__main__":
    main()
