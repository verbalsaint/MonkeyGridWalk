#include <cstddef>
#include <iostream>
#include <map>


namespace{
  using namespace std;
  map<size_t,size_t> CaculateMax(size_t limit_in){
    map<size_t,size_t> maxSize;
    for(size_t _sum = 0; _sum <= limit_in; ++_sum ){
        size_t _left = limit_in - _sum;

        for(size_t j = 1; ;++j){
            size_t tmpsum = 0;
            size_t tmpj = j;
            while (tmpj > 0) {
                size_t digit = tmpj % 10;
                tmpsum += digit;
                tmpj /= 10;
              }
            if(tmpsum <= _left) continue;
            else{
                maxSize[_sum] = j-1;
                break;
              }
          }
      }
    return maxSize;
  }



  size_t RunMonkeyRun(){

    size_t _countPos = 1; // add initial pos(0,0)

    //map<size_t,size_t>&& maxSize = CaculateMax(19); //get the Max position
    map<size_t,size_t> maxSize = CaculateMax(19); //get the Max position
    _countPos += maxSize[0] * 4; // four axis,(0,y) (0,|-y|) (x,0) (|-x|,0)

    size_t same = 0; // count the same position, e.g : (x,y) while (x==y) is true
    size_t xycount = 0;
    /**
      run from x axis
      */
    for(size_t xrun = 1 ; xrun < maxSize[0] ; ++xrun){
        size_t tmpxrun = xrun;
        size_t tmpsum = 0;
        while (tmpxrun > 0) {
            size_t _digit = tmpxrun % 10;
            tmpsum += _digit;
            tmpxrun /= 10;
          }

        if(tmpsum == 19) continue; // (199,0) has been counted before, so escape.
        if(xrun <= maxSize[tmpsum]){
            xycount = xycount + (maxSize[tmpsum]-1);
            ++same;
          }
        else xycount += maxSize[tmpsum];
      }
    cout << "X : " << xycount << endl;
    xycount *= 8; // 4 quadrant, 8 positions (x,y) (-x,y) (x,-y) (-x,-y)
    _countPos += xycount;
    _countPos += (same*4); // 4 quadrant (x,y) while |x|==|y| is true
    return _countPos;
  }

}

int main()
{
  using namespace std;
  //cout << "Monkey moves : "<< RunMonkeyRun() << endl;
  cout << RunMonkeyRun() << endl;
  map<size_t,size_t> tmp =  CaculateMax(19) ;
  cout << tmp[0] << endl;
  RunMonkeyRun();
  return 0;
}
