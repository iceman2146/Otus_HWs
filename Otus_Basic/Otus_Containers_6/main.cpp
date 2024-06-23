#define __CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW

#include "Sequence.h"
#include "ForwardList.h"
#include "List.h"
#include "TestExersize.h"


int main()
{
  size_t Kol_vo_elementov = 10;
  Sequence<int> SequenceContainer_int;
  test_seq(SequenceContainer_int, Kol_vo_elementov);
  
  ForwardList<int> OneWayContainer_int;
  test_seq(OneWayContainer_int, Kol_vo_elementov);
  

  List<float> TwoWayContainer_int;
  test_seq(TwoWayContainer_int, Kol_vo_elementov);

  _CrtDumpMemoryLeaks();
  return 0;
}