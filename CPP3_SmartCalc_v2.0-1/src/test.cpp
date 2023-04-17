// #include <gtest/gtest.h>

// #include "algorithm.h"

// //------------------LIST------------------
// TEST(algorithms, test1) {
//     Algorithm obj;
//     QString temp = obj.Sort_Facility("2+2*5/(6*3+(-3))");
//     double result = obj.Calculation(temp);
//     ASSERT_LE(result - 2.66667, 0.0001);
// }

// TEST(algorithms, test2) {
//     Algorithm obj;
//     QString temp = obj.Sort_Facility("c(50*s(50*t(50)))");
//     double result = obj.Calculation(temp);
//     ASSERT_LE(result - 0.407, 0.0001);
// }

// TEST(algorithms, test3) {
//     Algorithm obj;
//     QString temp = obj.Sort_Facility("6%3/a(50*q(4))*l(2.72)");
//     double result = obj.Calculation(temp);
//     ASSERT_LE(result - (6 % 3 / atan(50 * sqrt(4)) * log(2.72)), 0.0001);
// }

// TEST(algorithms, test4) {
//     Algorithm obj;
//     QString temp = obj.Sort_Facility("6%3/a(50*q(4))*l(2.72)*g(1000.5555)");
//     double result = obj.Calculation(temp);
//     ASSERT_LE(result - (6 % 3 / atan(50 * sqrt(4)) * log(2.72) *
//     log10(1000.5555)), 0.0001);
// }

// TEST(algorithms, test5) {
//     Algorithm obj;
//     QString temp = obj.Sort_Facility("6%3/a(50*q(4))*l(2.72)*g(1000.5555)");
//     double result = obj.Calculation(temp);
//     ASSERT_LE(result - (6 % 3 / atan(50 * sqrt(4)) * log(2.72) *
//     log10(1000.5555)), 0.0001);
// }

// int main(int argc, char **argv) {
//   ::testing::InitGoogleTest(&argc, argv);

//   return RUN_ALL_TESTS();
// }
