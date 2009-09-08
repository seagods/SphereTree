#include <iostream>
using namespace std;

template <class T> class CMyNullCheck{
     public:
     CMyNullCheck(){}
     ~CMyNullCheck(){}
     void  MyCheck(T *);
};
template <class T>
void CMyNullCheck<T>::MyCheck(T *i){
   try{
    if(i==NULL)throw CMyNullCheck();
    }
    catch(CMyNullCheck)
    {
      cout << "Null pointer returned, programme failed\n";
      exit(0);
    }

}
