#!/usr/bin/env python

from collections import namedtuple
from subprocess import (Popen, PIPE)
from sys import exit


Test = namedtuple('Test', ['binary', 'input', 'output'])


def runTest(test):
    binary, input, output = test
    p = Popen(binary, stdin=PIPE, stdout=PIPE, stderr=PIPE)
    sout, serr = p.communicate(input=input)
    return sout.strip() == output.strip() and serr == b''


tests = [
    # Matching Gloves
    Test('./gloves', b'5\nbcd\nerty\nytre\nopipo\ndcb', b'2'),
    Test('./gloves', b'3\nabcde\nedcba\nabcde', b'-1'),
    Test('./gloves', b'3\nioi\nertre\nghhg', b'0'),
    # Conference Room Scheduler
    Test('./rooms', b'3\n1-1-4\n1-2', b'Y\n2 3')
]


if __name__ == '__main__':
    results = list(map(runTest, tests))
    if all(results):
        print('All tests passed!')
        exit(0)

    for test, res in zip(tests, results):
        if not res:
            print('{} failed!'.format(test))
    exit(1)
