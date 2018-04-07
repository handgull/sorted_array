#include "sorted_array.h"
#include <cassert>
#include <cmath>
using namespace std;

struct greater_than {
  bool operator()(const int &a, const int &b) const {
    return a > b;
  }
};

struct near_to_10 {
  bool operator()(const int &a, const int &b) const {
    return abs(a-10) < abs(b-10);
  }
};

void test_constructors() {
  /// Default constructor
  cout<<"Testing default constructor..."<<endl;
  sorted_array<uint, greater_than> sarr1;
  // Test 1
  cout<<"  checking the size and elements...";
  assert(sarr1.get_size() == 0);
  assert(sarr1.get_elements() == 0);
  cout<<'['<< (uint)sarr1.get_size() <<',';
  cout<< (uint)sarr1.get_elements() <<"] OK!"<<endl;
  // Test 2
  sarr1.set_size(12);
  cout<<"  checking the NEW size and elements...";
  assert(sarr1.get_size() == 12);
  assert(sarr1.get_elements() == 0);
  cout<<'['<< (uint)sarr1.get_size() <<',';
  cout<< (uint)sarr1.get_elements() <<"] OK!"<<endl;
  // Test 3
  uint expected[] = {83,61,17,14,8,8,7,6,3,2,0};
  sarr1.push(7);
  sarr1.push(8);
  sarr1.push(3);
  sarr1.push(83);
  sarr1.push(2);
  sarr1.push(0);
  sarr1.push(8);
  sarr1.push(61);
  sarr1.push(17);
  sarr1.push(6);
  sarr1.push(14);
  cout<<"  checking _sorted elements...[";
  for(uint i=0; i<sarr1.get_elements(); i++) {
    assert(sarr1[i] == expected[i]);
    cout<< (uint)sarr1[i] <<',';
  }
  cout<<"\b] OK!"<<endl;
  // Test 4
  bool t4 = false;
  try {
  sarr1.push(0);
  sarr1.push(0);
  } catch(...) {
    t4 = true;
  }
  cout<<"  checking out of index...";
  assert(sarr1.get_elements() == 12);
  if(t4)
    cout<< "OK!"<<endl;
  else
    cout<< "ERR"<<endl;
  // Test 5
  sarr1.clear();
  cout<<"  checking the size and elements AFTER cleaning...";
  assert(sarr1.get_size() == 12);
  assert(sarr1.get_elements() == 0);
  cout<<'['<< (uint)sarr1.get_size() <<',';
  cout<< (uint)sarr1.get_elements() <<"] OK!"<<endl;
  // Test 6
  bool t6 = false;
  try {
    sarr1[6];
  } catch(...) {
    t6 = true;
  }
  cout<<"  checking that elements are not accessible AFTER cleaning...";
  if(t6)
    cout<< "OK!"<<endl;
  else
    cout<< "ERR"<<endl;
  sarr1.~sorted_array();

  /// Size constructor
  cout<<"Testing constructor with size init..."<<endl;
  sorted_array<int, near_to_10> sarr2(7);
  // Test 1
  cout<<"  checking the size getter returned value...";
  assert(sarr2.get_size() == 7);
  cout<<'['<< (uint)sarr2.get_size() <<"] OK!"<<endl;
  sarr2.push(8);
  sarr2.push(5);
  sarr2.push(3);
  sarr2.push(10);
  sarr2.push(30);
  sarr2.push(9);
  // Test 2
  cout<<"  checking the elements getter returned value...";
  assert(sarr2.get_elements() == 6);
  cout<<'['<< (uint)sarr2.get_elements() <<"] OK!"<<endl;
  // Test 3
  cout<<"  checking the third element in _array...";
  assert(sarr2(2) == 3);
  cout<<'['<< (uint)sarr2(2) <<"] OK!"<<endl;
  // Test 4

  /// Copy constructor
  cout<<"Testing the copy constructor..."<<endl;
  sorted_array<int, near_to_10> sarr3 = sarr2;
  // Test 1
  cout<<"  checking the size and elements...";
  assert(sarr2.get_size() == sarr3.get_size());
  assert(sarr2.get_elements() == sarr3.get_elements());
  cout<<'['<< (uint)sarr2.get_size() <<" == "<< (uint)sarr3.get_size() <<", ";
  cout<< (uint)sarr2.get_elements() <<" == "<< (uint)sarr3.get_elements();
  cout<<"] OK!"<<endl;
  // Test 2
  cout<<"  checking the second element in _array and in copy's _array...";
  assert(sarr2(1) == sarr3(1));
  cout<<'['<< (uint)sarr2(1) <<" == "<< (uint)sarr3(1) <<"] OK!"<<endl;
  // Test 3
  int expected2[] = {10,9,8,5,3,30}; 
  cout<<"  checking _sorted elements in sarr2 and sarr3(copy)...[";
  for(uint i=0; i<sarr2.get_elements(); i++) {
    assert(sarr2[i] == sarr3[i] && sarr3[i] == expected2[i]);
    cout<< (uint)sarr2[i] <<',';
  }
  cout<<"\b] OK!"<<endl;
  // Test 4
  cout<<"  checking size and elements after the destructor...";
  sarr2.~sorted_array();
  assert(sarr2.get_size() == 0);
  assert(sarr2.get_elements() == 0);
  assert(sarr3.get_size() == 7);
  assert(sarr3.get_elements() == 6);
  cout<<'['<< (uint)sarr2.get_size() <<" != "<< (uint)sarr3.get_size() <<", ";
  cout<< (uint)sarr2.get_elements() <<" != "<< (uint)sarr3.get_elements();
  cout<<"] OK!"<<endl;
  // Test 5
  cout<<"  checking the second element of copy after destructor...";
  assert(sarr3(1) == 5);
  cout<<'['<< (uint)sarr3(1) <<"] OK!"<<endl;
  sarr3.~sorted_array();
}

