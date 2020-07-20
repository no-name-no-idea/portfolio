#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
void RadixSort(int *data, int n, int numberOfTimes)//������� �Լ� 
{
  const int notation = 10;
  int i, cipher = 1, *cnt, *tmp;//for���� ������ ���� i ,�ڸ����� �˷��ֱ����� cipher,���Ŀ� ���� cnt�� tmp ����  
  tmp = (int *)malloc(n * sizeof(int));//tmp�� n*4byte��ŭ �����Ҵ� 
  cnt = (int *)malloc(notation * sizeof(int)); //notation * 4byte��ŭ �����Ҵ� 

  while(--numberOfTimes >= 0)//numberOfTimes��ŭ ���Ľ����� 
  {
    for(i = 0; i < notation; i++) cnt[i] = 0;             // ī���͸� 0���� �ʱ�ȭ 
    for(i = 0; i < n; i++) cnt[(data[i]/cipher)%notation]++; // ���� ���ϱ� 
    for(i = 1; i < notation; i++) cnt[i] += cnt[i-1];     // ������ ���ϱ� 
    for(i = n-1; i >= 0; i--)
    tmp[--cnt[(data[i]/cipher)%notation]] = data[i];       // tmp�� �ڷḦ ���� ��Ų��. 
    memcpy(data, tmp, n * sizeof(int));                   // ���ġ�� �ڷḦ ����(data)�� �����. 
    printf("%d�� �ڸ� ����\t",cipher) ;
	cipher *= notation; //�ڸ����� 10�� �����ش� 
    for(i = 0; i < n; i++) printf(" %2d  ", data[i]); printf("\n"); //������ ��� 
  }
  free(tmp);//tmp�� �����Ҵ��� ���� 
  free(cnt);//cnt�� �����Ҵ��� ���� 
}

int main()
{
	clock_t start, end; //�ð����� ���� 
    double result;//clock�� 
  	int *data;//�����͸� �־��� �������� 
   	int i,n; // for���� ���� i�� ��� �Է¹޾��ٰ����� ���� n����	
   	printf("�� ���� �Է� �Ͻðڽ��ϱ�? : ");
	scanf("%d",&n);//��� �����͸� �����Ұ��� �Է¹���
	data = (int *)malloc(n * sizeof(int));//data�� n*4byte��ŭ �����Ҵ� 
	for(i=0; i<n; i++){ 
		data[i] = rand() % 10000; 
	}
 	printf("_before_\n");
 	for(i = 0; i < n; i++) printf(" %2d  ", data[i]); printf("\n");//������ data������ ��� 
 	
 	printf("\n_radix_sort_\n");
 	start = clock();
	RadixSort(data, n, 4);//������ �ϴ� �Լ� 0~9999���� 4�ڸ� ���̹Ƿ� 4���ݺ� 
 	end = clock(); //�ð� ���� ��
  	printf("\n_after_\n");
 	for(i = 0; i < n; i++) printf(" %2d  ", data[i]); printf("\n");//���� �Ϸ��� ��� 
 	
    result = (double)(end - start);//���� �ð� - ���� �ð� = ����ð� 
    printf("���� �ð� : %fms", result);//����ð� ��� (1000Ŭ���� 1�� 1Ŭ���� 1ms) 
 	system("pause");
 	free(data);
  	return 0;
} 
