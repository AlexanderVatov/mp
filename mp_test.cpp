#define BOOST_TEST_MODULE MP
#include <boost/test/included/unit_test.hpp>

#include "mp.hpp"
using namespace MP;

#include <cstdint>
using std::uint8_t;
using std::uint16_t;
using std::uint32_t;

BOOST_AUTO_TEST_CASE(Conversions) {
  //Equalities with "special" numbers
  BOOST_TEST(long(Integer(0)) == 0);
  BOOST_TEST(long(Integer(1)) == 1);
  BOOST_TEST(long(Integer(-1)) == -1);

  //Equalities with large numbers, positive and negative
  BOOST_TEST(long(Integer(3180737898301137215)) == 3180737898301137215);
  BOOST_TEST(long(Integer(-54783912)) == -54783912);

  //Equalities with using a different fragment size
  BOOST_TEST(long(BasicInteger<uint16_t>(1687456364462140721l)) == 1687456364462140721l);
  BOOST_TEST(long(BasicInteger<uint16_t>(-3946403960656731443l)) == -3946403960656731443l);

  BOOST_TEST(long(BasicInteger<uint32_t>(1212375737939285076l)) == 1212375737939285076l);
  BOOST_TEST(long(BasicInteger<uint32_t>(-9755677176384584l)) == -9755677176384584l);
}

BOOST_AUTO_TEST_CASE(Sizes) {
  BOOST_TEST(BasicInteger<uint8_t>(0).size() == 0);
  BOOST_TEST(BasicInteger<uint8_t>(1).size() == 1);
  BOOST_TEST(BasicInteger<uint8_t>(255).size() == 1);
  BOOST_TEST(BasicInteger<uint8_t>(256).size() == 2);
}

BOOST_AUTO_TEST_CASE(Addition) {
  BOOST_TEST(long(Integer(0) + Integer(0))==0);
  BOOST_TEST(long(Integer(0) + Integer(1))==1);
  BOOST_TEST(long(BasicInteger<uint8_t>(255) + BasicInteger<uint8_t>(1))==256);
  BOOST_TEST(long(BasicInteger<uint8_t>(255) + BasicInteger<uint8_t>(255))==510);
  BOOST_TEST(long(Integer(1932353877895501793l) + Integer(4245370126020644564l))==6177724003916146357l);
}

BOOST_AUTO_TEST_CASE(Multiplication) {
  BOOST_TEST(long(Integer(0) * Integer(0)) == 0);
  BOOST_TEST(long(Integer(0) * Integer(1)) == 0);
  BOOST_TEST(long(Integer(1) * Integer(1)) == 1);
  BOOST_TEST(long(Integer(-1) * Integer(-1)) == 1);
  BOOST_TEST(long(Integer(1) * Integer(-1)) == -1);
  BOOST_TEST(long(Integer(1) * Integer(1000)) == 1000);
  BOOST_TEST(long(Integer(3) * Integer(100)) == 300);
  BOOST_TEST(long(BasicInteger<uint8_t>(21596494) * BasicInteger<uint8_t>(809197923)) == 17475838088881962l);

}
