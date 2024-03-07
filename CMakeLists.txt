cmake_minimum_required(VERSION 3.22)
project(Program_5_code)

set(CMAKE_CXX_STANDARD 14)

add_executable(Program_5_code main.cpp Bank.cpp Bank.h Account.cpp Account.h BSTree.cpp BSTree.h Transaction.cpp Transaction.h Deposit.cpp Deposit.h Withdraw.cpp Withdraw.h Transfer.cpp Transfer.h Client.cpp Client.h)
