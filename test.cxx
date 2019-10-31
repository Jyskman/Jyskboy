
#include "test.h"

#include<iostream>
#include<list>
#include<string>
#include<algorithm>

using namespace::std;

vector<test> test_vector;

test::test(int a, int x, int y ) {

x_p = x;
y_p = y;


};







bool comparefunction( test &a , test &b ) {

if ( a.x_p != b.x_p ) {
return false;
}

if ( a.y_p != b.y_p ) {
return false;
}

return true;


};

// https://stackoverflow.com/questions/6771374/sorting-an-stl-vector-on-two-values
bool compare_entry( const test & e1, const test & e2) {
  if( e1.x_p != e2.x_p)
    return (e1.x_p < e2.x_p);
  return (e1.y_p < e2.y_p);
}




void testfunc() {
cout << " works " << endl;
// https://stackoverflow.com/questions/12850181/stdunique-and-removing-duplicates-from-a-container-of-objects


test * new_test = new test( 1, 2, 2 );
test_vector.push_back( *new_test );
delete new_test;

test * new_test2 = new test( 1, 3, 2 );
test_vector.push_back( *new_test2 );
delete new_test2;

test * new_test3 = new test( 1, 2, 2 );
test_vector.push_back( *new_test3 );
delete new_test3;

test * new_test4 = new test( 1, 2, 2 );
test_vector.push_back( *new_test4 );
delete new_test4;

test * new_test5 = new test( 1, 5, 2 );
test_vector.push_back( *new_test5 );
delete new_test5;

test * new_test6 = new test( 1, 5, 2 );
test_vector.push_back( *new_test6 );
delete new_test6;

test * new_test7 = new test( 1, 2, 2 );
test_vector.push_back( *new_test7 );
delete new_test7;

// pkts.erase(unique(pkts.begin(), pkts.end(), comparePacketPtrs), pkts.end());

for ( int i = 0; i < test_vector.size(); i++ ) {

    cout << " x " << test_vector.at(i).x_p << " y " << test_vector.at(i).y_p << endl;

};


sort( test_vector.begin(), test_vector.end(), compare_entry );


test_vector.erase( unique(test_vector.begin(), test_vector.end(), comparefunction ), test_vector.end()   );

cout << " after " << endl;

for ( int i = 0; i < test_vector.size(); i++ ) {

    cout << " x " << test_vector.at(i).x_p << " y " << test_vector.at(i).y_p << endl;

};


cout << test_vector.size() << endl;

};
