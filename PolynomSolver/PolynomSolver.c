#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_LENGHT 1000
int valuetaker(char* filename,double values2[40]);/* dosyadan sayıları alıyor*/ 
int polynomialtaker(char* filename,char polinom[MAX_LENGHT]);/* dosyadan polinomu alıyor*/ 
double calculater(double value,char polynom[MAX_LENGHT]);/* alınan sayıları polinomda hesaplayıp sonucu döndürüyor*/ 
				/* prototype yazmadığımda arrayleri fonksiyona gönderirken sorun yaşıyordum. O yüzden kullanmam gerekti*/ 


int main(){/* main fonksiyonda fonksiyonlardan dönen değerleri dosyaya yazıyorum*/
	FILE *fp3;
	fp3 = fopen("evaluations.txt", "w+");/* yazmak için dosyayı açıyorum*/
	double values[40],results[40];/* sayılar ve sonuçlar için float array tanımlıyorum*/
	char polynom[MAX_LENGHT];/*polinomu alacağım değişken */
	int a;/*array sayacı */
	
	valuetaker("values.txt",values);	/* değerleri values arrayine alıyor*/
	polynomialtaker("polynomial.txt",polynom);/*polynomial.txtden polinomu alıyor */
	
	for(a=0;values[a]!='\0';a++){/*calculater fonksiyonunda alınan polinomda değerleri kullanarak çıkan sonucu results 
									arrayine gönderiyorum. değerler kadar dönüyor */
		results[a]=calculater(values[a],polynom); /* */
		fprintf(fp3,"%.2lf\n",results[a]); /* virgülden sonra 2 rakam olacak şekilde dosyaya yazıyorum(örnekte istenilen
											 gibi)*/
	}
	
	fclose(fp3);/* dosyayı kapatıyorum*/
	return 0;
}


int valuetaker(char* filename,double values2[40]){
	FILE *fp;
	int x=0;/* array sayacı*/
	fp = fopen(filename, "r"); /*dosyayı açıyorum */
    while(1){  
         if( feof(fp) )/* dosyanın sonunda döngüden çıksın*/
         { 
         	break ;
         }
		 
		 fscanf(fp,"%lf ",&values2[x]); /*değerleri teker teker alıyorum*/
		 x=x+1;
	}
	values2[x]='\0'/*son değere null atıyorum junk kalmasın diye */;
	fclose(fp);/* dosyayı kapatıyorum.*/
	return 0;
}

int polynomialtaker(char* filename,char polinom[MAX_LENGHT]){
	FILE *fp2;
	fp2 = fopen(filename, "r");/*dosyayı açıyorum */
    fgets(polinom,MAX_LENGHT,fp2);/*polinomu alıyorum*/
	fclose(fp2);/*dosyayı kapatıyorum */
	return 0;
}
double calculater(double value,char polynom[MAX_LENGHT]){
	int x=0,z=0,lenght,tempus,flag=1;/*x polinom char arrayi sayacı,z kıyaslarken charları attığım tempnumber char arrayi sayacı,
	 tempus üslü sayıyı tuttuğum sayaç,flag toplama çıkarma için  */
	lenght=strlen(polynom);/*gereksiz döngü olmasın diye polinomdaki karakter kadar döndüreceğim polinomun uzunluğun 
	alıyorum. */
	double result=0,temp,temptotal;/*result sonuç tutan değişken,temp chardan floata değiştirmek için tuttuğum değişken
									temptotal ise sayı(x)nın üssü ile hesapladığım değişken */
	char tempnumber[20]; /*sayı almak için oluşturduğum array*/
	
	while(x<lenght){/*strlen polinom kadar dönecek*/
		tempnumber[z]=polynom[x]; /* sayı almaya hemen başlıyorum bir işaret görene kadar olan charları alıyorum*/
		z=z+1;

		if(polynom[x]=='x'){/*char x ise önüne arkasına bakmak için koşul */		
			temptotal=1;/*üssü olmadığı vakitlerde yani üssü 1 olduğunda çarpan olması için 1 atadım. */		
			tempnumber[z-1]='\0';/*char 'x'se zyi sonradan arttırdığım için tempnumber z-1'i nulluyorum.
								 böylece oraya kadar olan sayıları almış olucak */
			sscanf(tempnumber,"%lf ",&temp);/* oraya kadar alan sayıyı floata çeviriyorum normalde 
											atof yapıcaktım fakat değişen birşey olmadı*/
			if(tempnumber[0]=='\0'){/*eğer tempnumber nullsa yani sayının kuvveti yoksa, tempde önceki değer kalıyor. 
									bu yüzden tempi 1liyorum*/
			temp=1;
			}

				if(polynom[x+1]=='^'){ /*xten sonra üssü varsa onu hesaplıyorum */
					tempus=polynom[x+2]-'0';/*üssü inte çeviriyorum '0' charından çıkararak(üssün 10dan küçük olması gerekiyor) */
					while(tempus>0){
					temptotal=value*temptotal;/*üs kadar çarpıyorum */
					tempus=tempus-1;
					}
					if(flag!=-1){
						result=result+temp*temptotal; /*flagimiz artıysa topluyor eksi ise çıkarıyor */
					
					}
					if(flag!=1){
						result=result-temp*temptotal;
					}	
				}
				else if(polynom[x+1]=='+'||polynom[x+1]=='-'){
					
					if(flag!=-1){
						result=result+temp*value; /*eğer üssü yoksa(xten sonra işaret geliyorsa) ayrı bir denklem yazıyorum. */
						
					
					}
					if(flag!=1){
						result=result-temp*value;
					}		
				}
			tempnumber[0]='\0';/* temp numberle işimiz bittiği için nulluyorum*/
			z=0;/*aynı şekilde z sayacınıda sıfırlıyorum */
		}
		
		if(polynom[x]=='+'){/*işaret için girdiğimiz için tempnumberi buralarda nulluyorum ve +/- için flag*/
			flag=1;
			tempnumber[0]='\0';
			z=0;
		}
		
		if(polynom[x]=='-'){			
			flag=-1;
			tempnumber[0]='\0';
			z=0;
		}		
			
		x=x+1;/* polinom sayacını arttıryıorum*/
	}
	return result; /*sonucu döndürüyorum */
}


