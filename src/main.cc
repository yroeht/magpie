#include <breeder.hh>
#include <cube.hh>
#include <fitness.hh>
#include <format.hh>
#include <output.hh>
#include <scrambler.hh>

#include <iostream>
#include <chrono>
#include <thread>

int main()
{
  unsigned scramble_length = 10;
  unsigned solution_length = 10;
  do {
      std::cout << Format::CLEAR;
      Cube c;

      /* Scramble */
        {
          auto scramble = Scrambler::scramble(scramble_length);
          scramble = Scrambler::reduce(scramble);
          std::cout << std::endl << "Scramble: " << scramble;
          std::cout << std::endl;

          c.rotate(scramble);

          std::cout << "** Applying scramble **" << std::endl
            << c << std::endl
            << "Fitness: " << Fitness::evaluate(*new Sequence, c)
            << std::endl << std::endl;
        }

      /* Solve */
      Sequence best_move;
        {
          auto generator = [&]() -> Sequence
            { return Scrambler::scramble(solution_length); };

          auto scorer = [c](const Sequence s) -> unsigned
            { return Fitness::evaluate(s, c); };

          auto printer = [&](const Sequence best,
                             const unsigned score,
                             const unsigned generation) -> void
            {
              std::cout << Format::CLEAR_LINE
                        << "Generation " << generation << ", best=" << best
                        << " score=" << score << std::endl;
            };

          PrintableBreeder<Sequence, unsigned> b(generator, scorer,
                                                 200000, 1.0);

          best_move = b.pick(300, 48, printer);

          std::cout << "best move: " << best_move << std::endl;
        }

      /* Show */
        {
          c.rotate(best_move);
          std::cout << "** Applying best sequence **" << std::endl
            << c << std::endl
            << "Fitness: " << Fitness::evaluate(*new Sequence, c) << std::endl
            << std::endl << std::endl;
        }
  } while (false);
}

