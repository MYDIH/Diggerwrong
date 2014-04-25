#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Model
#include <boost/test/unit_test.hpp>

#include "Board.hh"
#include "Square.hh"




BOOST_AUTO_TEST_CASE(board_out_of_range)
{
    Board m(8, 8, 0.2, 10);

    for(int i=0; i<8; i++)
    {
        for(int j=0; j<8; j++)
        {
            Normal *temp = new Normal(1);
            m.replaceSquare(i, j, temp);
            temp->release();
        }
    }

    Board testModel(m);

    BOOST_CHECK(testModel.move(-1, 0) == CONTINUE);
    BOOST_CHECK(m.move(-1, 0) == CONTINUE);
    BOOST_CHECK(m.move(-1, 0) == CONTINUE);
    BOOST_CHECK(m.move(-1, 0) == CONTINUE);
    BOOST_CHECK(m.move(-1, 0) == LOST);
}
