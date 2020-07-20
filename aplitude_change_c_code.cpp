#include <stdio.h>
#include <stdlib.h>
#define UINT_SIZE 8
int main(int argc,char* argv[]){
	FILE *fp_in, *fp_out_plus, *fp_out_minus;//파일 선언을 해주는 코드 
	
	fp_in= fopen("input.raw", "rb"); //읽기모드로 열기(rb가 읽기모드)  
	fp_out_plus= fopen("output_plus.raw", "wb");//증폭을 쓰기모드로 열기(wb가 쓰기모드) 
	fp_out_minus= fopen("output_minus.raw", "wb");//감소를 쓰기모드로 열기(wb가 쓰기모드) 

	short * buf = (short*)malloc(sizeof(short)*UINT_SIZE);//신호를 읽은뒤 저장할 공간인 buf를 선언 
	
	while(0!=fread(buf, sizeof(short), UINT_SIZE, fp_in)){//신호를 읽은뒤 buf에 저장 
		//fread(buf, sizeof(short), UINT_SIZE, fp_in)만 넣어주어도 상관이 없음 
		
		static int n = 1;//data out값을 확인하기 위한 n을 선언 
		for(int i = 0; i<UINT_SIZE; i++){//증폭을 위한 for문 
			buf[i] *= 2;	//2배로 증폭 
		}
		fwrite(buf, sizeof(short), UINT_SIZE, fp_out_plus); // fp_out_plus에 증가한 값을 저장
		
		for(int i = 0; i<UINT_SIZE; i++){//증폭을 위한 for문 
			buf[i] /= 4;	//0.5배로 증폭 
							//0.25배를 해주는 이유는 앞에 코드에서 2배를 증가시켰으므로 2배를 0.5배 시켜주기 위해선 /4를 해주어야함 
		}
		fwrite(buf, sizeof(short), UINT_SIZE, fp_out_minus); // fp_out_minus에 증가한 값을 저장
		printf("data out = %d byte \n", sizeof(short)*UINT_SIZE*n++);
	}
	free(buf);//buf값을 free시켜줌 (메모리 효율에 좋음) 
	fclose(fp_in);//열었던 파일을 닫아줌 
	fclose(fp_out_plus);//위와 동일
	fclose(fp_out_minus); //위와 동일
	 
	return 0;
	
}
