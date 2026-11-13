#!/usr/bin/env bash

test()
{
	local s="./computor \"$1\""
	echo "$s"
	bash -c "$s"
	echo "-------------"
}

test "5 * X^0 + 4 * X^1 - 9.3 * X^2 = 1 * X^0"

test "5 * X^0 + 4 * X^1 = 4 * X^0"

test "8 * X^0 - 6 * X^1 + 0 * X^2 - 5.6 * X^3 = 3 * X^0"

test "6 * X^0 = 6 * X^0"

test "10 * X^0 = 15 * X^0"

test "1 * X^0 + 2 * X^1 + 5 * X^2 = 0"