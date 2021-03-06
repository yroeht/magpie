#ifndef COLORS_HH
# define COLORS_HH

# include <ostream>
# include <string>

namespace Format
{
  static const char* DEFAULT = "\033[0m";
  static const char* CLEAR = "\033[J";             // tput ed
  static const char* CLEAR_LINE = "\033[A\033[K";  // tput cuui + el

  /*
  ** 88/256 Colors: http://misc.flogisoft.com/bash/tip_colors_and_formatting
  */
  enum Code
    {
      WHITE = 15,   YELLOW  = 227,
      RED   = 196,  ORANGE  = 208,
      BLUE  = 27,   GREEN   = 76
    };

  std::ostream& operator<<(std::ostream& os, const Code color);
}

#endif /* COLORS_HH */
