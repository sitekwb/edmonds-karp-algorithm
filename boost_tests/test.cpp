#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MAIN  // in only one cpp file
#include <boost/test/unit_test.hpp>
#include <Edge.h>

BOOST_AUTO_TEST_SUITE( edgeSuite )

    BOOST_AUTO_TEST_CASE( edgeConstructor )
    {
        const double negativeDouble = -5.8;
        const double positiveDouble = 11;

        BOOST_CHECK_THROW(auto edge1 = Edge(negativeDouble), std::out_of_range);
        BOOST_CHECK_NO_THROW(auto edge2 = Edge(0));
        BOOST_CHECK_NO_THROW(auto edge3 = Edge(positiveDouble));

        auto edge4 = Edge(0);
        BOOST_CHECK_EQUAL(edge4.getReverseEdge(), nullptr);
    }

    BOOST_AUTO_TEST_CASE( edgeCapacityGetterSetter )
    {
        const double positiveDouble = 23;
        const double positiveDouble2 = 11;
        auto edge = Edge(positiveDouble);
        BOOST_CHECK_EQUAL(edge.getCapacity(), positiveDouble);

        BOOST_TEST_CHECKPOINT("Will set capacity to positive double!");
        BOOST_CHECK_NO_THROW(edge.setCapacity(positiveDouble2));

        BOOST_TEST_CHECKPOINT("Will set capacity to positive double!");
        BOOST_CHECK_EQUAL(edge.getCapacity(), positiveDouble2);
    }







BOOST_AUTO_TEST_SUITE_END()