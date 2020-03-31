#define BOOST_TEST_MODULE MP test
#include <boost/test/included/unit_test.hpp>

#include "mp.hpp"
using namespace MP;

BOOST_AUTO_TEST_CASE(Conversions) {
  //Equalities with small numbers
  BOOST_TEST(long(Integer(0)) == 0);
  BOOST_TEST(long(Integer(1)) == 1);
  BOOST_TEST(long(Integer(-1)) == -1);

  //Equalities with large numbers, positive and negative
  BOOST_TEST(long(Integer(3180737898301137215)) == 3180737898301137215);
  BOOST_TEST(long(Integer(-54783912)) == -54783912);

  //Equalities with using a different fragment size
  BOOST_TEST(long(BasicInteger<unsigned short>(1687456364462140721)) == 1687456364462140721);
  BOOST_TEST(long(BasicInteger<unsigned short>(-3946403960656731443)) == -3946403960656731443);

  BOOST_TEST(long(BasicInteger<unsigned int>(1212375737939285076)) == 1212375737939285076);
  BOOST_TEST(long(BasicInteger<unsigned int>(-9755677176384584)) == -9755677176384584);
}
