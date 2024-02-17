#include <memory>
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <string>
#include <cassert>

template<
  typename CharT = char,
  typename Traits = std::char_traits<CharT>
> class Comment_counter {

public:

  using size_t = std::size_t;

private:

  enum class State {
    IN,            // Waiting for comments
    ROUND_N_STAR,  // Parsing (* comment *)
    FIGURE,        // Parsing {  comment  }
    SINGLE_STRING, // Parsing // comment 
    STR_LITERAL,   // Parsing 'string literal'
  } state_ = State::IN;
  
  bool failed_ = false;
  bool ended_  = false;

  size_t round_n_star_count_  = 0;
  size_t figure_count_        = 0;
  size_t single_string_count_ = 0;
  size_t str_literal_count_   = 0;

  static constexpr auto Eof = Traits::eof();
  typename Traits::int_type prev_sym_ = Eof;

public:

  /* Not implementing 'State' pattern since it implies 
   * using virtual functions - overhead, that can be avoided.
   */
  void parse(CharT sym) {

    if (ended_) {
      return;
    }

    auto cur_sym = (typename Traits::int_type) sym;
    if (cur_sym == Eof) {

      failed_ = (state_ == State::IN);
      ended_ = true;

      prev_sym_ = cur_sym;
      return;
    }

    switch(state_) {

      case State::IN: {

        if (prev_sym_ == '(' && cur_sym == '*') {

          state_ = State::ROUND_N_STAR;

        } else if (cur_sym == '{') {
        
          state_ = State::FIGURE;

        } else if (prev_sym_ == '/' && cur_sym == '/') {

          state_ = State::SINGLE_STRING;

        } else if (cur_sym == '\'') {

          state_ = State::STR_LITERAL;
        }
        break;
      }

      case State::ROUND_N_STAR: {

        if (prev_sym_ == '*' && cur_sym == ')') {

          ++round_n_star_count_;
          state_ = State::IN;
        }

        break;
      }

      case State::FIGURE: {

        if (cur_sym == '}') {

          ++figure_count_;
          state_ = State::IN;
        }
        break;
      }

      case State::SINGLE_STRING: {

        if (cur_sym == '\n') {

          ++single_string_count_;
          state_ = State::IN;
        }
        break;
      }

      case State::STR_LITERAL: {

        if (cur_sym == '\'') {

          ++str_literal_count_;
          state_ = State::IN;
        }
        break;
      }
    }

    prev_sym_ = cur_sym;
  }

  void reset() {

    state_  = State::IN;
    failed_ = false;
    ended_  = false;

    round_n_star_count_  = 0;
    figure_count_        = 0;
    single_string_count_ = 0;
    str_literal_count_   = 0;
  }

  size_t round_n_star_count()  { return round_n_star_count_;  }
  size_t figure_count()        { return figure_count_;        }
  size_t single_string_count() { return single_string_count_; }
  size_t str_literal_count()   { return str_literal_count_;   }

  bool failed() { return failed_; }
  bool  ended() { return ended_;  }
};

int main() {
  
  Comment_counter countcomm;

  do {
    countcomm.parse(std::cin.get());
  } while (!countcomm.ended());

  // assert(!countcomm.failed());

  std::cout << countcomm.round_n_star_count() << " " 
            << countcomm.figure_count() << " "
            << countcomm.single_string_count() << " "
            << countcomm.str_literal_count() << std::endl;
}