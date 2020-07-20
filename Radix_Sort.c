#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
void RadixSort(int *data, int n, int numberOfTimes)//기수정렬 함수 
{
  const int notation = 10;
  int i, cipher = 1, *cnt, *tmp;//for문을 돌리기 위한 i ,자릿수를 알려주기위한 cipher,정렬에 쓰일 cnt와 tmp 선언  
  tmp = (int *)malloc(n * sizeof(int));//tmp에 n*4byte만큼 동적할당 
  cnt = (int *)malloc(notation * sizeof(int)); //notation * 4byte만큼 동적할당 

  while(--numberOfTimes >= 0)//numberOfTimes만큼 정렬시켜줌 
  {
    for(i = 0; i < notation; i++) cnt[i] = 0;             // 카운터를 0으로 초기화 
    for(i = 0; i < n; i++) cnt[(data[i]/cipher)%notation]++; // 대상수 구하기 
    for(i = 1; i < notation; i++) cnt[i] += cnt[i-1];     // 누적수 구하기 
    for(i = n-1; i >= 0; i--)
    tmp[--cnt[(data[i]/cipher)%notation]] = data[i];       // tmp에 자료를 정렬 시킨다. 
    memcpy(data, tmp, n * sizeof(int));                   // 재배치된 자료를 원본(data)에 덮어쓴다. 
    printf("%d의 자리 정렬\t",cipher) ;
	cipher *= notation; //자릿수를 10배 시켜준다 
    for(i = 0; i < n; i++) printf(" %2d  ", data[i]); printf("\n"); //정렬후 출력 
  }
  free(tmp);//tmp의 동적할당을 해제 
  free(cnt);//cnt의 동적할당을 해제 
}

int main()
{
	clock_t start, end; //시간시작 시작 
    double result;//clock수 
  	int *data;//데이터를 넣어줄 공간선언 
   	int i,n; // for문을 위한 i와 몇개를 입력받아줄건지에 대한 n선언	
   	printf("몇 개를 입력 하시겠습니까? : ");
	scanf("%d",&n);//몇개의 데이터를 정렬할건지 입력받음
	data = (int *)malloc(n * sizeof(int));//data에 n*4byte만큼 동적할당 
	for(i=0; i<n; i++){ 
		data[i] = rand() % 10000; 
	}
 	printf("_before_\n");
 	for(i = 0; i < n; i++) printf(" %2d  ", data[i]); printf("\n");//정렬전 data값들을 출력 
 	
 	printf("\n_radix_sort_\n");
 	start = clock();
	RadixSort(data, n, 4);//정렬을 하는 함수 0~9999까지 4자리 수이므로 4번반복 
 	end = clock(); //시간 측정 끝
  	printf("\n_after_\n");
 	for(i = 0; i < n; i++) printf(" %2d  ", data[i]); printf("\n");//정렬 완료후 출력 
 	
    result = (double)(end - start);//끝난 시간 - 시작 시간 = 실행시간 
    printf("실행 시간 : %fms", result);//실행시간 출력 (1000클락은 1초 1클럭은 1ms) 
 	system("pause");
 	free(data);
  	return 0;
} 
