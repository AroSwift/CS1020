void binary_search( vector<int> v, int key ) {
  int lower = 0, upper = v.size(), mid;

  while( lower <= upper ) {
    mid = lower + (upper + lower) / 2;
    if( v[mid] == key ) {
      cout << v[mid] << endl;
      break;
    }

    if( lower < key ) {
      lower = mid + 1;
    } else {
      upper = mid - 1;
    }

  }
}