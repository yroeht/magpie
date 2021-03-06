#ifndef FITNESS_HH
# define FITNESS_HH

# include <cube.hh>
# include <types.hh>

namespace Fitness
{
  Score evaluate(const Sequence seq, const Cube& cu);
}

#endif /* FITNESS_HH */
