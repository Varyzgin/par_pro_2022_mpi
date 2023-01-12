// Copyright 2023 Varyzgin Dmitriy

#include <gtest/gtest.h>

#include "./mult_mat_hor_vert.h"

#include <gtest-mpi-listener.hpp>

TEST(Multiply, MultMatrix532) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int MonN = 15;  // 15, 25
    int NonK = 6;   // 6, 25
    int MonK = 10;  // 10, 25
    int n = 3;      // 3, 5
    std::vector<int> res = {80, 40, 77, 37, 67, 35, 51, 31, 44, 28};
    std::vector<int> A(MonN);
    std::vector<int> B(NonK);
    std::vector<int> Res(MonK, 0);

    A = {1, 7, 3, 2, 1, 9, 3, 2, 6, 4, 4, 1, 5, 1, 3};
    B = {3, 3, 8, 4, 7, 3};

    Res = multMatParallel(A, B, n);

    if (rank == 0) {
        EXPECT_EQ(Res, res);
    }
}
TEST(Multiply, MultMatrix555) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int MonN = 25;
    int NonK = 25;
    int MonK = 25;
    int n = 5;
    std::vector<int> res = {92, 71, 84, 87, 57, 122, 59, 140, 113, 52, 84, 62, 94, 102, 57, 83, 75, 88, 128, 81, 84, 54, 101, 116, 69};
    std::vector<int> A(MonN);
    std::vector<int> B(NonK);
    std::vector<int> Res(MonK, 0);

    A = {1, 7, 3, 1, 6, 2, 1, 9, 7, 3, 3, 2, 6,
         2, 5, 4, 4, 1, 4, 8, 5, 1, 3, 6, 4};
    B = {3, 3, 5, 8, 7, 8, 4, 6, 2, 3, 7, 3, 8,
         4, 1, 6, 1, 7, 5, 2, 1, 5, 1, 8, 4};
    Res = multMatParallel(A, B, n);

    if (rank == 0) {
        EXPECT_EQ(Res, res);
    }
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    MPI_Init(&argc, &argv);

    ::testing::AddGlobalTestEnvironment(new GTestMPIListener::MPIEnvironment);
    ::testing::TestEventListeners& listeners =
        ::testing::UnitTest::GetInstance()->listeners();

    listeners.Release(listeners.default_result_printer());
    listeners.Release(listeners.default_xml_generator());

    listeners.Append(new GTestMPIListener::MPIMinimalistPrinter);
    return RUN_ALL_TESTS();
}