struct intstr {
  int n;
  string s;

  intstr() {}
  intstr(int num, string str) : n(num), s(str) {}
};

struct alphabetical {
  bool operator()(const string &a, const string &b) const {
    return a < b;
  }
};
struct smaller_intstr {
  bool operator()(const intstr &a, const intstr &b) const {
    if(a.n == b.n)
      return a.s < b.s;
    else
      return a.n < b.n;
  }
};


void test_functors() {
  cout<<"Testing functor with strings..."<<endl;
  sorted_array<string, alphabetical> sarr1(4);
  string expected[] = {"ape","limoncello","zaino","zucchero"};
  sarr1.push("zaino");
  sarr1.push("zucchero");
  sarr1.push("ape");
  sarr1.push("limoncello");
  cout<<"  checking _sorted elements...[";
  for(uint i=0; i<sarr1.get_elements(); i++) {
    assert(sarr1[i] == expected[i]);
    cout<< sarr1[i] <<',';
  }
  cout<<"\b] OK!"<<endl;
  cout<<"Testing functor with structs..."<<endl;
  sorted_array<intstr, smaller_intstr> sarr2(4);
  intstr expected2[] = {{1,"auno"},{1,"buno"},{6,"sei"},{8,"otto"}};
  sarr2.push(intstr(6,"sei"));
  sarr2.push(intstr(1,"auno"));
  sarr2.push(intstr(8,"otto"));
  sarr2.push(intstr(1,"buno"));
  cout<<"  checking _sorted elements...[";
  for(uint i=0; i<sarr1.get_elements(); i++) {
    assert(sarr1[i] == expected[i]);
    cout<<'{'<<sarr2[i].n<<','<<sarr2[i].s<<"},";
  }
  cout<<"\b] OK!"<<endl;
}

void test_iterators() {}

int main() {
  test_constructors();
  cout<<endl;
  test_functors();
  cout<<endl;
  test_iterators();
  return 0;
}
