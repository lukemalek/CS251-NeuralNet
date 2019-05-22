#ifndef _SD_FUN_
#define _SD_FUN_
#include<cstddef>
#include<cstdlib>
#include<climits>
#include<string>
#include<map>

struct Range {
  int pos, len;
};
const int max_length = 100000;
const int mem_len = 10000;

class irange {
private:
	int last, curr;

public:
	irange(int end): last(end), curr(0) {}

	const irange& begin() const { return *this; }
	const irange& end() const { return *this; }

	bool operator!=(const irange&) const { return curr < last; }
	void operator++() { ++curr; }
	int operator*() const { return curr; }
};

struct str_or_num {
  std::string str;
  long long num_i;
  double num_d;
  enum {STRING, DOUBLE, LONG} kind;
  str_or_num(const char *_s) : str(_s), kind(STRING) {}
  str_or_num(std::string _s) : str(_s), kind(STRING) {}
  str_or_num(char _i) : num_i(_i), kind(LONG) {}
  str_or_num(short _i) : num_i(_i), kind(LONG) {}
  str_or_num(int _i) : num_i(_i), kind(LONG) {}
  str_or_num(unsigned int _i) : num_i(_i), kind(LONG) {}
  str_or_num(long _i) : num_i(_i), kind(LONG) {}
  str_or_num(std::size_t _i) : num_i(_i), kind(LONG) {}
  str_or_num(long long _i) : num_i(_i), kind(LONG) {}
  str_or_num(float _d) : num_d(_d), kind(DOUBLE) {}
  str_or_num(double _d) : num_d(_d), kind(DOUBLE) {}
};

extern char *mem, *yaml, *query_str, *response;

// from sd_fun.cpp
extern void init(const char *c = 0);
extern void quit(const char *c = 0);
extern bool just_starting();
extern void initialize(char *&mem, char *&yaml);
extern void initialize_empty(char *&mem, char *&yaml);
extern void initialize_from_file(const char *fname, char *&mem, char *&yaml);
extern void terminate(const char *buffer, const char *yaml);
extern char *echo_string(const char *s);
extern char *query_data_port(const char *query);
extern std::string fetch(const char *url);
extern std::string fetch(std::string url);
extern void read_file_into_mem(const char *fname, char *mem, int start = 0);

extern void check_equal(bool computed, bool correct);
extern void check_equal(char computed, char correct);
extern void check_equal(int computed, int correct);
extern void near_equal(double computed, double correct);
extern void check_equal(const char *computed, int pos, const char *correct);
extern void check_equal(const char *computed, const char *correct);

extern void show_int_array(const int *arr, int size);
extern void show_char_array(const char *arr, int size);

extern long long current_time();
extern const char *time_of_day(long t_raw);
extern const char *time_of_day(const char *mem, int pos);
extern double random_number();

// from str_util.cpp
extern int length_of(const char *s, int pos=0);
extern int indentation_at(const char *response, int pos);
extern int indentation_of(const char *response, int pos);
extern void print_range(const char *s, Range r);

extern void append(char *s, const char *t);
extern void append(char *s, const char *t, Range r, const char *post="");
extern void append(char *s, int n, const char *post="");
extern void append(char *s, unsigned int n, const char *post="");
extern void append(char *s, long n, const char *post="");
extern void append(char *s, long long n, const char *post="");
extern void append(char *s, std::size_t n, const char *post="");
extern void append(char *s, double d, const char *post="");

extern void append(char *s, const char *pre, const char *t, const char *post="");
extern void append(char *s, const char *pre, const char *t, Range r, const char *post="");
extern void append(char *s, const char *pre, int n, const char *post="");
extern void append(char *s, const char *pre, unsigned int n, const char *post="");
extern void append(char *s, const char *pre, long n, const char *post="");
extern void append(char *s, const char *pre, long long n, const char *post="");
extern void append(char *s, const char *pre, std::size_t n, const char *post="");
extern void append(char *s, const char *pre, double d, const char *post="");

extern void add_yaml(const char *fname, const std::map<std::string, str_or_num> &m = {});

extern int index_of(const char *s, Range r, const char *query);
extern int index_of(const char *s, int start, const char *query);
extern int index_of(const char *s, const char *query);

extern bool in(const char *s, const char *query);
extern bool in(const char *s, int start, const char *query);
extern bool in(const char *s, Range r, const char *query);
extern bool was_pressed(const char *s, const char *query);
extern bool was_pressed(const char *s, const char *query, int i);
extern int was_picked(const char *s, const char *query);
extern int was_picked(const char *s, const char *query, int i);
extern int touch_pos_x(const char *s);
extern int touch_pos_y(const char *s);
extern int touch_start_pos_x(const char *s);
extern int touch_start_pos_y(const char *s);

extern int count(const char *s, Range r, const char *query);
extern int count(const char *s, int start, const char *query);
extern int count(const char *s, const char *query);

extern void write_chars_at(char *mem, int pos, char c0, char c1=-1, char c2=-1, char c3=-1, char c4=-1, char c5=-1, char c6=-1, char c7=-1, char c8=-1, char c9=-1, char c10=-1, char c11=-1, char c12=-1, char c13=-1, char c14=-1, char c15=-1, char c16=-1, char c17=-1, char c18=-1, char c19=-1);
extern void write_at(char *mem, int pos, const char *x);
extern void write_at(char *mem, int pos, bool t);
extern void write_at(char *mem, int pos, int n);
extern void write_at(char *mem, int pos, long n);
extern void write_at(char *mem, int pos, long long n);
extern void write_at(char *mem, int pos, std::size_t n);
extern void write_at(char *mem, int pos, double d);
extern void write_at(char *mem, int pos, const char *x, Range r);
extern void write_at(char *mem, int pos, const char *x, int start);

extern bool is_whitespace(char c);
extern bool is_whitespace_or_char(char c, const char *chars = "");
extern Range split(char *mem, Range &r, const char *sep="");
extern Range split(char *mem, int &start, const char *sep="");

extern Range lstrip(const char *yaml, Range r, const char *chars = "");
extern Range rstrip(const char *yaml, Range r, const char *chars = "");
extern Range strip(const char *yaml, Range r, const char *chars = "");

extern Range find_value(const char *yaml, Range r, const char *key, bool skip_quotes = true);
extern Range find_value(const char *yaml, int start, const char *key, bool skip_quotes = true);
extern Range find_value(const char *yaml, const char *key, bool skip_quotes = true);

extern int as_integer(const char *yaml, int pos);
extern int as_integer(const char *yaml, Range r);
extern int as_double(const char *yaml, int pos);
extern int as_double(const char *yaml, Range r);

#endif // _SD_FUN_
