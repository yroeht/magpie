#include <cube.hh>
#include <output.hh>

#include <algorithm>
#include <assert.h>
#include <ostream>

Cube::Cube()
  : top     (3, std::vector<Color> (3, CUB_WHITE))
  , bottom  (3, std::vector<Color> (3, CUB_YELLOW))
  , left    (3, std::vector<Color> (3, CUB_BLUE))
  , right   (3, std::vector<Color> (3, CUB_GREEN))
  , front   (3, std::vector<Color> (3, CUB_ORANGE))
  , back    (3, std::vector<Color> (3, CUB_RED))
{}

Cube::Cube(const Cube& other)
  : top     (other.top)
  , bottom  (other.bottom)
  , left    (other.left)
  , right   (other.right)
  , front   (other.front)
  , back    (other.back)
{}

void
Cube::show_face(std::ostream& os, Side s)
{
  switch (s)
    {
    case TOP:       os << top;      break;
    case BOTTOM:    os << bottom;   break;
    case LEFT:      os << left;     break;
    case RIGHT:     os << right;    break;
    case FRONT:     os << front;    break;
    case BACK:      os << back;     break;
    }
}

void
Cube::rotate(Sequence s)
{
  for (auto m : s)
    this->rotate(m);
}

void
Cube::rotate(Move m)
{
#define RotateFace(face)        \
  do {                          \
      Color swap = face[0][1];  \
      face[0][1] = face[1][0];  \
      face[1][0] = face[2][1];  \
      face[2][1] = face[1][2];  \
      face[1][2] = swap;        \
  } while (0);                  \
  do {                          \
      Color swap = face[0][0];  \
      face[0][0] = face[2][0];  \
      face[2][0] = face[2][2];  \
      face[2][2] = face[0][2];  \
      face[0][2] = swap;        \
  } while (0)

  switch (m)
    {
      case ROT_UP:
        {
          /* The Slice */
          std::vector<Color> bar_swp;
          bar_swp = front[0];
          front[0] = right[0];
          right[0] = back[2]; std::reverse(right[0].begin(), right[0].end());
          back[2] = left[0];  std::reverse(back[2].begin(), back[2].end());
          left[0] = bar_swp;

          /* The Face */
          RotateFace(top);
        }
      break;

      case ROT_DOWN:
        {
          Color swp;

          /* The Slice */

          /* Corners */
          swp = front[2][0];
          front[2][0] = left[2][0];
          left[2][0] = back[0][2];
          back[0][2] = right[2][0];
          right[2][0] = swp;

          swp = front[2][2];
          front[2][2] = left[2][2];
          left[2][2] = back[0][0];
          back[0][0] = right[2][2];
          right[2][2] = swp;

          /* Edges */
          swp = front[2][1];
          front[2][1] = left[2][1];
          left[2][1] = back[0][1];
          back[0][1] = right[2][1];
          right[2][1] = swp;

          /* The Face */
          RotateFace(bottom);
        }
      break;

      case ROT_LEFT:
        {
          Color swp;

          /* The Slice */

          /* Corners */
          swp = front[0][0];
          front[0][0] = top[0][0];
          top[0][0] = back[0][0];
          back[0][0] = bottom[0][0];
          bottom[0][0] = swp;

          swp = front[2][0];
          front[2][0] = top[2][0];
          top[2][0] = back[2][0];
          back[2][0] = bottom[2][0];
          bottom[2][0] = swp;

          /* Edges */
          swp = front[1][0];
          front[1][0] = top[1][0];
          top[1][0] = back[1][0];
          back[1][0] = bottom[1][0];
          bottom[1][0] = swp;

          /* The Face */
          RotateFace(left);
        }
      break;

      case ROT_RIGHT:
        {
          Color swp;

          /* The Slice */

          /* Corners */
          swp = top[0][2];
          top[0][2] = front[0][2];
          front[0][2] = bottom[0][2];
          bottom[0][2] = back[0][2];
          back[0][2] = swp;

          swp = top[2][2];
          top[2][2] = front[2][2];
          front[2][2] = bottom[2][2];
          bottom[2][2] = back[2][2];
          back[2][2] = swp;

          /* Edges */
          swp = top[1][2];
          top[1][2] = front[1][2];
          front[1][2] = bottom[1][2];
          bottom[1][2] = back[1][2];
          back[1][2] = swp;

          /* The Face */
          RotateFace(right);
        }
      break;

      case ROT_FRONT:
        {
          Color swp;

          /* The Slice */

          /* Corners */
          swp = top[2][2];
          top[2][2] = left[0][2];
          left[0][2] = bottom[0][0];
          bottom[0][0] = right[2][0];
          right[2][0] = swp;

          swp = top[2][0];
          top[2][0] = left[2][2];
          left[2][2] = bottom[0][2];
          bottom[0][2] = right[0][0];
          right[0][0] = swp;

          /* Edges */
          swp = top[2][1];
          top[2][1] = left[1][2];
          left[1][2] = bottom[0][1];
          bottom[0][1] = right[1][0];
          right[1][0] = swp;

          /* The Face */
          RotateFace(front);
        }
      break;
      case ROT_BACK:
        {
          Color swp;

          /* The Slice */

          /* Corners */
          swp = top[0][0];
          top[0][0] = right[0][2];
          right[0][2] = bottom[2][2];
          bottom[2][2] = left[2][0];
          left[2][0] = swp;

          swp = top[0][2];
          top[0][2] = right[2][2];
          right[2][2] = bottom[2][0];
          bottom[2][0] = left[0][0];
          left[0][0] = swp;

          /* Edges */
          swp = top[0][1];
          top[0][1] = right[1][2];
          right[1][2] = bottom[2][1];
          bottom[2][1] = left[1][0];
          left[1][0] = swp;

          /* The Face */
          RotateFace(back);
        }
      break;

      case ROT_UP_I:
        {
          rotate(ROT_UP);
          rotate(ROT_UP);
          rotate(ROT_UP);
        };
      break;

      case ROT_DOWN_I:
        {
          rotate(ROT_DOWN);
          rotate(ROT_DOWN);
          rotate(ROT_DOWN);
        };
      break;

      case ROT_LEFT_I:
        {
          rotate(ROT_LEFT);
          rotate(ROT_LEFT);
          rotate(ROT_LEFT);
        };
      break;

      case ROT_RIGHT_I:
        {
          rotate(ROT_RIGHT);
          rotate(ROT_RIGHT);
          rotate(ROT_RIGHT);
        };
      break;

      case ROT_FRONT_I:
        {
          rotate(ROT_FRONT);
          rotate(ROT_FRONT);
          rotate(ROT_FRONT);
        };
      break;

      case ROT_BACK_I:
        {
          rotate(ROT_BACK);
          rotate(ROT_BACK);
          rotate(ROT_BACK);
        };
      break;
    }
}
