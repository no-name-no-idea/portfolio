#include <stdio.h>

int main(){

	int i,j;
	int Branch1[6][5]= {0};
	float Branch2[5]={0};
	int gla[10][4] = {0};
	
	
	for(i=0; i<5; i++){
		
		for(j=0;j<4;j++){
			switch(i){
			case 0 : printf("kim"); break; 
			case 1 : printf("LEE"); break; 
			case 2 : printf("PARK"); break; 
			case 3 : printf("SONG"); break; 
			case 4 : printf("CHOI"); break; 
			}
			printf("�� %d/4�б��� ������ �Է��ϼ��� :\n",j+1);
			scanf("%d",&Branch1[i][j]); 
		}
	}
	for(i = 0; i<5; i++){ 
		for(j = 0; j < 4; j++){
			Branch1[i][4] += Branch1[i][j];
		}
	}
	
	for(i = 0; i<6; i++){ 
		for(j = 0; j < 5; j++){
			Branch1[5][i] += Branch1[j][i];
		}
	}

	printf("�ǸŻ��\t1/4�б�\t2/4�б�\t3/4�б�\t4/4�б�\t����\n");
	for(i = 0; i<6; i++){ 
		switch(i){
			case 0 : printf("kim\t"); break; 
			case 1 : printf("LEE\t"); break; 
			case 2 : printf("PARK\t"); break; 
			case 3 : printf("SONG\t"); break; 
			case 4 : printf("CHOI\t"); break;
			case 5 : printf("�б�����"); break;  
			}
		for(j = 0; j < 5; j++){
			printf("\t%d", Branch1[i][j]);
		}printf("\n");}
	printf("�б����\t");
	for(i = 0; i<5; i++){ 
		Branch2[i] += Branch1[5][i];
	}		
	for(i = 0; i<5; i++){ 
		Branch2[i] = Branch2[i]/5;
		printf("%.2f\t",Branch2[i]);
	}printf("\n");
	
	
	
} 
