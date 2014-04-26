#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Model
#include <boost/test/unit_test.hpp>

#include "Board.hh"
#include "Square.hh"


void fill_board_normal(Board & b, unsigned value)
{
   const unsigned height = b.getHeight();
   const unsigned width  = b.getWidth();

   for(unsigned x=0; x<width; x++)
   {
      for(unsigned y=0; y<height; y++)
      {
	 Normal *temp = new Normal(value);
	 b.replaceSquare(x, y, temp);
	 temp->release();
      }
   }
}


BOOST_AUTO_TEST_CASE(Board_move_with_Normal_squares)
{
   /*
     . -- 1
     S -- initiale
     F -- finale

     Plateau "b" :
     | . | . | . | . | . |
     | . | . | . | . | . |
     | . | . | 3 | . | . |
     | . | 2 | . | . | 4 |
     | . | . | S | . | . |
     | . | . | . | . | . |
     | . | F | . | . | . |
     | . | . | . | . | . |

   */

   point p;

   Square *n2 = new Normal(2);
   Square *n3 = new Normal(3);
   Square *n4 = new Normal(4);

   Board b(5,8, 0.77, 100);

   fill_board_normal(b,1);

   b.replaceSquare(1, 3, n2);
   b.replaceSquare(2, 2, n3);
   b.replaceSquare(4, 3, n4);

   n2 -> release();
   n3 -> release();
   n4 -> release();



   Board t1(b);

   t1.move(-1, -1);
   t1.move(+1, 0);
   t1.move(+1, 0);
   t1.move(0, +1);

   t1.move(-1, 0);
   t1.move(-1, 0);
   t1.move(-1, 0);

   p = t1.getDigger();
   BOOST_CHECK( p.x == 1 and p.y == 6 );


   Board t2(b);

   t2.move(-1, 0);
   t2.move(-1, 0);
   t2.move(+1, -1);
   t2.move(0, -1);
   t2.move(0, -1);
   t2.move(+1, 0);
   t2.move(+1, 0);
   t2.move(0, +1);
   t2.move(0, +1);
   t2.move(0, +1);

   t2.move(-1, 0);
   t2.move(-1, 0);
   t2.move(0, 1);
   t2.move(-1, 0);
   t2.move(0, -1);

   p = t2.getDigger();
   BOOST_CHECK( p.x == 1 and p.y == 6 );


   Board t3(b);

   t3.move(-1, 1);
   t3.move(0, 1);

   p = t3.getDigger();
   BOOST_CHECK( p.x == 1 and p.y == 6 );
}


BOOST_AUTO_TEST_CASE(tiny_Board_move_out_of_range)
{
    Board b(1, 1, 0.66, 100);
    fill_board_normal(b, 1);

    BOOST_CHECK(b.move(+1, 0) == LOST);


    Board b2(3, 3, 0.66, 100);
    fill_board_normal(b2, 1);

    BOOST_CHECK(b2.move(0, -1) == CONTINUE);
    BOOST_CHECK(b2.move(0, -1) == LOST);


    Board b3(8, 11, 0.66, 100);
    fill_board_normal(b3, 1);

    BOOST_CHECK(b3.move(+1, 0) == CONTINUE);
    BOOST_CHECK(b3.move(+1, 0) == CONTINUE);
    BOOST_CHECK(b3.move(+1, 0) == CONTINUE);
    BOOST_CHECK(b3.move(+1, 0) == LOST);
}


BOOST_AUTO_TEST_CASE(big_Board_move_out_of_range)
{
    Board b(500, 888, 0.66, 1000);
    fill_board_normal(b, 1);

    for (unsigned x = 1; x <= 249; x++)
       BOOST_CHECK(b.move(+1, 0) == CONTINUE);

    BOOST_CHECK(b.move(+1, 0) == LOST);
}

