#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MAIN  // in only one cpp file
#include <boost/test/unit_test.hpp>
#include <Edge.h>
#include <Vertice.h>
#include <Generator.h>

using namespace std;

const int REPEAT_NUM = 50;
default_random_engine engine;
uniform_real_distribution distribution;
uniform_int_distribution int_distribution;


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

    BOOST_AUTO_TEST_CASE( edgeCapacityScaler1 )
    {
        const double positiveDouble = 23;
        auto edge = Edge(positiveDouble);
        BOOST_CHECK_EQUAL(edge.getCapacity(), positiveDouble);

        const double scale = 5;
        const double scaledDouble = positiveDouble / scale;

        BOOST_TEST_CHECKPOINT("Will scale capacity!");
        BOOST_CHECK_NO_THROW(edge.scaleCapacity(scale));

        BOOST_CHECK_EQUAL(edge.getCapacity(), scaledDouble);
    }

    BOOST_AUTO_TEST_CASE( edgeCapacityScaler2 )
    {
        const double positiveDouble = 23;
        auto edge = Edge(positiveDouble);

        const double scale1 = -2;
        const double scale2 = 0;

        BOOST_TEST_CHECKPOINT("Will scale capacity with less than 0!");
        BOOST_CHECK_THROW(edge.scaleCapacity(scale1), std::out_of_range);
        BOOST_TEST_CHECKPOINT("Will scale capacity with equal to 0!");
        BOOST_CHECK_THROW(edge.scaleCapacity(scale2), std::out_of_range);

    }

    BOOST_AUTO_TEST_CASE( edgeSetReverseEdge )
    {
        const double capacity1 = 12.5;
        const double capacity2 = 15;
        auto edge1 = make_shared<Edge>(capacity1);
        {
            auto edge2 = make_shared<Edge>(capacity2);
            BOOST_CHECK_NO_THROW(edge1->setReverseEdge(edge2));
            BOOST_TEST_CHECKPOINT("Will compare edges!");
            BOOST_TEST(edge1->getReverseEdge() == edge2);
        }
        BOOST_TEST_CHECKPOINT("Before checking shared ptr working!");
        BOOST_CHECK_EQUAL(edge1->getReverseEdge()->getCapacity(), capacity2);
    }

    BOOST_AUTO_TEST_CASE( edgeDestructor )
    {
        const double capacity1 = 12.5;
        const double capacity2 = 15;
        auto edge2 = make_shared<Edge>(capacity2);
        {
            auto edge1 = make_shared<Edge>(capacity1);
            BOOST_CHECK_NO_THROW(edge1->setReverseEdge(edge2));
            BOOST_TEST_CHECKPOINT("Before checking shared ptr working after setReverseEdge()!");
            BOOST_CHECK_EQUAL(edge2.use_count(), 2);
        }
        BOOST_TEST_CHECKPOINT("Before checking shared ptr working after destructor!");
        BOOST_CHECK_EQUAL(edge2.use_count(), 1);
    }

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE( verticeSuite )

    BOOST_AUTO_TEST_CASE( verticeConstructor )
    {
        const double negativeDouble = -5.8;
        const double positiveDouble = 11;

        BOOST_CHECK_THROW(auto vertice1 = Vertice(negativeDouble), std::out_of_range);
        BOOST_CHECK_NO_THROW(auto vertice2 = Vertice(0));
        BOOST_CHECK_NO_THROW(auto vertice3 = Vertice(positiveDouble));

        BOOST_TEST_CHECKPOINT("Before initial color and parent set check!");
        auto vertice4 = Vertice(0);
        BOOST_CHECK_EQUAL(vertice4.getColor(), WHITE);
        BOOST_CHECK_EQUAL(vertice4.getParentVertice(), Vertice::noParent());
    }

    BOOST_AUTO_TEST_CASE( verticeCapacityGetterSetter )
    {
        for(int i = 0; i < REPEAT_NUM; ++i) {
            const double positiveDouble = abs(distribution(engine));
            const double positiveDouble2 = abs(distribution(engine));
            const double positiveDouble3 = abs(distribution(engine));
            const double negativeDouble = -abs(distribution(engine));
            auto vertice = Vertice(positiveDouble);
            BOOST_CHECK_EQUAL(vertice.getCapacity(), positiveDouble);

            BOOST_TEST_CHECKPOINT("Will increment capacity by positive and negative double! i = " + i);
            BOOST_CHECK_NO_THROW(vertice.incrementCapacity(positiveDouble2));
            BOOST_CHECK_THROW(vertice.incrementCapacity(negativeDouble), std::out_of_range);

            BOOST_TEST_CHECKPOINT("Will reduce capacity by positive and negative double! i = " + i);
            BOOST_CHECK_NO_THROW(vertice.reduceCapacity(positiveDouble3));
            BOOST_CHECK_THROW(vertice.reduceCapacity(negativeDouble), std::out_of_range);

            BOOST_TEST_CHECKPOINT("Will check capacity by getter! i = " + i);
            BOOST_CHECK_EQUAL(vertice.getCapacity(), positiveDouble + positiveDouble2 - positiveDouble3);
        }
    }

    BOOST_AUTO_TEST_CASE( verticeCapacityScaler1 )
    {
        for(int i = 0; i < REPEAT_NUM; ++i) {
            const double positiveDouble = abs(distribution(engine));
            auto vertice = Vertice(positiveDouble);
            BOOST_CHECK_EQUAL(vertice.getCapacity(), positiveDouble);

            const double scale = abs(distribution(engine));
            const double scaledDouble = positiveDouble / scale;

            BOOST_TEST_CHECKPOINT("Will scale capacity!");
            BOOST_CHECK_NO_THROW(vertice.scaleCapacity(scale));

            BOOST_CHECK_EQUAL(vertice.getCapacity(), scaledDouble);
        }
    }

    BOOST_AUTO_TEST_CASE( verticeCapacityScaler2 )
    {
        for(int i = 0; i < REPEAT_NUM; ++i) {
            const double positiveDouble = abs(distribution(engine));
            auto vertice = Vertice(positiveDouble);

            const double scale1 = -abs(distribution(engine));
            const double scale2 = 0;

            BOOST_TEST_CHECKPOINT("Will scale capacity with less than 0!");
            BOOST_CHECK_THROW(vertice.scaleCapacity(scale1), std::out_of_range);
            BOOST_TEST_CHECKPOINT("Will scale capacity with equal to 0!");
            BOOST_CHECK_THROW(vertice.scaleCapacity(scale2), std::out_of_range);
        }
    }

    BOOST_AUTO_TEST_CASE( verticeColor )
    {
        for(int i = 0; i < REPEAT_NUM; ++i) {
            const double capacity1 = abs(distribution(engine));
            auto vertice1 = make_shared<Vertice>(capacity1);
            BOOST_CHECK_NO_THROW(vertice1->setColor(GREY));
            BOOST_CHECK_EQUAL(vertice1->getColor(), GREY);
        }
    }

    BOOST_AUTO_TEST_CASE( verticeParent )
    {
        for(int i = 0; i < REPEAT_NUM; ++i) {
            const double capacity1 = abs(distribution(engine));
            const int parent = abs(int_distribution(engine));
            auto vertice1 = make_shared<Vertice>(capacity1);
            BOOST_CHECK_NO_THROW(vertice1->setParentVertice(parent));
            BOOST_CHECK_EQUAL(vertice1->getParentVertice(), parent);
        }
    }

    BOOST_AUTO_TEST_CASE( verticeHasParent ) {
        for (int i = 0; i < REPEAT_NUM; ++i) {
            const double capacity1 = abs(distribution(engine));
            const double capacity2 = abs(distribution(engine));
            const int parent = abs(int_distribution(engine));
            auto vertice1 = make_shared<Vertice>(capacity1);
            auto vertice2 = make_shared<Vertice>(capacity2);
            BOOST_CHECK_NO_THROW(vertice2->setParentVertice(parent));
            BOOST_TEST(vertice2->hasParent());
            BOOST_TEST(!vertice1->hasParent());
        }
    }

    BOOST_AUTO_TEST_CASE( verticeCreateEdge ) {
        for (int i = 0; i < REPEAT_NUM; ++i) {
            const double capacity1 = abs(distribution(engine));
            const int verticeNumber = abs(int_distribution(engine));
            const double edgeCapacity = abs(distribution(engine));
            auto vertice = make_shared<Vertice>(capacity1);
            BOOST_CHECK_NO_THROW(vertice->createEdge(verticeNumber, edgeCapacity));
            BOOST_TEST(vertice->issetEdge(verticeNumber));
        }
    }

BOOST_AUTO_TEST_SUITE_END()