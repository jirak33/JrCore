Jirak's Library
==================================

개요
----
Jirak 코어 라이브러리는 연습용 라이브러리 입니다.

* 버블 정렬
* 힙 정렬
* 삽입 정렬
* 퀵-소트 알고리즘
  * 이터레이션 + 메디안 피봇 + 삽입 정렬 응용 방식
  * 이터레이션 + 뒷쪽 피복 고정 방식
  * 순수-재귀 방식
  * 꼬리-재귀 방식
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


