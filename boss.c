#include<stdio.h>
#include<stdlib.h>
int compare (char *buff,char *pattern,int n,int z){
	int k,j,l;
	int O_K1;
			for (k=0;k<z-n;k=k++){
					O_K1=0;
				for (j=0;j<n;j++){
					if (buff[k+j]==pattern[j]){
						O_K1=O_K1+1;
						//printf("%d\t",O_K1);
						if (O_K1==n-1){
							/*for (l=0;l<100;l++){
								printf("%c",buff[l]);
							}*/
							return 1;
						}
					}
					
			    }
				
			}
			
			return 0;
	
}
int line_empty(char *adr_names,int n){
	int i,l,c=0;
	for (i=0;i<n;i++){
		if (adr_names[i]=='\0'){
			c++;
		}
	}
	//printf("%d\n",c);
	if (c==n){
		return 1;
	}else{
		return 0;
	}
}

int main(){
	char pattern_dev[13]="deviceAddress";
	char pattern_amount[6]="Amount";
	int c;
	int O_K1;
	int i,j,k,l,p;
	//char *buff;
	char buff[100];
	char new_buff[11];
	char num_buff[11];
	int buff_num=0;
	int size=0;
	int flag=0,once=0,num_flag=0;;
	char adr_names[4][6];
	int amount[4];
	FILE *jac_file;
	FILE *bla_file;
	FILE *bla_file1;
	FILE *bla_file2;
	for (i=0;i<4;i++){
		for (j=0;j<6;j++){
			adr_names[i][j]='\0';
		}
	}
	for(i=0;i<4;i++){
		amount[i]=0;
	}
	memset(new_buff,'\0',11);
	memset(num_buff,'\0',11);
	if((jac_file = fopen ("jac.xml","rb"))==NULL) {
       printf("i cant open this file 1.\n");
       exit(1);
    }
	if((bla_file = fopen ("bla.txt","wb+"))==NULL) {  ///important 
       printf("i cant open this file 2.\n");
       exit(1);
    }
    c=fgetc(jac_file);
	while(c!=EOF){
		//printf("%c",c);
		fputc(c,bla_file);
		c=fgetc(jac_file);
		
	}
	fclose(bla_file);
	fclose(jac_file);
	if((bla_file1 = fopen ("bla.txt","rb"))==NULL) {
       printf("i cant open this file 3.\n");
       exit(1);
    }
	c=fgetc(bla_file1);
	memset(buff,'\0',100);
	fclose(bla_file1);
	if((bla_file2 = fopen ("bla.txt","rb"))==NULL) {
       printf("i cant open this file 3.\n");
       exit(1);
    }
	c=fgetc(bla_file2);
	i=0;
	while (c!=EOF){
		buff[i]=c;
		//printf("%c_",buff[i]);
		i++;
		if(c=='\n'){
			/*for (l=0;l<100;l++){
					printf("%c_",buff[l]);
				}*/
				
					for (l=0;l<100;l++){	
							if((int)buff[l]!=0 && (int)buff[l+1]==0){//удаление сомволов с кодом 0.
								for (j=l+1;j<95;j++){
									buff[j]=buff[j+1];
									
								}
							}
					}
			if(compare(buff,pattern_dev,14,100)){// если в строке файла содержится deviceAddress.
				/*	for (l=0;l<70;l++){
					printf("%c",buff[l]);
				}*/


				flag=0;
				j=0;
				size=0;
				for (l=0;l<100;l++){
					if (flag==2){
						break;
					}
					if (flag==1&&buff[l]!='"'){
						new_buff[j]=buff[l];
						j++;
					}
					if (buff[l]=='"'){
						flag++;
					}
					
				}
				/*for (l=0;l<10;l++){
					printf("%c",new_buff[l]);
				}
				printf("\n");*/
				once=1;
				for(l=0;l<4;l++){
					if(compare(new_buff,&adr_names[l][0],6,10)){
				//printf("ok");
				     once=0;
					}/*else{
						for (l=0;l<10;l++){
					printf("%c",new_buff[l]);
				}
				printf("\n");
				        once=0;
						//size=1;
					}*/
				}
				if (once){
					size=1;
				}
				if(size){
					for(l=0;l<4;l++){
						if (line_empty(&adr_names[l][0],6)){
							k=l;
						}
					}
					
						for (j=0;j<6;j++){
							adr_names[k][j]=new_buff[j];
							//printf("%c",new_buff[j]);
					}
				
				
				
				}
				
				
			}
			
			if(compare(buff,pattern_amount,6,100)){// если в строке файла содержится amount.
				/*for (l=0;l<70;l++){
					printf("%c",buff[l]);
				}*/
				num_flag=0;
				j=0;
				for (l=0;l<70;l++){
					if (num_flag==1&&buff[l]=='<'){
						num_flag++;
					}
					if (num_flag==2){
						break;
					}
					if (num_flag==1&&buff[l]!='>'){
						num_buff[j]=buff[l];
						j++;
					}
					/*if (num_flag==1&&buff[l]=='<'){
						num_flag++;
					}*/
					if (buff[l]=='>'){
						num_flag++;
					}
				}
				for(l=0;l<4;l++){
					if(compare(new_buff,&adr_names[l][0],6,10)){
					/*	for (j=0;j<6;j++){
							printf("%c",new_buff[j]);
					}
					printf("\t");*/
				    amount[l]=amount[l]+atoi(num_buff);
					}
				}
				//printf("%d\n",atoi(num_buff));
				/*for (l=0;l<11;l++){
					printf("%c",num_buff[l]);
				}
				printf("\n");*/
			}
			i=0;
			memset(buff,'\0',100);
			memset(num_buff,'\0',11);
		}
		c=fgetc(bla_file2);
	}
	printf("\n");
	for (i=0;i<4;i++){
		for (j=0;j<6;j++){
			printf("%c",adr_names[i][j]);
		}
		printf(" %d\n",amount[i]);
	}
	/*for (j=0;j<4;j++){
			printf("%d\n",amount[j]);
		}*/
	fclose(bla_file2);
	return 0;
}