#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include "../../../src/ds/matrix.hpp"

#define ROWS 5
#define COLS 7
#define DEF  13


TEST_CASE("matrices can be created") {
    SECTION("matrix can be initialized") {
        Matrix<int> mat_A(ROWS, COLS);
        REQUIRE(mat_A.rows == ROWS);
        REQUIRE(mat_A.cols == COLS);
    }

    SECTION("default matrix has the right values") {
        Matrix<int> mat_B(ROWS, COLS, DEF);

        // Check dimensions.
        REQUIRE(mat_B.rows == ROWS);
        REQUIRE(mat_B.cols == COLS);

        // Check elements.
        for (size_t r = 0; r < ROWS; ++r) 
            for (size_t c = 0; c < COLS; ++c)
                REQUIRE(mat_B(r, c) == DEF);
    }

    SECTION("copy constructor initializes the right values") {
        // Create a non-uniform matrix.
        Matrix<int> mat_C(ROWS, COLS);
        for (size_t r = 0; r < ROWS; ++r)
            for (size_t c = 0; c < COLS; ++c)
                mat_C(r, c) = r * COLS + c;
    
        // Copy matrix.
        Matrix<int> mat_C_prime(mat_C);

        // Check dimensions.
        REQUIRE(mat_C_prime.rows == ROWS);
        REQUIRE(mat_C_prime.cols == COLS);

        // Check if the value of these two matrices are the same.
        for (size_t r = 0; r < ROWS; ++r) 
            for (size_t c = 0; c < COLS; ++c) 
                REQUIRE(mat_C(r, c) == r * COLS + c);
    }
}

TEST_CASE("matrices are assigned properly") {
    SECTION("default matrix") {
        Matrix<int> mat_A = Matrix<int>(ROWS, COLS, DEF);
        
        // Check dimensions.
        REQUIRE(mat_A.rows == ROWS);
        REQUIRE(mat_A.cols == COLS);

        // Check elements.
        for (size_t r = 0; r < ROWS; ++r) 
            for (size_t c = 0; c < COLS; ++c)
                REQUIRE(mat_A(r, c) == DEF);
    }

    SECTION("non-uniform matrix") {
        // Create a non-uniform matrix.
        Matrix<int> mat_B(ROWS, COLS);
        for (size_t r = 0; r < ROWS; ++r)
            for (size_t c = 0; c < COLS; ++c)
                mat_B(r, c) = r * COLS + c;
    
        // Copy matrix.
        Matrix<int> mat_B_prime(mat_B);

        // Check dimensions.
        REQUIRE(mat_B_prime.rows == ROWS);
        REQUIRE(mat_B_prime.cols == COLS);

        // Check if the value of these two matrices are the same.
        for (size_t r = 0; r < ROWS; ++r) 
            for (size_t c = 0; c < COLS; ++c) 
                REQUIRE(mat_B_prime(r, c) == r * COLS + c);
    }

    SECTION("assigning a matrix of different dimension") {
        Matrix<int> mat_C(ROWS, COLS, DEF);
        Matrix<int> mat_D(COLS, ROWS, DEF);

        REQUIRE_THROWS(mat_D = mat_C);
    }
}

TEST_CASE("matrix elements are assigned and retrieved correctly") {
    SECTION("out-of-bounds assignment/retrieval") {
        Matrix<int> mat_A(ROWS, COLS, DEF);
        // "Smaller" row (signed -> unsigned conversion).
        REQUIRE_THROWS(mat_A(-1, 0));
        // Larger row.
        REQUIRE_THROWS(mat_A(ROWS, 0));
        // "Smaller" column.
        REQUIRE_THROWS(mat_A(0, -1));
        // Larger column.
        REQUIRE_THROWS(mat_A(0, COLS));
    }
}

TEST_CASE("matrix equality works") {
    SECTION("default matrix") {
        Matrix<int> mat_A = Matrix<int>(ROWS, COLS, DEF);
        Matrix<int> mat_B = Matrix<int>(ROWS, COLS, DEF);
        
        REQUIRE(mat_A == mat_B);
    }

    SECTION("non-uniform matrix") {
        // Create a non-uniform matrix.
        Matrix<int> mat_C(ROWS, COLS);
        for (size_t r = 0; r < ROWS; ++r)
            for (size_t c = 0; c < COLS; ++c)
                mat_C(r, c) = r * COLS + c;
    
        // Copy matrix.
        Matrix<int> mat_C_prime(mat_C);

        REQUIRE(mat_C == mat_C_prime);
    }

    SECTION("matrices of different dimensions") {
        Matrix<int> mat_D(ROWS, COLS);
        Matrix<int> mat_E(COLS, ROWS);

        REQUIRE_FALSE(mat_D == mat_E);
    }

    SECTION("matrices with different values") {
        Matrix<int> mat_F(ROWS, COLS, DEF);
        Matrix<int> mat_G(ROWS, COLS, DEF + 1);

        REQUIRE_FALSE(mat_F == mat_G);
    }
}

