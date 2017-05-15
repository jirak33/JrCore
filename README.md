Jirak's Library
==================================

개요
----
Jirak 코어 라이브러리는 연습용 라이브러리 입니다.

* 퀵-소트 알고리즘
  * 정의 : https://en.wikipedia.org/wiki/Quicksort <br>
    퀵-정렬(Quicksort)은 찰스 앤터니 리처드 호어가 개발한 정렬 알고리즘이다. <br>
    다른 원소와의 비교만으로 정렬을 수행하는 비교 정렬에 속한다. <br>
    퀵 정렬은 n개의 데이터를 정렬할 때, 최악의 경우에는 O(n^2)번의 비교를 수행하고, 평균적으로 O(n log n)번의 비교를 수행한다. <br>
    퀵 정렬은 분할 정복(divide and conquer) 방법을 통해 리스트를 정렬한다. <br>
     <br>
    리스트 가운데서 하나의 원소를 고른다. 이렇게 고른 원소를 피벗이라고 한다. <br>
    피벗 앞에는 피벗보다 값이 작은 모든 원소들이 오고, 피벗 뒤에는 피벗보다 값이 큰 모든 원소들이 오도록 피벗을 기준으로 리스트를 둘로 나눈다. <br>
    이렇게 리스트를 둘로 나누는 것을 분할이라고 한다. 분할을 마친 뒤에 피벗은 더 이상 움직이지 않는다. <br>
    분할된 두 개의 작은 리스트에 대해 재귀(Recursion)적으로 이 과정을 반복한다. 재귀는 리스트의 크기가 0이나 1이 될 때까지 반복된다. <br>
     <br>
    재귀 호출이 한번 진행될 때마다 최소한 하나의 원소는 최종적으로 위치가 정해지므로, 이 알고리즘은 반드시 끝난다는 것을 보장할 수 있다.
    <br>
  * 시간 복잡도 : O(nlogn)

  * 이터레이션 + 메디안 피봇 + 삽입 정렬 응용 방식
    * 대상 : uint32 수치값 1억개
    * 최소 : 4402 ms
    * 최대 : 8587 ms
    * 단점 : 큰 단점 없음.

  * 표준 std::qsort() 함수
    * 대상 : uint32 수치값 1억개
    * 최소 : 4731 ms
    * 최대 : 14552 ms
    * 단점 : 경우에 따라서 콜-스택 많이 소요

  * 이터레이션 + 뒷쪽 피봇 고정 방식
    * 대상 : uint32 수치값 1억개
    * 최소 : 너무 느림.
    * 최대 : 너무 느림.
    * 단점 : 경우에 따라서 콜-스택 많이 소요

  * 순수-재귀 방식
    * 대상 : uint32 수치값 1억개
    * 최소 : 너무 느림.
    * 최대 : 너무 느림.
    * 단점 : 콜-스택 많이 소요

  * 꼬리-재귀 방식
    * 대상 : uint32 수치값 1억개
    * 최소 : 너무 느림.
    * 최대 : 너무 느림.
    * 단점 : 콜-스택 많이 소요


* 거품(버블) 정렬
  * 정의 : https://en.wikipedia.org/wiki/Bubble_sort <br>
    거품 정렬(Bubble sort)은 두 인접한 원소를 검사하여 정렬하는 방법이다. <br>
    시간 복잡도가 O(n^2) {\displaystyle O(n^{2})} O(n^{2})로 상당히 느리지만, 코드가 단순하기 때문에 자주 사용된다. <br>
    원소의 이동이 거품이 수면으로 올라오는 듯한 모습을 보이기 때문에 지어진 이름이다. <br>
  * 시간 복잡도 : O(N^2)
  * 대상 : uint32 수치값 1억개
  * 최소 : 너무 느림.
  * 최대 : 너무 느림.


* 힙 정렬
  * 정의 : https://en.wikipedia.org/wiki/Heapsort <br>
    힙 정렬(Heapsort)이란 최대 힙 트리나 최소 힙 트리를 구성해 정렬을 하는 방법으로서, <br>
    내림차순 정렬을 위해서는 최대 힙을 구성하고 오름차순 정렬을 위해서는 최소 힙을 구성하면 된다. <br>
    최대 힙을 구성하여 정렬하는 방법은 아래 예와 같다. <br>
    1. n개의 노드에 대한 완전 이진 트리를 구성한다. 이때 루트 노드부터 부노드, 왼쪽 자노드, 오른쪽 자노드 순으로 구성한다. <br>
    2. 최대 힙을 구성한다. 최대 힙이란 부노드가 자노드보다 큰 트리를 말하는데, 단말 노드를 자노드로 가진 부노드부터 구성하며 <br>
       아래부터 루트까지 올라오며 순차적으로 만들어 갈 수 있다. <br>
    3. 가장 큰 수(루트에 위치)를 가장 작은 수와 교환한다. <br>
    4. 2와 3을 반복한다.
  * 시간 복잡도 : O(n log n)
  * 대상 : uint32 수치값 1억개
  * 최소 : 11938 ms.
  * 최대 : 29608 ms.
  * 장점 : 평균적인 성능 보장함.


* 삽입 정렬
  * 정의 : https://en.wikipedia.org/wiki/Insertion_sort <br>
    삽입 정렬(揷入整列, insertion sort)은 자료 배열의 모든 요소를 앞에서부터 차례대로 이미 정렬된 배열 부분과 비교하여, <br>
    자신의 위치를 찾아 삽입함으로써 정렬을 완성하는 알고리즘이다. <br>
  * 시간 복잡도 : O(N^2)
  * 대상 : uint32 수치값 1억개
  * 최소 : 너무 느림.
  * 최대 : 너무 느림.
  * 장점 : N 수가 작을때 오버헤드가 없음.


* 기타 유틸


테스트 작성시 유의사항
----

* 테스트 이름을 현재 경로 기반으로 Prefix를 작성하자.
* 빌드는 통합되어 생성되기 때문에, 실행시, 특정 테스트만 실행하려면, 
* prefix 등으로 filtering하여 실행시킬 수 있기 때문이다.

* ex)
```
TEST(JrCore_Algorithm_Sorting_Bubble, DefaultTest)
TEST(JrCore_Algorithm_Sorting_QuickPureRecursion, DefaultTest)
```

빌드하기
----

# 빌드하기.
```
DEBUG   : make TARGET=Debug 
RELEASE : make TARGET=Release
```

실행하기
----

# 전체 실행하기.
```
DEBUG   : ./_BUILD/OUTPUT/Debug/unit_testd
RELEASE : ./_BUILD/OUTPUT/Release/unit_test
```

고급 옵션들
----
# 테스트가 깨졌을 때, 테스트를 Disable 시키고 싶을 경우.!!
```
테스트 이름에 'DISABLED_'라는 prfix를 붙이면, 테스트를 실행하지 않는다.

예를 들어, TEST(JrCore_Algorithm_Sorting_Bubble, DefaultTest) 라는 테스트가 있다면,

'TEST(DISABLE_JrCore_Algorithm_Sorting_Bubble, DefaultTest)' 로 수정한다. 

```

# 일부 파트만 실행하기
```
./_BUILD/OUTPUT/Debug/unit_testd --gtest_filter=POSITIVE_PATTERNS[-NEGATIVE_PATTERNS]
```

# QuickSort PureRecursion만 실행하기
```
./_BUILD/OUTPUT/Debug/unit_testd --gtest_filter=JrCore_Algorithm_Sorting_QuickPureRecursion.*
```


## 끝.


