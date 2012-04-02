#include <cstddef>
#include <iostream>
#include <set>
#include <map>

namespace{
  using namespace std;

  struct Pos{
    size_t x;
    size_t y;
  };

  struct PosLess:public binary_function<Pos,
      Pos, bool> {
    bool operator()(Pos ps1, Pos ps2) const
    {
      if(ps1.x == ps2.x){
          if(ps1.y < ps2.y)
            return true;
          else
            return false;
        }
      else{
          if(ps1.x < ps2.x){
              return true;
            }
          else{
              return false;
            }
        }
    }
  };

  set<Pos,PosLess> posCount;

  bool JudgePos(Pos p){
    static const size_t limit = 19;
    size_t tmpsumx=0;
    size_t sum=0;
    size_t tmpX = p.x;
    while (tmpX > 0) {
        size_t digit = tmpX % 10;
        tmpsumx += digit;
        tmpX /= 10;
      }
    sum = tmpsumx;
    size_t tmpY = p.y;
    size_t tmpsumy=0;
    while (tmpY > 0) {
        size_t digit = tmpY % 10;
        tmpsumy += digit;
        tmpY /= 10;
      }
    sum += tmpsumy;
    return (sum <= limit);
  }

  void RunMonkeyRun(Pos p){
    if(JudgePos(p)){
        //        cout << "(" << p.x << "," << p.y << ") ";
        pair<set<Pos,PosLess>::iterator,bool> tit = posCount.insert(p);
        if(tit.second == true){
            Pos px = {p.x+1,p.y};
            RunMonkeyRun(px);
            Pos py = {p.x,p.y+1};
            RunMonkeyRun(py);
          }
      }
  }

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

  void Start(){
    Pos StartPos={0,0};
    RunMonkeyRun(StartPos);
  }

}

int main()
{
  using namespace std;
  Start();
//  set<Pos,PosLess>::iterator it;
//  for(it = posCount.begin();it!=posCount.end();++it){
//      cout << "(" << (*it).x << "," << (*it).y << ") ";
//    }
//  cout << posCount.size() << endl;
//  cout << CaculateMax(19)[0] << endl;
  size_t countPos = (posCount.size() - (CaculateMax(19)[0]+1))*4 + 1;
  cout << countPos << endl;
  return 0;
}
