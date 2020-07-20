#include <stdio.h>
#include <stdlib.h>
#define UINT_SIZE 8
int main(int argc,char* argv[]){
	FILE *fp_in, *fp_out_plus, *fp_out_minus;//���� ������ ���ִ� �ڵ� 
	
	fp_in= fopen("input.raw", "rb"); //�б���� ����(rb�� �б���)  
	fp_out_plus= fopen("output_plus.raw", "wb");//������ ������� ����(wb�� ������) 
	fp_out_minus= fopen("output_minus.raw", "wb");//���Ҹ� ������� ����(wb�� ������) 

	short * buf = (short*)malloc(sizeof(short)*UINT_SIZE);//��ȣ�� ������ ������ ������ buf�� ���� 
	
	while(0!=fread(buf, sizeof(short), UINT_SIZE, fp_in)){//��ȣ�� ������ buf�� ���� 
		//fread(buf, sizeof(short), UINT_SIZE, fp_in)�� �־��־ ����� ���� 
		
		static int n = 1;//data out���� Ȯ���ϱ� ���� n�� ���� 
		for(int i = 0; i<UINT_SIZE; i++){//������ ���� for�� 
			buf[i] *= 2;	//2��� ���� 
		}
		fwrite(buf, sizeof(short), UINT_SIZE, fp_out_plus); // fp_out_plus�� ������ ���� ����
		
		for(int i = 0; i<UINT_SIZE; i++){//������ ���� for�� 
			buf[i] /= 4;	//0.5��� ���� 
							//0.25�踦 ���ִ� ������ �տ� �ڵ忡�� 2�踦 �����������Ƿ� 2�踦 0.5�� �����ֱ� ���ؼ� /4�� ���־���� 
		}
		fwrite(buf, sizeof(short), UINT_SIZE, fp_out_minus); // fp_out_minus�� ������ ���� ����
		printf("data out = %d byte \n", sizeof(short)*UINT_SIZE*n++);
	}
	free(buf);//buf���� free������ (�޸� ȿ���� ����) 
	fclose(fp_in);//������ ������ �ݾ��� 
	fclose(fp_out_plus);//���� ����
	fclose(fp_out_minus); //���� ����
	 
	return 0;
	
}
