/* Headers to be tested */
#include "vector.h"
#include "matrix.h"

// Template: Operator << overload for std::ostream
// std::ostream& operator << ( std::ostream& os, T const& value ) {
// 	os << convertMyTypeToString( value );
// 	return os;
// }

// char * vector_to_str( Vector arg ) {
//     char * result;
//     result = new char[2 * arg.dimensions + 1];
//     for (int i=0; i<arg.dimensions; i++)
//         sprintf(result, "%f ", arg.value[i]);
//     return result;
// }

// char * matrix_to_str( Matrix arg ) {
//     char * result;
//     result = new char[arg.row * (2 * arg.col + 1) + 1];
//     for (int i=0; i<arg.row; i++) {
//         for (int j=0; j<arg.col; j++) {
//             sprintf(result, "%f ", arg.values[i][j]);
//         }
//         sprintf(result, "\n");
//     }

//     return result;
// }

// std::ostream& operator << ( std::ostream& os, Vector const& value ) {
// 	os << vector_to_str( value );
// 	return os;
// }

// std::ostream& operator << ( std::ostream& os, Matrix const& value ) {
// 	os << matrix_to_str( value );
// 	return os;
// }

#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"

TEST_CASE( "Vector", "[vector]" ) {
    SECTION( "Testing vector constructors" ) {
        SECTION( "Empty Vector Constructor" ) {
            Vector vector_null;
            REQUIRE( vector_null.value == nullptr );
            REQUIRE( vector_null.dimensions == 0 );
        }

        SECTION( "Zero Vector Constructor" ) {
            const int size_zero = 3;
            Vector vector_zero(size_zero);
            for (int i=0; i<size_zero; i++)
                REQUIRE( vector_zero.value[i] == 0 );
            REQUIRE( vector_zero.dimensions == size_zero );
        }
        
        SECTION( "Basic Vector Constructor" ) {
            float args[] = {1, 2, 3, 4};
            const int size = sizeof(args)/sizeof(float);
            Vector vector(size, args);
        
            REQUIRE( vector.dimensions == size );
            for (int i=0; i<size; i++)
                REQUIRE( vector.value[i] == args[i] );
        }

        SECTION( "Argument List Vector Construction" ) {
            Vector vector_arg1{1, 2, 3, 4, 5};
            Vector vector_arg2 = {1, 2, 3, 4, 5};

            REQUIRE( vector_arg1.dimensions == vector_arg2.dimensions);
            for (int i=0; i<vector_arg1.dimensions; i++)
                REQUIRE( vector_arg1.value[i] == vector_arg2.value[i] );
        }

        SECTION( "Assignment Overload " ) {
            float args[] = {1, 2, 3, 4};
            const int size = sizeof(args)/sizeof(float);
            Vector vector(size, args);
            Vector vector_null;

            vector_null = vector;
            for (int i=0; i<size; i++)
                REQUIRE( vector_null.value[i] == vector.value[i] );
            REQUIRE( vector_null.dimensions == vector.dimensions );
        }

        SECTION( "Copy Vector Constructor" ) {
            Vector vector_zero = Vector();
            REQUIRE( vector_zero.value == nullptr );
            REQUIRE( vector_zero.dimensions == 0 );
        }
    }

    SECTION( "Testing Basic Operations" ) {
        // float arg_1[] = {3, 4, 7};
        // float arg_2[] = {2, 5, 8};
        
        // int size_1 = sizeof(arg_1)/sizeof(float);
        // int size_2 = sizeof(arg_2)/sizeof(float);

        // Vector vector_1(size_1, arg_1);
        // Vector vector_2(size_2, arg_2);
        Vector vector_1 = {3, 4, 7};
        Vector vector_2 = {2, 5, 8};
        Vector vector_ans;

        SECTION( "Vector-Vector Addition" ) {
            vector_ans = vector_1 + vector_2;
            REQUIRE( vector_ans.dimensions == vector_1.dimensions );
            for (int i=0; i<vector_1.dimensions; i++)
                REQUIRE( vector_ans.value[i] == vector_1.value[i] + vector_2.value[i] );
        }
        
        SECTION( "Vector-Scalar Addition" ) {
            vector_ans = vector_1 + 5;
            REQUIRE( vector_ans.dimensions == vector_1.dimensions );
            for (int i=0; i<vector_1.dimensions; i++)
                REQUIRE( vector_ans.value[i] == vector_1.value[i] + 5 );
        }

        SECTION( "Vector-Vector Subtraction" ) {
            vector_ans = vector_1 - vector_2;
            REQUIRE( vector_ans.dimensions == vector_1.dimensions );
            for (int i=0; i<vector_1.dimensions; i++)
                REQUIRE( vector_ans.value[i] == vector_1.value[i] - vector_2.value[i] );
        }

        SECTION( "Vector-Scalar Subtraction" ) {
            vector_ans = vector_1 - 5;
            REQUIRE( vector_ans.dimensions == vector_1.dimensions );
            for (int i=0; i<vector_1.dimensions; i++)
                REQUIRE( vector_ans.value[i] == vector_1.value[i] - 5 );
        }

        SECTION( "Vector Negation" ) {
            vector_ans = -vector_1;
            REQUIRE( vector_ans.dimensions == vector_1.dimensions );
            for (int i=0; i<vector_1.dimensions; i++)
                REQUIRE( vector_ans.value[i] == -vector_1.value[i] );
        }

        SECTION( "Vector-Vector Multiplication" ) {
            float float_ans = vector_1 * vector_2;
            float product = 0;
            
            for (int i=0; i<vector_1.dimensions; i++)
                product += vector_1.value[i] * vector_2.value[i];

            REQUIRE( float_ans == product );
        }

        SECTION( "Vector-Scalar Multiplication" ) {
            vector_ans = vector_1 * 5;
            REQUIRE( vector_ans.dimensions == vector_1.dimensions );
            for (int i=0; i<vector_1.dimensions; i++)
                REQUIRE( vector_ans.value[i] == vector_1.value[i] * 5 );
        }

    }
}

TEST_CASE( "Matrix", "[matrix]" ) {
    SECTION( "Constructors" ) {
        SECTION( "Empty Matrix Constructor" ) {
            Matrix null_matrix;
            REQUIRE( null_matrix.values == nullptr );
            REQUIRE( null_matrix.row == 0 );
            REQUIRE( null_matrix.col == 0 );
        }

        SECTION( "Zero Matrix Constructor" ) {
            Matrix zero_matrix(3, 3, ZERO);
            REQUIRE( zero_matrix.row == 3 );
            REQUIRE( zero_matrix.col == 3 );
            for (int i=0; i<3; i++)
                for (int j=0; j<3; j++)
                    REQUIRE( zero_matrix.values[i][j] == 0 );
        }

        SECTION( "Identiry Matrix Constructor" ) {

        }

        SECTION( "Basic Matrix Construtor" ) {

        }

        SECTION( "Assignment Overload" ) {

        }

        SECTION( "Copy Matrix Constructor" ) {

        }


    }

    SECTION( "Basic Operations" ) {
        SECTION( "Matrix Addition" ) {

        }
        
        SECTION( "Matrix Subtraction" ) {

        }

        SECTION( "Matrix Multiplication" ) {

        }

        SECTION( "Matrix-Vector Multiplication" ) {

        }
    }
}